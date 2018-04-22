#ifndef SHADERGL_H
#define SHADERGL_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <glad/glad.h>


class ShaderGL
{
    public:
        GLuint Program;

        ShaderGL();
        ~ShaderGL();

        void setShader(std::string vertexPath,
            std::string fragmentPath);
        void useShader();
};

#endif // SHADERGL_H
