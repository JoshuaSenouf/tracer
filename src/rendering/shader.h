#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <glad/glad.h>


class Shader
{
    public:
        GLuint Program;

        Shader();
        ~Shader();

        void setShader(std::string vertexPath, std::string fragmentPath);
        void useShader();
};

#endif
