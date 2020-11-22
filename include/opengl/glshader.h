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

        void Setup(
            std::string vertex_shader_path,
            std::string fragment_shader_path);
        void Use();

    private:
        GLuint program_id_;
};

#endif // GLSHADER_H
