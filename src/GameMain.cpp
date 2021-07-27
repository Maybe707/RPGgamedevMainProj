#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <algorithm>
#include "world/World.h"
#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "Player.h"
#include "graphics/Camera2D.h"
#include "Input.h"
#include "Data.h"
#include "RTime.h"
#include "KeyInputNotifier.h"
#include "graphics/Texture.h"
#include "graphics/SpriteBatch.h"
#include "Collision.h"
#include "graphics/Font.h"
#include "graphics/Text.h"

#define WALL_SIZE_1 10
#define WALL_SIZE_2 4
#define RAND_SPRITE_SIZE 7

// Никто не забыт, ничто не забыто

// D.E.L.E.T.E.D
// summonDestructor3000 
// 2021-2021
// Покойся с миром 

namespace map { std::vector<std::unique_ptr<Tile>> TilesData; }

void inputCallback(Window *window, int key, int scancode, int action, int mods);

void resizeCallback(Window *window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

KeyInputNotifier inputNotifier;
std::vector<int> inputVec{};

// TODO: Почистить main
int main()
{
    // Создание окна
    auto &window = Window::getInstance(SCR_WIDTH, SCR_HEIGHT, "TRUE RPG");
    window.makeContextCurrent();
    // window.setInputCallback(inputCallback);
    window.setResizeCallback(resizeCallback);

    Camera2D camera(glm::vec2(0), SCR_WIDTH, SCR_HEIGHT, 0.008f);
    Camera2D guiCamera(glm::vec2(0), SCR_WIDTH, SCR_HEIGHT, 0.5f);
    map::World world;

    // Создание шейдерной программы
    Shader ourShader = Shader::createShader("../res/shaders/shader.vs", "../res/shaders/shader.fs");
    Shader guiShader = Shader::createShader("../res/shaders/shader_gui.vs", "../res/shaders/shader_gui.fs");

    // Создание батча, который будет рисовать наши спрайты
    SpriteBatch spriteBatch(ourShader, 30000);

    SpriteBatch textBatch(guiShader, 30000);

    Font font("../res/fonts/vt323.ttf", 32);
    Text text(font, "True RPG!\n Welcome!");
    text.setOrigin(glm::vec2(text.getWidth() * camera.getScale(), text.getHeight()));

    Text fpsText(font, "Debug:\nFPS: ");
    float t = 0;

    Texture emptyTexture(0, "", 0, 0);
    Texture wallTexture = Texture::create("../res/textures/enemy.png");
    Texture heroTexture = Texture::create("../res/textures/hero.png");

    // Подготовка спрайтов
    Sprite emptySprite(emptyTexture);
    emptySprite.setTextureRect(IntRect(0, 0, 0, 0));
    emptySprite.setHeight(0);
    emptySprite.setWidth(0);
    emptySprite.setOrigin(glm::vec2(0));

    Sprite wallSprite(wallTexture);
    wallSprite.setTextureRect(IntRect(0, 224, 128 -32, 128 -32));
    wallSprite.setHeight(1);
    wallSprite.setWidth(1);
    wallSprite.setOrigin(glm::vec2(.5f));


    Sprite heroSprite(heroTexture);
    heroSprite.setTextureRect(IntRect(32, 96, 32, 32));
    heroSprite.setHeight(1);
    heroSprite.setWidth(1);
    heroSprite.setOrigin(glm::vec2(.5f));

    world.init();

    // TODO: Так добовляется информация о тайле.
    map::TilesData.emplace_back(std::make_unique<map::Tile>(map::Tile(map::TileType::EMPTY, emptySprite, 0, false)));
    map::TilesData.emplace_back(std::make_unique<map::Tile>(map::Tile(map::TileType::WALL, wallSprite, 1, true)));

    // Создание игрока
    Player playerHero(heroSprite, 15.0f);
    playerHero.setPosition(glm::vec2(2.0f, 2.0f));

    inputNotifier.attach(&playerHero);

    const int animIndexArray = 3;
    int animCount = 0;
    float deltaTime = 0;
    float animationDelta = 0;

    // Game timer.
    RTime chrono(0.0f, 0.0f, 0.0f);
    Collision collision;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window.isOpen())
    {
        camera.update();
        guiCamera.update();

        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteBatch.begin();
      
        deltaTime = chrono.getDeltaTime();
        processInput(playerHero, deltaTime);
        Collision::detection(world, playerHero, deltaTime);

        camera.setPosition(-playerHero.getPosition());
        spriteBatch.setProjectionMatrix(camera.getProjectionMatrix());
        spriteBatch.setViewMatrix(camera.getViewMatrix());

        if (window.getKey(GLFW_KEY_S))
        {
            animationDelta += deltaTime * 200;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        heroSprite.setTextureRect(IntRect(0, 96, 32, 32));
                        break;
                    case 1:
                        heroSprite.setTextureRect(IntRect(32, 96, 32, 32));
                        break;
                    case 2:
                        heroSprite.setTextureRect(IntRect(64, 96, 32, 32));
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }
        else if (window.getKey(GLFW_KEY_A))
        {
            animationDelta += deltaTime * 200;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        heroSprite.setTextureRect(IntRect(0, 64, 32, 32));
                        break;
                    case 1:
                        heroSprite.setTextureRect(IntRect(32, 64, 32, 32));
                        break;
                    case 2:
                        heroSprite.setTextureRect(IntRect(64, 64, 32, 32));
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }
        else if (window.getKey(GLFW_KEY_D))
        {
            animationDelta += deltaTime * 200;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        heroSprite.setTextureRect(IntRect(0, 32, 32, 32));
                        break;
                    case 1:
                        heroSprite.setTextureRect(IntRect(32, 32, 32, 32));
                        break;
                    case 2:
                        heroSprite.setTextureRect(IntRect(64, 32, 32, 32));
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }
        else if (window.getKey(GLFW_KEY_W))
        {
            animationDelta += deltaTime * 200;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        heroSprite.setTextureRect(IntRect(0, 0, 32, 32));
                        break;
                    case 1:
                        heroSprite.setTextureRect(IntRect(32, 0, 32, 32));
                        break;
                    case 2:
                        heroSprite.setTextureRect(IntRect(64, 0, 32, 32));
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }

        playerHero.draw(spriteBatch);
        world.draw(spriteBatch);

        spriteBatch.end();

        textBatch.begin();

        textBatch.setProjectionMatrix(guiCamera.getProjectionMatrix());

        text.setPosition(-guiCamera.getPosition() + glm::vec2(0.f, (int) window.getHeight() * guiCamera.getScale()));
        text.draw(textBatch);
        // Анимация просто для теста
        text.setColor(glm::vec4(
                (std::sin(t) + 1) / 2,
                (std::sin(2 * t + 1) + 1) / 2,
                (std::sin(0.5 * t) + 2) / 2, 1.f
        ));
        t += deltaTime * 200 / 100;

        fpsText.setText("Debug:\nFPS: " + std::to_string(chrono.getFps()));
        fpsText.setPosition(-guiCamera.getPosition() + glm::vec2(-(int) window.getWidth() * guiCamera.getScale(), -(int) window.getHeight() * guiCamera.getScale()));
        fpsText.setOrigin(glm::vec2(0, 0));
        fpsText.draw(textBatch);

        textBatch.end();

        // glfw: обмен содержимым front- и back- буферов.
        // Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        window.swapBuffers();
        glfwPollEvents();
    }

    ourShader.destroy();
    wallTexture.destroy();
    heroTexture.destroy();
    spriteBatch.destroy();
    font.destroy();

    window.destroy();

    return 0;
}

void inputCallback(Window *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        inputVec.push_back(key);
        inputNotifier.notifier(inputVec.back(), action);
    }
    if (action == GLFW_RELEASE)
    {
        inputNotifier.notifier(inputVec.back(), action);
        inputVec.erase(std::remove(inputVec.begin(), inputVec.end(), key), inputVec.end());
    }
}

// всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void resizeCallback(Window *window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}
