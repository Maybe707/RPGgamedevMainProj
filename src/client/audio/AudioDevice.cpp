#include "AudioDevice.h"

#include <iostream>
#include <algorithm>

AudioDevice::AudioDevice()
{
    ma_device_config deviceConfig;
    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = FORMAT;
    deviceConfig.playback.channels = CHANNELS;
    deviceConfig.sampleRate = SAMPLE_RATE;
    deviceConfig.dataCallback = dataCallback;
    deviceConfig.pUserData = &m_sounds;

    if (ma_device_init(nullptr, &deviceConfig, &m_device) != MA_SUCCESS)
    {
        std::cerr << "Failed to open playback device" << std::endl;
        ma_device_uninit(&m_device);
        return;
    }

    if (ma_device_start(&m_device) != MA_SUCCESS)
    {
        std::cerr << "Failed to start playback device" << std::endl;
        ma_device_uninit(&m_device);
        return;
    }
}

AudioDevice::~AudioDevice()
{
    ma_device_uninit(&m_device);
}

void AudioDevice::play(Sound &sound)
{
    auto result = m_sounds.find(&sound);
    if (result == m_sounds.end())
    {
        m_sounds.insert(&sound);
    }
    else
    {
        std::cerr << (*result)->m_path << " is already playing!" << std::endl;
    }
}

void AudioDevice::dataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    // Достаем все звуки
    auto *sounds = (std::unordered_set<Sound *> *) pDevice->pUserData;
    if (sounds == nullptr || sounds->empty()) return;


    // Смешиваем все звуки. Если звук уже не воспроизводится (result == false), то удаляем его из списка звуком
    for (auto it = sounds->begin(); it != sounds->end();)
    {
        bool result = readAndMixSound(**it, (float *) pOutput, frameCount);
        if (!result)
        {
            sounds->erase(it);
        }
        else
        {
            ++it;
        }
    }
}

bool AudioDevice::readAndMixSound(Sound &sound, float *pOutputF32, ma_uint32 frameCount)
{
    auto *temp = new float[frameCount * CHANNELS];

    ma_result result = ma_data_source_read_pcm_frames(&sound.m_decoder, temp, frameCount, nullptr, sound.isLoop());
    if (result != MA_SUCCESS)
    {
        return false;
    }

    // Смешиваем фреймы
    for (ma_uint32 sample = 0; sample < frameCount * CHANNELS; sample += CHANNELS)
    {
        // Громкость левого канала
        float left = 1 - std::clamp(sound.getPan(), 0.f, 1.f);
        pOutputF32[sample] += sound.getVolume() * left * temp[sample];
        std::clamp(pOutputF32[sample], -1.f, 1.f);

        // Громкость правого канала
        float right = 1 - std::abs(std::clamp(sound.getPan(), -1.f, 0.f));
        pOutputF32[sample + 1] += sound.getVolume() * right * temp[sample + 1];
        std::clamp(pOutputF32[sample + 1], -1.f, 1.f);
    }

    delete[] temp;

    return true;
}