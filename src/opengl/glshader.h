#ifndef GLSHADER_H
#define GLSHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include <glad/glad.h>


class GLShader
{
    public:
        GLShader();

        void setup(std::string vertexShaderPath,
            std::string fragmentShaderPath);
        void use();
        
    private:
        GLuint programID;
};

#endif // GLSHADER_H
