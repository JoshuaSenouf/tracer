#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>


class Material
{
    public:
        Material();

        virtual bool Evaluate() = 0;
        virtual bool Sample() = 0;
        virtual bool Pdf() = 0;
};

#endif // MATERIAL_H
