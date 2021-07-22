#ifndef RPG_SHADER_H
#define RPG_SHADER_H

#include <glad/gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    unsigned int m_id;
public:
    // Конструктор генерирует шейдер "на лету"
    Shader(const char *vertexPath, const char *fragmentPath);

    // Активация шейдера
    void use() const;

    void setUniform(const std::string &name, bool value) const;

    void setUniform(const std::string &name, int value) const;

    void setUniform(const std::string &name, float value) const;

    void setUniform(const std::string &name, bool transpose, float *mat) const;

private:
    // Полезные функции для проверки ошибок компиляции/связывания шейдеров
    static void checkCompileErrors(unsigned int shader, const std::string &type);
};

#endif //RPG_SHADER_H
