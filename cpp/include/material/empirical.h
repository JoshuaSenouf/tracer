#ifndef EMPIRICAL_H
#define EMPIRICAL_H

#include "material/material.h"


class Empirical : public Material
{
    public:
        Empirical();

        virtual bool Evaluate() override;
        virtual bool Sample() override;
        virtual bool Pdf() override;
};

#endif // EMPIRICAL_H
