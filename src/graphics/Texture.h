#ifndef RPG_TEXTURE_H
#define RPG_TEXTURE_H

#include <string>
#include "IGLObject.h"

class Texture : public IGLObject
{
private:
    unsigned int m_id{};
    std::string m_path; // Путь до файла
    int m_width{}; // Ширина текстуры
    int m_height{}; // Высота текстуры

public:
    explicit Texture(const std::string &path);

    void bind(unsigned int slot = 0) const;

    void unbind() const;

    unsigned int getId() const noexcept override;

    void destroy();

    std::string getPath() const;

    int getWidth() const;

    int getHeight() const;
};


#endif //RPG_TEXTURE_H
