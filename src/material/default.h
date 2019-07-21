#ifndef DEFAULT_H
#define DEFAULT_H

#include "material.h"

#include "embree_helper.h"


struct Default : public Material
{
    Default();

    virtual bool Evaluate() override;
    virtual bool Sample() override;
    virtual bool Pdf() override;
};

#endif // DEFAULT_H
