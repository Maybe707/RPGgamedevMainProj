#ifndef RPG_AUDIODEVICE_H
#define RPG_AUDIODEVICE_H

#include "AudioSource.h"
#include "AudioState.h"

#include <miniaudio.h>
#include <mutex>
#include <unordered_map>

#define FORMAT ma_format_f32
#define CHANNELS 2
#define SAMPLE_RATE 48000

// Структурка для передачи данных в callback декодера
struct UserData
{
    std::unordered_map<AudioSource *, ma_decoder> &sources;
    std::mutex &mutex;
};

/**
 * Сущность аудио-девайса.
 * Может воспроизводить звуки, миксовать их между собой.
 * В идеале, аудио-девайс должен быть один на всю игру.
 */
class AudioDevice
{
private:
    ma_device m_device{};

    // Мапа с аудио-сурсами является разделяемым ресурсом,
    // т.к. воспроизведение звука выполняется в отдельном потоке.
    // Нужно быть осторожным при работе с ней
    std::unordered_map<AudioSource *, ma_decoder> m_sources;

    std::mutex m_mutex;

    // Это мы будем передавать в callback декодера
    UserData m_userData;

public:

    /**
     * Создать аудио-девайс.
     */
    AudioDevice();

    ~AudioDevice();

    /**
     * Добавить аудио-сурс.
     *
     * @param source аудио-сурс
     */
    void add(AudioSource &source);

    /**
     * Удалить аудио-сурс.
     *
     * @param source аудио-сурс
     */
    void remove(AudioSource &source);

    /**
     * Очистить девайс.
     */
    void clear();

private:
    static void dataCallback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount);

    static bool readAndMixSound(const AudioSource &source, ma_decoder &decoder, float *pOutputF32, ma_uint32 frameCount);
};

#endif //RPG_AUDIODEVICE_H
