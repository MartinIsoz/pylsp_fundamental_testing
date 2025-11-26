#ifndef materialPoint_H
#define materialPoint_H

#include "solidModel.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "uniformDimensionedFields.H"
#include "mechanicalEnergies.H"

namespace Foam{ namespace solidModels {

class materialPoint : public solidModel {
private:
    materialPoint(const materialPoint&);
    void operator=(const materialPoint&);
    interpolationTable<scalar> strainXXseries_;
    OFstream osStrainStressData;
    OFstream osEpsP;

protected:
    virtual nonLinearGeometry::nonLinearType nonLinGeom() const { return nonLinearGeometry::LINEAR_GEOMETRY; }


public:
    TypeName("materialPoint");
    materialPoint(Time& runTime, const word& region = dynamicFvMesh::defaultRegion);
    virtual ~materialPoint() {}

    virtual volVectorField& solutionD() { return D(); }
    virtual bool evolve();
    virtual tmp<vectorField> tractionBoundarySnGrad(const vectorField& traction, const scalarField& pressure, const fvPatch& patch) const;

    virtual void end() {}
};

}}

#endif
