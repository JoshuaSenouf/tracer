#ifndef EMPIRICAL_H
#define EMPIRICAL_H

#include "material.h"

#include "embree_helper.h"


struct Empirical : public Material
{
    Empirical();

    virtual bool Evaluate() override;
    virtual bool Sample() override;
    virtual bool Pdf() override;
};

#endif // EMPIRICAL_H
