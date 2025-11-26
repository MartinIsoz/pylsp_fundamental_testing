#ifndef homogenization_H
#define homogenization_H

#include "mechanicalLaw.H"
#include "surfaceMesh.H"
#include "zeroGradientFvPatchFields.H"
#include "oofemlib/engngm.h"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class homogenization Declaration
\*---------------------------------------------------------------------------*/

class homogenization
:
    public mechanicalLaw
{
    // Private data
        int dim;
        std::vector<std::unique_ptr<oofem::EngngModel>> oofem_problems;
        oofem::FloatArray macroStress;
        oofem::FloatArray macroStrain;
        oofem::FloatArray macroPlasticStrain;

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

        //- Total strain
        volSymmTensorField epsilon_;
        volSymmTensorField epsilonP_;

    // Private Member Functions

        void initOOFEM(const dictionary& dict);
        void macroLaw2d(oofem::Homogenization* oofem_problem, const symmTensor& strain, symmTensor& stress, symmTensor& plasticStrain);
        void macroLaw3d(oofem::Homogenization* oofem_problem, const symmTensor& strain, symmTensor& stress, symmTensor& plasticStrain);


        //- Disallow default bitwise copy construct
        homogenization(const homogenization&);

        //- Disallow default bitwise assignment
        void operator=(const homogenization&);

public:

    //- Runtime type information
    TypeName("homogenization");

    // Static data members


    // Constructors

        //- Construct from dictionary
        homogenization
        (
            const word& name,
            const fvMesh& mesh,
            const dictionary& dict,
            const nonLinearGeometry::nonLinearType& nonLinGeom
        );


    // Destructor

        virtual ~homogenization();


    // Member Functions

        //- Return density
        virtual tmp<volScalarField> rho() const;


        //- Return the implicit stiffness
        //  This is the diffusivity for the Laplacian term
        virtual tmp<volScalarField> impK() const;

        //- Provide access to mu for the coupledUnsNonLinhomogenizationSolid
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
