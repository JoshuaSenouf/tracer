#include "opengl/glshader.h"


GLShader::GLShader()
{
}

void GLShader::Setup(std::string vertex_shader_path,
    std::string fragment_shader_path)
{
    // Reading the shaders on disk.
    std::string vertex_shader_code;
    std::string fragment_shader_code;
    std::ifstream vertex_shader_fstream;
    std::ifstream fragment_shader_fstream;

    vertex_shader_fstream.exceptions(std::ifstream::badbit);
    fragment_shader_fstream.exceptions(std::ifstream::badbit);

    try
    {
        vertex_shader_fstream.open(vertex_shader_path);
        fragment_shader_fstream.open(fragment_shader_path);

        std::stringstream vertex_shader_sstream;
        std::stringstream fragment_shader_sstream;

        vertex_shader_sstream << vertex_shader_fstream.rdbuf();
        fragment_shader_sstream << fragment_shader_fstream.rdbuf();
        vertex_shader_fstream.close();
        fragment_shader_fstream.close();

        vertex_shader_code = vertex_shader_sstream.str();
        fragment_shader_code = fragment_shader_sstream.str();
    }
    catch (std::ifstream::failure exception)
    {
        std::cout << "ERROR - Could not read the vertex and/or fragment shaders on disk." << std::endl;
    }

    const GLchar *vertex_shader_gl_code(vertex_shader_code.c_str());
    const GLchar *fragment_shader_gl_code(fragment_shader_code.c_str());

    int vertex_shader_length(vertex_shader_code.length());
    int fragment_shader_length(fragment_shader_code.length());

    GLuint vertex_shader_gl_id;
    GLuint fragment_shader_gl_id;
    GLint gl_compile_status;
    GLchar gl_output_log[512];

    // Pass the vertex shader code to OpenGL, and compile it.
    vertex_shader_gl_id = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertex_shader_gl_id, 1, &vertex_shader_gl_code, &vertex_shader_length);
    glCompileShader(vertex_shader_gl_id);
    glGetShaderiv(vertex_shader_gl_id, GL_COMPILE_STATUS, &gl_compile_status);

    if (!gl_compile_status)
    {
        glGetShaderInfoLog(vertex_shader_gl_id, 512, NULL, gl_output_log);

        std::cout << "ERROR - Could not compile the vertex shader:\n" << gl_output_log << std::endl;
    }

    // Pass the fragment shader code to OpenGL, and compile it.
    fragment_shader_gl_id = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragment_shader_gl_id, 1, &fragment_shader_gl_code, &fragment_shader_length);
    glCompileShader(fragment_shader_gl_id);
    glGetShaderiv(fragment_shader_gl_id, GL_COMPILE_STATUS, &gl_compile_status);

    if (!gl_compile_status)
    {
        glGetShaderInfoLog(fragment_shader_gl_id, 512, NULL, gl_output_log);

        std::cout << "ERROR - Could not compile the fragment shader:\n" << gl_output_log << std::endl;
    }

    // Link the compiled vertex and fragment shader to the program_id_
    program_id_ = glCreateProgram();

    glAttachShader(program_id_, vertex_shader_gl_id);
    glAttachShader(program_id_, fragment_shader_gl_id);
    glLinkProgram(program_id_);
    glGetProgramiv(program_id_, GL_LINK_STATUS, &gl_compile_status);

    if (!gl_compile_status)
    {
        glGetProgramInfoLog(program_id_, 512, NULL, gl_output_log);

        std::cout << "ERROR - Could not compile the vertex and fragment shader to the GL Program:\n" << gl_output_log << std::endl;
    }

    glDeleteShader(vertex_shader_gl_id);
    glDeleteShader(fragment_shader_gl_id);
}

void GLShader::Use()
{
    glUseProgram(program_id_);
}
