#include "StreamAudioClip.h"
#include "AudioDevice.h"

StreamAudioClip::StreamAudioClip(const std::string &path)
        : m_path(path) {}

std::string StreamAudioClip::getPath() const
{
    return m_path;
}

void StreamAudioClip::createDecoder(ma_decoder *decoder, ma_decoder_config* config) const
{
    // если я правильно понял, оно по дефолту работает как нужно
    ma_decoder_init_file(m_path.c_str(), config, decoder);
}

