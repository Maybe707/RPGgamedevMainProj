#ifndef RPG_AUDIOSOURCECOMPONENT_H
#define RPG_AUDIOSOURCECOMPONENT_H

#include "../../client/audio/IAudioClip.h"
#include "../../utils/Types.h"
#include "../../client/audio/AudioState.h"

/**
 * Компонент аудио-сурса.
 * Необходим для воспроизведения аудио-клипа.
 */
struct AudioSourceComponent
{
    IAudioClip *audioClip;

    AudioState state{AudioState::Stop};

    float volume{1.f};
    float pan{0.f};
    bool loop{false};

public:

    /**
     * Создать аудио-сурс.
     *
     * @param audioClip аудио-клип
     */
    AudioSourceComponent(IAudioClip &audioClip);

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
};

#endif //RPG_AUDIOSOURCECOMPONENT_H
