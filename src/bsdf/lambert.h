#ifndef LAMBERT_H
#define LAMBERT_H

#include <string>

#include "bsdf.h"

#include "embree_helper.h"


struct Lambert : public BSDF
{
    Lambert();

    virtual bool Evaluate() override;
    virtual bool Sample() override;
    virtual bool Pdf() override;
};

#endif // LAMBERT_H
