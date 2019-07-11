#ifndef BSDF_H
#define BSDF_H

#include <string>

#include "embree_helper.h"


struct BSDF
{
    BSDF();

    virtual bool Evaluate() = 0;
    virtual bool Sample() = 0;
    virtual bool Pdf() = 0;

    std::string _name;
};

#endif // BSDF_H
