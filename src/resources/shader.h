#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>


class Shader
{
    public:
        GLuint Program;

        Shader();
        ~Shader();
        void setShader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void useShader();
};

#endif
