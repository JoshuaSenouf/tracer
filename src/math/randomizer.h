#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>


class Randomizer
{
    public:
        Randomizer();

        unsigned getNewSeed();
        int getRandomInt();
        float getRandomFloat();

    private:
        std::uniform_int_distribution<int> intDistrib;
        std::uniform_real_distribution<float> floatDistrib;
        std::mt19937 mtEngine;
};

#endif // RANDOMIZER_H
