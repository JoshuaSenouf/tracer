#include "randomizer.h"


Randomizer::Randomizer(): intDistrib(),
    floatDistrib(0, 1),
    mtEngine(getNewSeed())
{

}


unsigned Randomizer::getNewSeed()
{
    std::uniform_int_distribution<unsigned> newRandSeed;
    std::random_device rd;

    return newRandSeed(rd);
}


int Randomizer::getRandomInt()
{
    return intDistrib(mtEngine);
}


float Randomizer::getRandomFloat()
{
    return floatDistrib(mtEngine);
}
