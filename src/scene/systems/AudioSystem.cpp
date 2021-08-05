#include <iostream>
#include "AudioSystem.h"

AudioSystem::AudioSystem(entt::registry &registry)
        : m_registry(registry)
{
    // Будем сразу отлавливать момент создания/уничтожения компонентов
    m_registry.on_construct<AudioSourceComponent>().connect<&AudioSystem::onConstruct>(this);
    m_registry.on_destroy<AudioSourceComponent>().connect<&AudioSystem::onDestroy>(this);
}

void AudioSystem::update()
{
    auto view = m_registry.view<AudioSourceComponent>();
    for (auto entity : view)
    {
        auto &audioSourceComponent = view.get<AudioSourceComponent>(entity);

        auto* audioSource = m_audioSourceRegistry[entity];
        audioSource->setVolume(audioSourceComponent.volume);
        audioSource->setPan(audioSourceComponent.pan);
        audioSource->setLoop(audioSourceComponent.loop);

        if (audioSourceComponent.state == AudioState::Play)
        {
            audioSource->play();
        }
        else if (audioSourceComponent.state == AudioState::Pause)
        {
            audioSource->pause();
        }
        else if (audioSourceComponent.state == AudioState::Stop)
        {
            audioSource->stop();
        }
    }
}

void AudioSystem::destroy()
{
    // Здесь просто все чистим
    m_audioDevice.clear();
    for (const auto &item : m_audioSourceRegistry)
    {
        delete item.second;
    }
    m_audioSourceRegistry.clear();
}

void AudioSystem::onConstruct(entt::registry &registry, entt::entity entity)
{
    // В момент создания, создаем соответствующий аудио-сурс для компонента
    // и связываем с энтити в нашем реестре
    auto &audioSourceComponent = registry.get<AudioSourceComponent>(entity);

    auto* audioSource = new AudioSource(*audioSourceComponent.audioClip);
    m_audioSourceRegistry.insert({entity, audioSource});
    m_audioDevice.add(*audioSource);
}

void AudioSystem::onDestroy(entt::registry &registry, entt::entity entity)
{
    // Когда компонент уничтожают, нам соответствующий ему аудио-сурс уже не нужен
    auto audioSource = m_audioSourceRegistry[entity];
    m_audioDevice.remove(*audioSource);
    delete audioSource;
    m_audioSourceRegistry.erase(entity);
}
