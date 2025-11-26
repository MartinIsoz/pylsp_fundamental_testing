#ifndef laserIntenzitySolver_H
#define laserIntenzitySolver_H

#include "solidModel.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "uniformDimensionedFields.H"
#include "mechanicalEnergies.H"

namespace Foam{ namespace solidModels {

class laserIntenzitySolver : public solidModel {
private:
    volScalarField p_;
    volScalarField pMAX_;
    volScalarField pSUM_;
    laserIntenzitySolver(const laserIntenzitySolver&);
    void operator=(const laserIntenzitySolver&);

protected:
    virtual nonLinearGeometry::nonLinearType nonLinGeom() const { return nonLinearGeometry::LINEAR_GEOMETRY; }


public:
    TypeName("laserIntenzitySolver");
    laserIntenzitySolver(Time& runTime, const word& region = dynamicFvMesh::defaultRegion);
    virtual ~laserIntenzitySolver() {}

    virtual volVectorField& solutionD() { return D(); }
    virtual bool evolve();
    virtual tmp<vectorField> tractionBoundarySnGrad(const vectorField& traction, const scalarField& pressure, const fvPatch& patch) const;

    virtual void end() {}
    void writeFields(const Time& runTime) { 
        p_.write();
        pSUM_.write();
        pMAX_.write();
        D().write();
    }
};

}}

#endif
