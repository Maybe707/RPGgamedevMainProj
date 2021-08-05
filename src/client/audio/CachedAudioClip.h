#ifndef RPG_CACHEDAUDIOCLIP_H
#define RPG_CACHEDAUDIOCLIP_H

#include <string>
#include <vector>
#include "IAudioClip.h"

/**
 * Класс аудио-клипа, который кэширует весь аудио-файл.
 * Данную реализацию лучше использовать для коротких звуков.
 */
class CachedAudioClip : public IAudioClip
{
    std::string m_path;
    std::vector<char> m_data;

public:
    /**
     * Создать аудио-клип.
     *
     * @param path путь до файла
     */
    CachedAudioClip(const std::string &path);

    virtual std::string getPath() const;

protected:
    virtual void createDecoder(ma_decoder* decoder, ma_decoder_config* config) const;
};

#endif //RPG_CACHEDAUDIOCLIP_H
