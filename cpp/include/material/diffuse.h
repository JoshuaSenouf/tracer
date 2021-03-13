#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "material/material.h"


class Diffuse : public Material
{
    public:
        Diffuse();

        virtual bool Evaluate() override;
        virtual bool Sample() override;
        virtual bool Pdf() override;
};

#endif // DIFFUSE_H
