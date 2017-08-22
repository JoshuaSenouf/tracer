#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>


class Randomizer
{
    public:
        Randomizer();

        std::uniform_int_distribution<int> intDistrib;
        std::uniform_real_distribution<float> floatDistrib;
        std::mt19937 mtEngine;

        unsigned getNewSeed();
        int getRandomInt();
        float getRandomFloat();
};

#endif // RANDOMIZER_H
