#include "glshader.h"


GLShader::GLShader()
{
}

void GLShader::Setup(std::string vertexShaderPath,
    std::string fragmentShaderPath)
{
    // Reading the shaders on disk.
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::ifstream vertexShaderFStream;
    std::ifstream fragmentShaderFStream;

    vertexShaderFStream.exceptions(std::ifstream::badbit);
    fragmentShaderFStream.exceptions(std::ifstream::badbit);

    try
    {
        vertexShaderFStream.open(vertexShaderPath);
        fragmentShaderFStream.open(fragmentShaderPath);

        std::stringstream vertexShaderSStream;
        std::stringstream fragmentShaderSStream;

        vertexShaderSStream << vertexShaderFStream.rdbuf();
        fragmentShaderSStream << fragmentShaderFStream.rdbuf();
        vertexShaderFStream.close();
        fragmentShaderFStream.close();

        vertexShaderCode = vertexShaderSStream.str();
        fragmentShaderCode = fragmentShaderSStream.str();
    }
    catch (std::ifstream::failure exception)
    {
        std::cout << "ERROR - Could not read the vertex and/or fragment shaders on disk." << std::endl;
    }

    const GLchar* vShaderCode(vertexShaderCode.c_str());
    const GLchar* fShaderCode(fragmentShaderCode.c_str());

    int vShaderLength(vertexShaderCode.length());
    int fShaderLength(fragmentShaderCode.length());

    GLuint glVertexShaderID;
    GLuint glFragmentShaderID;
    GLint glCompileStatus;
    GLchar glOutputLog[512];

    // Pass the vertex shader code to OpenGL, and compile it.
    glVertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(glVertexShaderID, 1, &vShaderCode, &vShaderLength);
    glCompileShader(glVertexShaderID);
    glGetShaderiv(glVertexShaderID, GL_COMPILE_STATUS, &glCompileStatus);

    if (!glCompileStatus)
    {
        glGetShaderInfoLog(glVertexShaderID, 512, NULL, glOutputLog);

        std::cout << "ERROR - Could not compile the vertex shader:\n" << glOutputLog << std::endl;
    }

    // Pass the fragment shader code to OpenGL, and compile it.
    glFragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(glFragmentShaderID, 1, &fShaderCode, &fShaderLength);
    glCompileShader(glFragmentShaderID);
    glGetShaderiv(glFragmentShaderID, GL_COMPILE_STATUS, &glCompileStatus);

    if (!glCompileStatus)
    {
        glGetShaderInfoLog(glFragmentShaderID, 512, NULL, glOutputLog);

        std::cout << "ERROR - Could not compile the fragment shader:\n" << glOutputLog << std::endl;
    }

    // Link the compiled vertex and fragment shader to the programID
    programID = glCreateProgram();

    glAttachShader(programID, glVertexShaderID);
    glAttachShader(programID, glFragmentShaderID);
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &glCompileStatus);

    if (!glCompileStatus)
    {
        glGetProgramInfoLog(programID, 512, NULL, glOutputLog);

        std::cout << "ERROR - Could not compile the vertex and fragment shader to the GL Program:\n" << glOutputLog << std::endl;
    }

    glDeleteShader(glVertexShaderID);
    glDeleteShader(glFragmentShaderID);
}

void GLShader::Use()
{
    glUseProgram(programID);
}
