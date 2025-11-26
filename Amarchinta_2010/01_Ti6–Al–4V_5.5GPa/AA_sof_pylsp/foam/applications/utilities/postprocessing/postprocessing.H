#ifndef POSTPROCESSING_H
#define POSTPROCESSING_H

#include "fvCFD.H"

/*
co máme:

1. epsilonPEq
2. principal stresses (ordered according to theory)

co si myslíme, že bychom chtěli:
1. maximum shears (Tresca model criterion)
2. maximum distortion energy (vonMises model criterion)
3. principal directions/axes (eigenvectors corresponding to principal stresses)
4. sigma(epsilon,epsilonP) decomposition that will allow us to compute compressive/expansive disbalance of forces required to compensate for the imposed plasticity

To Do:
1. order principal stresses and redraw kamax images (in-cell data) (by 03.05.2023)
2. modify pyLSP to automatically save epsilonPEq
- ostatní už asi tak nějak postupně, jak to půjde. vždycky ideálně zobrazit přes kamax výsledky.

udelat:
0. equivalentni a tak (to co uz mam do postprocesingu)

1. maximum shears (Tresca model criterion)
2. maximum distortion energy (vonMises model criterion)
3. principal directions/axes (eigenvectors corresponding to principal stresses)
4. sigma(epsilon,epsilonP) decomposition that will allow us to compute compressive/expansive disbalance of forces required to compensate for the imposed plasticity

*/

class CalcField {
    word m_fieldName;
    List<word> m_requiredFields;


protected:
    bool checkRequiredFields(const Time& runTime, const fvMesh& mesh) {
        word fieldName = getFieldName();
        Info<< "calculated field: " << fieldName << endl;

        const List<word>& requiredFields = getRequiredFields();

        Info<< "required fields: " << endl;
        forAll (requiredFields, i) {
            word requiredFieldName = requiredFields[i];

            IOobject fieldHeader
            (
                requiredFieldName,
                runTime.timeName(),
                mesh,
                IOobject::MUST_READ
            );

            // if (!fieldHeader.headerOk()) {
            //     Info<< "   " << requiredFieldName << " does NOT exists " << runTime.timeName() << endl;
            //     Info<< "status: no calculation at this time" << endl << endl;
            //     return false;
            // }

            word requiredFieldType(fieldHeader.headerClassName());

            Info<< "   " << requiredFieldName << " (" << requiredFieldType << ") " << "exists" << endl;
            
        }

        Info<< "status: OK" << endl;
        return true;
    }

    virtual void calculate(const Time& runTime, const fvMesh& mesh) = 0;

public:
    CalcField(word fieldName, const List<word> requiredFields) : m_fieldName(fieldName) {
        forAll(requiredFields, i) {
            m_requiredFields.append(requiredFields[i]);
        }
    };
    virtual ~CalcField() {};

    const List<word>& getRequiredFields() const {
        return m_requiredFields;
    }

    const word& getFieldName() const {
        return m_fieldName;
    }

    bool calc (const Time& runTime, const fvMesh& mesh) {
        if (!checkRequiredFields(runTime, mesh)) {
            return false;
        }

        Info << "in progress..." << endl;
        this->calculate(runTime, mesh);
        Info << "done" << endl << endl;
        return true;
    }
};

#endif