#ifndef GLSHADER_H
#define GLSHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>


class GLShader
{
    public:
        GLShader();

        void Setup(std::string vertexShaderPath,
            std::string fragmentShaderPath);
        void Use();
        
    private:
        GLuint programID;
};

#endif // GLSHADER_H
