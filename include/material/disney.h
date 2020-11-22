#ifndef DISNEY_H
#define DISNEY_H

#include "material/material.h"


class Disney : public Material
{
    public:
        Disney();

        virtual bool Evaluate() override;
        virtual bool Sample() override;
        virtual bool Pdf() override;
};

#endif // DISNEY_H
