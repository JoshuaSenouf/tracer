#ifndef DEFAULT_H
#define DEFAULT_H

#include "material/material.h"


class Default : public Material
{
    public:
        Default();

        virtual bool Evaluate() override;
        virtual bool Sample() override;
        virtual bool Pdf() override;
};

#endif // DEFAULT_H
