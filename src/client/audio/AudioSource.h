#ifndef RPG_AUDIOSOURCE_H
#define RPG_AUDIOSOURCE_H

#include <mutex>
#include "IAudioClip.h"
#include "../../utils/Types.h"
#include "AudioState.h"

/**
 * Класс аудио-сурса. Содержит в себе необходимую для воспроизведения конфигурацию.
 */
class AudioSource
{
    IAudioClip &m_audioClip;

    AudioState m_state{AudioState::Stop};

    float m_volume{1.f};
    float m_pan{0.f};
    bool m_loop{false};

    std::mutex m_mutex;

public:

    /**
     * Создать аудио-сурс.
     * @param audioClip аудио-клип
     */
    AudioSource(IAudioClip &audioClip);

    /**
     * Получить аудио-клип.
     *
     * @return аудио-клип
     */
    IAudioClip &getAudioClip() const;

    /**
     * Получить текущее состояние.
     *
     * @return состояние
     */
    AudioState getState() const;

    /**
     * Начать воспроизведение.
     */
    void play();

    /**
     * Поставить на паузу.
     */
    void pause();

    /**
     * Остановить воспроизведение.
     */
    void stop();

    /**
     * Получить громкость.
     * 0.f - без звука
     * 1.f - 100%
     *
     * @return громкость
     */
    float getVolume() const;

    /**
     * Задать громкость.
     * 0.f - без звука
     * 1.f - 100%
     *
     * @param volume громкость
     */
    void setVolume(float volume);

    /**
     * Получить панорамирование.
     * -1.f - лево
     * 1.f - право
     *
     * @return панорамирование
     */
    float getPan() const;

    /**
     * Задать панорамирование.
     * -1.f - лево
     * 1.f - право
     *
     * @param pan панорамирование
     */
    void setPan(float pan);

    /**
     * Зациклен ли аудио-сурс.
     *
     * @return зациклен или нет
     */
    bool isLoop() const;

    /**
     * Зациклить аудио-сурс.
     *
     * @param loop зациклить или нет
     */
    void setLoop(bool loop);
};

#endif //RPG_AUDIOSOURCE_H
