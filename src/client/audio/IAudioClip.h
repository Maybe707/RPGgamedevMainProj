#ifndef RPG_IAUDIOCLIP_H
#define RPG_IAUDIOCLIP_H

#include <miniaudio.h>
#include <string>

/**
 * Интерфейс аудио-клипа.
 */
class IAudioClip
{
public:
    virtual ~IAudioClip() = default;

    /**
     * Получить путь до аудио-файла.
     *
     * @return путь до файла
     */
    virtual std::string getPath() const = 0;

protected:

    /**
     * Создать декодер для аудио-клипа.
     *
     * @param decoder декодер
     * @param config конфиг
     */
    virtual void createDecoder(ma_decoder* decoder, ma_decoder_config* config) const = 0;

    friend class AudioDevice;
};

#endif //RPG_IAUDIOCLIP_H
