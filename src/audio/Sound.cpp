#include "Sound.h"

#include "AudioDevice.h"

Sound::Sound(const std::string &path)
        : m_path(path)
{
    ma_decoder_config config = ma_decoder_config_init(FORMAT, CHANNELS, SAMPLE_RATE);
    ma_decoder_init_file(path.c_str(), &config, &m_decoder);
}

Sound::~Sound()
{
    ma_decoder_uninit(&m_decoder);
}

std::string Sound::getPath()
{
    return m_path;
}

float Sound::getVolume()
{
    return m_volume;
}

void Sound::setVolume(float volume)
{
    m_volume = volume;
}

float Sound::getPan()
{
    return m_pan;
}

void Sound::setPan(float pan)
{
    m_pan = pan;
}

bool Sound::isLoop()
{
    return m_loop;
}

void Sound::setLoop(bool loop)
{
    m_loop = loop;
}
