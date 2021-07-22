#include "Shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // 1. Получение исходного кода вершинного/фрагментного шейдера из переменной filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Убеждаемся, что объекты ifstream могут выбросить исключение:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Читаем содержимое файловых буферов
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();

        // Конвертируем в строковую переменную данные из потока
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    // 2. Компилируем шейдеры
    unsigned int vertex, fragment;

    // Вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Шейдерная программа
    m_id = glCreateProgram();
    glAttachShader(m_id, vertex);
    glAttachShader(m_id, fragment);
    glLinkProgram(m_id);
    checkCompileErrors(m_id, "PROGRAM");

    // После того, как мы связали шейдеры с нашей программой, удаляем их, т.к. они больше не нужны
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(m_id);
}

void Shader::setUniform(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setUniform(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setUniform(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

// TODO: По какой-то причине в коде используются транспонированные и нетранспонированные матрицы одновременно,
//  поэтому добавил тут параметр transpose. По хорошему нужно остановиться на каком-то одном варианте.
void Shader::setUniform(const std::string &name, bool transpose, float *mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, transpose ? GL_TRUE : GL_FALSE, mat);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
                      << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
