#ifndef DISNEY_H
#define DISNEY_H

#include "material.h"


struct Disney : public Material
{
    Disney();

    virtual bool Evaluate() override;
    virtual bool Sample() override;
    virtual bool Pdf() override;
};

#endif // DISNEY_H
