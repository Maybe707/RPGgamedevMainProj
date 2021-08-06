#include "AudioSystem.h"

#include <iostream>
#include "../components/AudioListenerComponent.h"
#include "../utils/Hierarchy.h"

AudioSystem::AudioSystem(entt::registry &registry)
        : m_registry(registry)
{
    // Будем сразу отлавливать момент создания/уничтожения компонентов
    m_registry.on_construct<AudioSourceComponent>().connect<&AudioSystem::onConstruct>(this);
    m_registry.on_destroy<AudioSourceComponent>().connect<&AudioSystem::onDestroy>(this);
}

void AudioSystem::update()
{
    // Находим слушателя
    entt::entity listenerEntity = entt::null;
    {
        auto view = m_registry.view<AudioListenerComponent>();
        for (auto entity : view)
        {
            listenerEntity = entity;
            break;
        }
    }

    // Если нет слушателя, то ничего не делаем
    if (listenerEntity == entt::null) return;

    // Определяем координаты слушателя
    TransformComponent listenerTransform = Hierarchy::computeTransform({listenerEntity, &m_registry});
    glm::vec2 listenerPosition = listenerTransform.position;

    auto view = m_registry.view<AudioSourceComponent>();
    for (auto entity : view)
    {
        auto &audioSourceComponent = view.get<AudioSourceComponent>(entity);

        // Определяем координаты аудио-сурса
        auto transformComponent = Hierarchy::computeTransform({entity, &m_registry});
        glm::vec2 sourcePosition = transformComponent.position;

        // Пересчитываем громкость
        float volumeFactor = 1.f - glm::distance(listenerPosition, sourcePosition) / audioSourceComponent.maxDistance;
        volumeFactor = std::clamp(volumeFactor, 0.f, 1.f);

        // Пересчитываем панорамирование
        float panFactor = (sourcePosition - listenerPosition).x / audioSourceComponent.maxDistance * 2.f;

        auto* audioSource = m_audioSourceRegistry[entity];
        audioSource->setVolume(audioSourceComponent.volume * volumeFactor);
        audioSource->setPan(audioSourceComponent.pan + panFactor);
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
    // Когда компонент уничтожают, удаляем его аудио-сурс
    auto audioSource = m_audioSourceRegistry[entity];
    m_audioDevice.remove(*audioSource);
    delete audioSource;
    m_audioSourceRegistry.erase(entity);
}
