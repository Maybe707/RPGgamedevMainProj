#ifndef RPG_STREAMAUDIOCLIP_H
#define RPG_STREAMAUDIOCLIP_H

#include <string>
#include "IAudioClip.h"

/**
 * Класс не хранит ничего в памяти, воспроизводит файл напрямую с диска.
 * Данную реализацию лучше использовать для длинных аудио-файлов.
 */
class StreamAudioClip : public IAudioClip
{
    std::string m_path;
public:
    /**
     * Создать аудио-клип.
     *
     * @param path путь до файла
     */
    StreamAudioClip(const std::string &path);

    virtual std::string getPath() const;

protected:
    virtual void createDecoder(ma_decoder* decoder, ma_decoder_config* config) const;
};

#endif //RPG_STREAMAUDIOCLIP_H
