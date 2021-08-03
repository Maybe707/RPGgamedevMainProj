#ifndef RPG_SOUND_H
#define RPG_SOUND_H

#include <miniaudio.h>
#include <string>

class Sound
{
    std::string m_path;

    ma_decoder m_decoder;

    float m_volume{1.f};
    float m_pan{0.f};
    bool m_loop{false};

public:
    Sound() = default;
    Sound(const std::string &path);

    ~Sound();

    std::string getPath();

    float getVolume();

    void setVolume(float volume);

    float getPan();

    void setPan(float pan);

    bool isLoop();

    void setLoop(bool loop);

    friend class AudioDevice;
};

#endif //RPG_SOUND_H
