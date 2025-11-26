#ifndef myExplicitLinGeomTotalDispSolid_H
#define myExplicitLinGeomTotalDispSolid_H

#include "solidModel.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "uniformDimensionedFields.H"
#include "mechanicalEnergies.H"

namespace Foam{ namespace solidModels {

class myExplicitLinGeomTotalDispSolid : public solidModel {
private:
    bool bUpdateDeltaT;
    const volScalarField impK_;
    surfaceScalarField impKf_;
    surfaceScalarField waveSpeed_;
    mechanicalEnergies energies_;
    volVectorField a_;
    volVectorField F0_;
    const scalar JSTScaleFactor_;

    void updateStress();

    myExplicitLinGeomTotalDispSolid(const myExplicitLinGeomTotalDispSolid&);
    void operator=(const myExplicitLinGeomTotalDispSolid&);

protected:
    virtual nonLinearGeometry::nonLinearType nonLinGeom() const { return nonLinearGeometry::LINEAR_GEOMETRY; }


public:
    TypeName("myExplicitLinearGeometryTotalDisplacement");
    myExplicitLinGeomTotalDispSolid(Time& runTime, const word& region = dynamicFvMesh::defaultRegion);
    virtual ~myExplicitLinGeomTotalDispSolid() {}

    virtual volVectorField& solutionD() { return D(); }
    virtual void setDeltaT(Time& runTime);
    virtual bool evolve();
    virtual tmp<vectorField> tractionBoundarySnGrad(const vectorField& traction, const scalarField& pressure, const fvPatch& patch) const;

    virtual void end();
};

}}

#endif
