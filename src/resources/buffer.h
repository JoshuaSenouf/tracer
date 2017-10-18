#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include "tinyexr.h"

#include "vector.h"
#include "math_helper.h"


class Buffer
{
    public:
        Buffer();

        void initBuffer(int bufferWidth, int bufferHeight);
        void cleanBufferData(int bufferWidth, int bufferHeight);
        void swapBufferData(std::vector<Vector3>& buffer);

        std::vector<Vector3>& getBufferData();
        void setBufferData(const std::vector<Vector3>& buffer);

    private:
        std::vector<Vector3> bufferData;
};

void exportToPPM(int ppmWidth, int ppmHeight, const std::vector<Vector3>& exportBuffer);
void exportToEXR(int exrWidth, int exrHeight, const std::vector<Vector3>& exportBuffer);


#endif // BUFFER_H
