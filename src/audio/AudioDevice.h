#ifndef RPG_AUDIODEVICE_H
#define RPG_AUDIODEVICE_H

#include "Sound.h"

#include <miniaudio.h>
#include <unordered_set>

#define FORMAT ma_format_f32
#define CHANNELS 2
#define SAMPLE_RATE 48000

/**
 * Сущность аудио-девайса.
 * Может воспроизводить звуки, миксовать их между собой.
 * В идеале, аудио-девайс должен быть один на всю игру.
 */
class AudioDevice
{
private:
    ma_device m_device{};

    std::unordered_set<Sound *> m_sounds;
public:
    AudioDevice();

    ~AudioDevice();

    void play(Sound &sound);

private:
    static void dataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);
    static bool readAndMixSound(Sound& sound, float *pOutputF32, ma_uint32 frameCount);
};

#endif //RPG_AUDIODEVICE_H
