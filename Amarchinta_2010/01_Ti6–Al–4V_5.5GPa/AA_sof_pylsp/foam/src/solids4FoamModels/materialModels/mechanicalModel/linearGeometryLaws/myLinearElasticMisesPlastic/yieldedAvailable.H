#ifndef yieldedAvailable_H
#define yieldedAvailable_H

#include "volFields.H"
#include "tmp.H"

namespace Foam
{

class yieldedAvailable
{
public:
    TypeName("yieldedAvailable");

    virtual tmp<volScalarField> yielded() const = 0;

    virtual ~yieldedAvailable() {}
};

} // End namespace Foam

#endif
