#ifndef RPG_SHADER_H
#define RPG_SHADER_H

#include <glad/gl.h>
#include <glm/glm.hpp>
#include "IGLObject.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader : public IGLObject
{
private:
    unsigned int m_id{};
public:
    Shader() = default;
    Shader(unsigned int id);

    // Активация шейдера
    void use() const;

    void setUniform(const std::string &name, bool value) const;

    void setUniform(const std::string &name, int value) const;

    void setUniform(const std::string &name, float value) const;

    void setUniform(const std::string &name, const glm::vec3& vec) const;

    void setUniform(const std::string &name, const glm::mat4& mat) const;

    void setUniform(const std::string &name, const int arr[], int size) const;

    unsigned int getId() const noexcept override;

    void destroy() override;

    static Shader createShader(const std::string& vertexPath, const std::string& fragmentPath);

private:
    // Полезные функции для проверки ошибок компиляции/связывания шейдеров
    static unsigned int compileShader(const std::string& path, unsigned int type);

    static void checkCompileErrors(unsigned int glHandelr, unsigned int status, 
                                   void (*GLget)(unsigned int, unsigned int, int*),
                                   void (*GLinfoLog)(unsigned int, int, int*, char*));
};

#endif //RPG_SHADER_H
