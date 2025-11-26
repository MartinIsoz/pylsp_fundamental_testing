#ifndef myLinearElastic_H
#define myLinearElastic_H

#include "mechanicalLaw.H"
#include "surfaceMesh.H"
#include "zeroGradientFvPatchFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class myLinearElastic Declaration
\*---------------------------------------------------------------------------*/

class myLinearElastic
:
    public mechanicalLaw
{
    // Private data

        //- Density
        dimensionedScalar rho_;

        //- Shear modulus (second Lame parameter)
        dimensionedScalar mu_;

        //- Bulk modulus
        dimensionedScalar K_;

        //- Young's modulus
        dimensionedScalar E_;

        //- Poisson's ratio
        dimensionedScalar nu_;

        //- First Lame parameter
        dimensionedScalar lambda_;

        //- Switch to enable solution of pressure Laplacian equation
        //  This can help quell oscillations in the hydrostatic stress
        Switch solvePressureEqn_;

        //- Optional: it is possible to scale the amount of smoothing in the
        //  pressure equation with this coefficient
        scalar pressureSmoothingCoeff_;

        //- Hydrostatic stress
        //  Note: sigmaHyd_ == tr(sigma)/3.0 == -p,
        //  where p is the hydrostatic pressure
        volScalarField sigmaHyd_;

        //- Hydrostatic stress surface field
        surfaceScalarField sigmaHydf_;

        //- Total strain
        volSymmTensorField epsilon_;

        //- Total strain surface field
        surfaceSymmTensorField epsilonf_;

        //- Total plastic strain
        volSymmTensorField epsilonP_;

        //- Total plastic strain surface field
        surfaceSymmTensorField epsilonPf_;        

        //- Initial (residual) stress field
        //  Defaults to zero if not specified
        const volSymmTensorField sigma0_;

        //- Initial (residual) stress surface field
        mutable surfaceSymmTensorField* sigma0fPtr_;

    // Private Member Functions

        //- Make the initial stress surface field
        void makeSigma0f() const;

        //- Return a reference to the initial stress surface field
        const surfaceSymmTensorField& sigma0f() const;

        //- Calculate hydrostatic component of the stress tensor
        void calculateHydrostaticStress
        (
            volScalarField& sigmaHyd,
            const volScalarField& trEpsilon
        );

        //- Calculate hydrostatic component of the stress tensor
        void calculateHydrostaticStress
        (
            surfaceScalarField& sigmaHyd,
            const surfaceScalarField& trEpsilon
        );

        //- Disallow default bitwise copy construct
        myLinearElastic(const myLinearElastic&);

        //- Disallow default bitwise assignment
        void operator=(const myLinearElastic&);

public:

    //- Runtime type information
    TypeName("myLinearElastic");

    // Static data members


    // Constructors

        //- Construct from dictionary
        myLinearElastic
        (
            const word& name,
            const fvMesh& mesh,
            const dictionary& dict,
            const nonLinearGeometry::nonLinearType& nonLinGeom
        );


    // Destructor

        virtual ~myLinearElastic();


    // Member Functions

        //- Return density
        virtual tmp<volScalarField> rho() const;

        //- Return bulk modulus
        virtual tmp<volScalarField> bulkModulus() const;

        //- Return density scale
        virtual dimensionedScalar rhoScalar() const;

        //- Return the implicit stiffness
        //  This is the diffusivity for the Laplacian term
        virtual tmp<volScalarField> impK() const;

        //- Provide access to mu for the coupledUnsNonLinmyLinearElasticSolid
        virtual const dimensionedScalar& mu() const;

        //- Bulk modulus
        virtual const dimensionedScalar& K() const;

        //- Young's modulus
        virtual const dimensionedScalar& E() const;

        //- Poisson's ratio
        virtual const dimensionedScalar& nu() const;

        //- Lambda
        virtual const dimensionedScalar& lambda() const;

        //- Calculate the stress
        virtual void correct(volSymmTensorField& sigma);

        //- Calculate the stress
        virtual void correct(surfaceSymmTensorField& sigma);
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
