#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include "window/Window.h"
#include "RTime.h"
#include "client/graphics/Texture.h"
#include "client/graphics/SpriteBatch.h"
#include "Collision.h"
#include "Game.h"
#include "client/audio/AudioDevice.h"

// Никто не забыт, ничто не забыто

// D.E.L.E.T.E.D
// summonDestructor3000 
// 2021-2021
// Покойся с миром 

std::vector<std::unique_ptr<Tile>> TilesData;

void resizeCallback(Window *window, int width, int height);

int main()
{
    // Создание окна
    auto &window = Window::getInstance(1280, 720, "TRUE RPG");
    window.makeContextCurrent();
    window.setResizeCallback(resizeCallback);

    Game game;

    AudioDevice audioDevice;

    Sound music("../res/audio/music.mp3");
    music.setLoop(true);
    music.setVolume(0.5f);
    audioDevice.play(music);

    Texture baseTexture = Texture::create("../res/textures/base.png");
    Texture waterTexture = Texture::create("../res/textures/water.png");

    // Подготовка спрайтов
    Sprite waterSprite(waterTexture);
    waterSprite.setTextureRect(IntRect(0, 0, 32, 32));
    waterSprite.setScale(glm::vec2(2.f, 2.f));
    waterSprite.setOrigin(glm::vec2(16, 16));

    Sprite sandSprite(baseTexture);
    sandSprite.setTextureRect(IntRect(192, 4256 - 32, 32, 32));
    sandSprite.setScale(glm::vec2(2.f, 2.f));
    sandSprite.setOrigin(glm::vec2(16, 16));

    Sprite grassSprite(baseTexture);
    grassSprite.setTextureRect(IntRect(96, 4256 - 32, 32, 32));
    grassSprite.setScale(glm::vec2(2.f, 2.f));
    grassSprite.setOrigin(glm::vec2(16, 16));

    Sprite dirtSprite(baseTexture);
    dirtSprite.setTextureRect(IntRect(160, 4256 - 32, 32, 32));
    dirtSprite.setScale(glm::vec2(2.f, 2.f));
    dirtSprite.setOrigin(glm::vec2(16, 16));

    // TODO: Лучше сделать нормальный настраиваемый компонент, а не манипулировать тут сырыми спрайтами
    TilesData.emplace_back(std::make_unique<Tile>(waterSprite, 0, false));
    TilesData.emplace_back(std::make_unique<Tile>(sandSprite, 1, false));
    TilesData.emplace_back(std::make_unique<Tile>(grassSprite, 2, false));
    TilesData.emplace_back(std::make_unique<Tile>(dirtSprite, 3, false));

    // Game timer
    RTime time(0.0f, 0.0f, 0.0f);
    Collision collision;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window.isOpen())
    {
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.update(time.getDeltaTime());

        // Обмен содержимым front- и back- буферов.
        // Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        window.swapBuffers();
        glfwPollEvents();
    }

    baseTexture.destroy();
    waterTexture.destroy();
    game.destroy();

    window.destroy();

    return 0;
}

// всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void resizeCallback(Window *window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}
