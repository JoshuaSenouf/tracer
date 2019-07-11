#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "material.h"

#include "embree_helper.h"


struct Diffuse : public Material
{
    Diffuse();

    virtual bool Evaluate() override;
    virtual bool Sample() override;
    virtual bool Pdf() override;
};

#endif // DIFFUSE_H
