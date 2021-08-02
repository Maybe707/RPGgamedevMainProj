#include "Sound.h"

#include "AudioDevice.h"

Sound::Sound(const std::string &path)
        : m_path(path), m_loop(false)
{
    ma_decoder_config config = ma_decoder_config_init(FORMAT, CHANNELS, SAMPLE_RATE);
    ma_decoder_init_file(path.c_str(), &config, &m_decoder);
}

Sound::~Sound()
{
    ma_decoder_uninit(&m_decoder);
}

bool Sound::isLoop()
{
    return m_loop;
}

void Sound::setLoop(bool loop)
{
    m_loop = loop;
}

std::string Sound::getPath()
{
    return m_path;
}
