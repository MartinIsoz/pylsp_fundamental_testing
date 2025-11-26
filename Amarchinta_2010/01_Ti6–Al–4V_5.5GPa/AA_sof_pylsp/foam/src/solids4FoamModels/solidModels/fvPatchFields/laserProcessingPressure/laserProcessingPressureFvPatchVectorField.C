/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

\*---------------------------------------------------------------------------*/

#include "laserProcessingPressureFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"
#include "lookupSolidModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

laserProcessingPressureFvPatchVectorField::
laserProcessingPressureFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedGradientFvPatchVectorField(p, iF),
    traction_(p.size(), vector::zero),
    pressure_(p.size(), 0.0),
    laserSpaceProfile_(p.size(), 0.0),
    pressureSeries_()
{
    fvPatchVectorField::operator=(patchInternalField());
    gradient() = vector::zero;
}


laserProcessingPressureFvPatchVectorField::
laserProcessingPressureFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedGradientFvPatchVectorField(p, iF),
    traction_(p.size(), vector::zero),
    pressure_(p.size(), 0.0),
    laserSpaceProfile_(p.size(), 0.0),
    pressureSeries_()
{
    Info<< "Creating " << type() << " laser boundary condition" << endl;

    if (dict.found("gradient"))
    {
        gradient() = vectorField("gradient", dict, p.size());
    }
    else
    {
        gradient() = vector::zero;
    }

    if (dict.found("value"))
    {
        Field<vector>::operator=(vectorField("value", dict, p.size()));
    }
    else
    {
        fvPatchVectorField::operator=(patchInternalField());
    }

    Info<< "    pressure is time-varying" << endl;

    /*
    
    fileName laserSpaceProfileDict(p.patch().boundaryMesh().mesh().time().systemPath() + "/laserSpaceProfile");

    if (!isFile(laserTimeProfileDict)) {
        return;
    }

    if (!isFile(laserSpaceProfileDict)) {
        return;
    }
    */

    //const dictionary& laserBeamDict = db().lookupObject<IOdictionary>("laserBeam");

    IOdictionary laserBeamProperties
    (
        IOobject
        (
            "laserBeamProperties",
            p.patch().boundaryMesh().mesh().time().caseConstant(),
            p.patch().boundaryMesh().mesh().time(),
            IOobject::READ_IF_PRESENT,
            IOobject::AUTO_WRITE
        )
    );

    if (!laserBeamProperties.headerOk()) {
        return;
    }


    fileName noneFileName("none");
    const List<Tuple2<scalar, scalar> >&  laserTimeProfile(laserBeamProperties.lookup("timeProfile"));
    pressureSeries_ = interpolationTable<scalar>(laserTimeProfile, bounds::repeatableBounding::CLAMP, noneFileName);
 
    point startPoint(laserBeamProperties.lookup("startPoint"));
    point endPoint(laserBeamProperties.lookup("endPoint"));
    Switch bConsiderFaceNormal(laserBeamProperties.lookup("considerFaceNormal"));
    string laserSpotType(laserBeamProperties.lookup("spotType"));

    const vector axis = (endPoint - startPoint);
    const scalar magAxis = sqrt(magSqr(axis));
    vector unitAxis = axis / magAxis;
   

    if ((laserSpotType == "PIECEWISE_LINEAR_SQUARE_LASER_SPOT") || (laserSpotType == "EXP_SQUARE_LASER_SPOT")) {
        vector squareDir (laserBeamProperties.lookup("square"));
        scalar rPureSquare(readScalar(laserBeamProperties.lookup("pureSquareRadius")));
        List<vector> C(4, vector::zero);
        C[0] = vector( rPureSquare,  rPureSquare, 0.0);
        C[1] = vector(-rPureSquare,  rPureSquare, 0.0);
        C[2] = vector( rPureSquare, -rPureSquare, 0.0);
        C[3] = vector(-rPureSquare, -rPureSquare, 0.0);

        vector e1 = (unitAxis & squareDir) * unitAxis;
        e1 = squareDir - e1;
        e1 = e1 / mag(e1);

        vector e2 = unitAxis ^ e1;
        e2 = e2 / mag(e2);
        if (laserSpotType == "PIECEWISE_LINEAR_SQUARE_LASER_SPOT") {
            const List<Tuple2<scalar, scalar> >&  laserSpaceProfile(laserBeamProperties.lookup("spaceProfile"));
            interpolationTable<scalar> spaceProfileSeries(laserSpaceProfile, bounds::repeatableBounding::CLAMP, noneFileName);
            forAll(p.patch(), faceI) {
                const vector d = p.patch().faceCentres()[faceI] - startPoint;
                const scalar magD = d & unitAxis;
                if ((magD > 0) && (magD < magAxis)) {
                    scalar d1 = e1 & d;
                    scalar d2 = e2 & d;
                    scalar maxDist = max(fabs(d1), fabs(d2));
                    if (maxDist > rPureSquare) {
                        vector V(d1, d2, 0.0);
                        for (int i = 0; i < 4; i++) {
                            vector R = V - C[i];
                            if ((R.x() * C[i].x() >= 0.0) && (R.y() * C[i].y() >= 0.0)) {
                                maxDist = rPureSquare + mag(R);
                            }
                        }
                    }
                    scalar eff = 1.0;
                    if (bConsiderFaceNormal) {
                        eff = -(p.Sf()[faceI] / p.magSf()[faceI]) & unitAxis;
                        if (eff < 0.0) {
                            eff = 0.0;
                        }
                    }
                    laserSpaceProfile_[faceI] = eff * spaceProfileSeries(maxDist);
                }
            }
        } else if (laserSpotType == "EXP_SQUARE_LASER_SPOT") {
            scalar a(readScalar(laserBeamProperties.lookup("a")));
            scalar c(readScalar(laserBeamProperties.lookup("c")));
            scalar n(readScalar(laserBeamProperties.lookup("n")));
            Switch bModified(laserBeamProperties.lookup("modified"));
            forAll(p.patch(), faceI) {
                const vector d = p.patch().faceCentres()[faceI] - startPoint;
                const scalar magD = d & unitAxis;
                if ((magD > 0) && (magD < magAxis)) {
                    scalar d1 = e1 & d;
                    scalar d2 = e2 & d;
                    laserSpaceProfile_[faceI] = exp(-(pow(0.5 * d1 / c / rPureSquare, n)) - (pow(0.5 * d2 / c / rPureSquare, n)));
                    
                    if (bModified) {
                        laserSpaceProfile_[faceI] -= 0.1 * a * exp(-a * sqrt(d1 * d1 + d2 * d2) / (c * 2.0 * rPureSquare));
                    }
                    
                    laserSpaceProfile_[faceI] = max(laserSpaceProfile_[faceI], 0.0);
                    
                    scalar eff = 1.0;
                    if (bConsiderFaceNormal) {
                        eff = -(p.Sf()[faceI] / p.magSf()[faceI]) & unitAxis;
                        if (eff < 0.0) {
                            eff = 0.0;
                        }
                    }
                    laserSpaceProfile_[faceI] = eff * laserSpaceProfile_[faceI];
                }
            }
        }
    } else if (laserSpotType == "PIECEWISE_LINEAR_CIRCLE_LASER_SPOT") {
        const List<Tuple2<scalar, scalar> >&  laserSpaceProfile(laserBeamProperties.lookup("spaceProfile"));
        interpolationTable<scalar> spaceProfileSeries(laserSpaceProfile, bounds::repeatableBounding::CLAMP, noneFileName);
        forAll(p.patch(), faceI) {
            const vector d = p.patch().faceCentres()[faceI] - startPoint;
            const scalar magD = fabs(d & unitAxis);
            if ((magD > 0) && (magD < magAxis)) {
                const scalar d2 = sqrt((d & d) - sqr(magD));
                scalar eff = 1.0;
                if (bConsiderFaceNormal) {
                    eff = -(p.Sf()[faceI] / p.magSf()[faceI]) & unitAxis;
                    if (eff < 0.0) {
                        eff = 0.0;
                    }
                }
                laserSpaceProfile_[faceI] = eff * spaceProfileSeries(d2);
            }
        }
    } else if (laserSpotType == "EXP_CIRCLE_LASER_SPOT") {
        scalar a(readScalar(laserBeamProperties.lookup("a")));
        scalar c(readScalar(laserBeamProperties.lookup("c")));
        scalar n(readScalar(laserBeamProperties.lookup("n")));
        scalar rPureSquare(readScalar(laserBeamProperties.lookup("pureSquareRadius")));
        Switch bModified(laserBeamProperties.lookup("modified"));
        forAll(p.patch(), faceI) {
            const vector d = p.patch().faceCentres()[faceI] - startPoint;
            const scalar magD = fabs(d & unitAxis);
            if ((magD > 0) && (magD < magAxis)) {
                const scalar d2 = sqrt((d & d) - sqr(magD));

                laserSpaceProfile_[faceI] = exp(-pow(pow(0.5 * d2 / c / rPureSquare, 2), 0.5 * n));
                
                if (bModified) {
                    laserSpaceProfile_[faceI] -= 0.1 * a * exp(-a * sqrt(d2 * d2) / (c * 2.0 * rPureSquare));
                }
                
                laserSpaceProfile_[faceI] = max(laserSpaceProfile_[faceI], 0.0);

                scalar eff = 1.0;
                if (bConsiderFaceNormal) {
                    eff = -(p.Sf()[faceI] / p.magSf()[faceI]) & unitAxis;
                    if (eff < 0.0) {
                        eff = 0.0;
                    }
                }
                laserSpaceProfile_[faceI] = eff * laserSpaceProfile_[faceI];
            }
        }
    } else {
    }
}


laserProcessingPressureFvPatchVectorField::
laserProcessingPressureFvPatchVectorField
(
    const laserProcessingPressureFvPatchVectorField& stpvf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedGradientFvPatchVectorField(stpvf, p, iF, mapper),
#ifdef OPENFOAMFOUNDATION
    traction_(mapper(stpvf.traction_)),
    pressure_(mapper(stpvf.pressure_)),
    laserSpaceProfile_(mapper(stpvf.laserSpaceProfile_)),
#else
    traction_(stpvf.traction_, mapper),
    pressure_(stpvf.pressure_, mapper),
    laserSpaceProfile_(stpvf.laserSpaceProfile_, mapper),
#endif
    pressureSeries_(stpvf.pressureSeries_)
{}


laserProcessingPressureFvPatchVectorField::
laserProcessingPressureFvPatchVectorField
(
    const laserProcessingPressureFvPatchVectorField& stpvf
)
:
    fixedGradientFvPatchVectorField(stpvf),
    traction_(stpvf.traction_),
    pressure_(stpvf.pressure_),
    laserSpaceProfile_(stpvf.laserSpaceProfile_),
    pressureSeries_(stpvf.pressureSeries_)
{}


laserProcessingPressureFvPatchVectorField::
laserProcessingPressureFvPatchVectorField
(
    const laserProcessingPressureFvPatchVectorField& stpvf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedGradientFvPatchVectorField(stpvf, iF),
    traction_(stpvf.traction_),
    pressure_(stpvf.pressure_),
    laserSpaceProfile_(stpvf.laserSpaceProfile_),
    pressureSeries_(stpvf.pressureSeries_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void laserProcessingPressureFvPatchVectorField::autoMap
(
    const fvPatchFieldMapper& m
)
{
    fixedGradientFvPatchVectorField::autoMap(m);

#ifdef OPENFOAMFOUNDATION
    m(traction_, traction_);
    m(pressure_, pressure_);
    m(laserSpaceProfile_, laserSpaceProfile_);    
#else
    traction_.autoMap(m);
    pressure_.autoMap(m);
    laserSpaceProfile_.autoMap(m);
#endif
}


// Reverse-map the given fvPatchField onto this fvPatchField
void laserProcessingPressureFvPatchVectorField::rmap
(
    const fvPatchVectorField& ptf,
    const labelList& addr
)
{
    fixedGradientFvPatchVectorField::rmap(ptf, addr);

    const laserProcessingPressureFvPatchVectorField& dmptf =
        refCast<const laserProcessingPressureFvPatchVectorField>(ptf);

    traction_.rmap(dmptf.traction_, addr);
    pressure_.rmap(dmptf.pressure_, addr);
    laserSpaceProfile_.rmap(dmptf.laserSpaceProfile_, addr);
}


// Update the coefficients associated with the patch field
void laserProcessingPressureFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    if (pressureSeries_.size())
    {
        pressure_ = laserSpaceProfile_ * pressureSeries_(this->db().time().timeOutputValue());
    }

    scalarField press = pressure_;

    // Lookup the solidModel object
    const solidModel& solMod = lookupSolidModel(patch().boundaryMesh().mesh());

    // Set surface-normal gradient on the patch corresponding to the desired
    // traction
    gradient() =
        solMod.tractionBoundarySnGrad
        (
            traction_, press, patch()
        );

    fixedGradientFvPatchVectorField::updateCoeffs();
}


void laserProcessingPressureFvPatchVectorField::evaluate
(
    const Pstream::commsTypes commsType
)
{
    if (!this->updated())
    {
        this->updateCoeffs();
    }

    // Lookup the gradient field
    const fvPatchField<tensor>& gradField =
        patch().lookupPatchField<volTensorField, tensor>
        (
#ifdef OPENFOAMESIORFOUNDATION
            "grad(" + internalField().name() + ")"
#else
            "grad(" + dimensionedInternalField().name() + ")"
#endif
        );

    // Face unit normals
    const vectorField n = patch().nf();

    // Delta vectors
    const vectorField delta = patch().delta();

    // Non-orthogonal correction vectors
    const vectorField k = ((I - sqr(n)) & delta);


    Field<vector>::operator=
    (
        patchInternalField()
        + (k & gradField.patchInternalField())
        + gradient()/patch().deltaCoeffs()
    );

    fvPatchField<vector>::evaluate();
}


void laserProcessingPressureFvPatchVectorField::write(Ostream& os) const
{
    // Bug-fix: courtesy of Michael@UW at https://www.cfd-online.com/Forums/
    // openfoam-cc-toolkits-fluid-structure-interaction/221892-solved-paraview
    // -cant-read-solids-files-duplicate-entries-keyword-value.html#post762325
    //fixedGradientFvPatchVectorField::write(os);
    fvPatchVectorField::write(os);

#ifdef OPENFOAMFOUNDATION
    writeEntry(os, "traction", traction_);
#else
    traction_.writeEntry("traction", os);
#endif

    os.writeKeyword("pressureSeries") << nl;
    os << token::BEGIN_BLOCK << nl;
    pressureSeries_.write(os);
    os << token::END_BLOCK << nl;

#ifdef OPENFOAMFOUNDATION
    writeEntry(os, "value", *this);
    writeEntry(os, "gradient", gradient());
#else
    writeEntry("value", os);
    gradient().writeEntry("gradient", os);
#endif
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField(fvPatchVectorField, laserProcessingPressureFvPatchVectorField);

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //
