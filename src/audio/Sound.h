#ifndef RPG_SOUND_H
#define RPG_SOUND_H

#include <miniaudio.h>
#include <string>

class Sound
{
    std::string m_path;

    ma_decoder m_decoder;

    bool m_loop;

public:
    Sound(const std::string &path);

    ~Sound();

    bool isLoop();

    void setLoop(bool loop);

    std::string getPath();

    friend class AudioDevice;
};

#endif //RPG_SOUND_H
