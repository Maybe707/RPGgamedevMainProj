#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <algorithm>
#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "Player.h"
#include "graphics/Camera2D.h"
#include "Collision.h"
#include "Input.h"
#include "Data.h"
#include "ChronoGuard.h"
#include "KeyInputNotifier.h"
#include "graphics/Texture.h"
#include "graphics/SpriteBatch.h"
#include "world/World.h"

#define WALL_SIZE_1 10
#define WALL_SIZE_2 4
#define RAND_SPRITE_SIZE 7

// Никто не забыт, ничто не забыто

// D.E.L.E.T.E.D
// summonDestructor3000 
// 2021-2021
// Покойся с миром 

void inputCallback(Window *window, int key, int scancode, int action, int mods);

void resizeCallback(Window *window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

KeyInputNotifier inputNotifier;
std::vector<int> inputVec{};

int main()
{
    // Создание окна
    auto& window = Window::getInstance(SCR_WIDTH, SCR_HEIGHT, "TRUE RPG");
    window.makeContextCurrent();
    // window.setInputCallback(inputCallback);
    window.setResizeCallback(resizeCallback);

    map::World world;
    world.init();

    // Создание шейдерной программы
    Shader ourShader = Shader::createShader("../res/shaders/shader.vs", "../res/shaders/shader.fs");
    // Создание батча, который будет рисовать наши спрайты
    SpriteBatch spriteBatch(ourShader);

    Texture wallTexture = Texture::create("../res/textures/enemy.png");
    Texture heroTexture = Texture::create("../res/textures/hero.png");

    unsigned int seedDeb = static_cast<unsigned>(time(0));
    std::cout << "rand seed: " << seedDeb << std::endl;
    srand(seedDeb);

    Camera2D camera(glm::vec2(0), SCR_WIDTH, SCR_HEIGHT);

    // Подготовка спрайтов
    Sprite wallSprite(wallTexture);
    wallSprite.setTextureRect(IntRect(0, 224, 128 -32, 128 -32));
    wallSprite.setHeight(64);
    wallSprite.setWidth(64);
    wallSprite.setOrigin(glm::vec2(32, 32));

    Sprite heroSprite(heroTexture);
    heroSprite.setTextureRect(IntRect(32, 96, 32, 32));
    heroSprite.setHeight(64);
    heroSprite.setWidth(64);
    heroSprite.setOrigin(glm::vec2(32, 32));

    // Создание игрока
    Player playerHero(heroSprite, 2.0f);
    playerHero.setPosition(glm::vec2(0.0f, 0.0f));

    inputNotifier.attach(&playerHero);

    const int animIndexArray = 3;
    int animCount = 0;
    float deltaTime = 0;
    float animationDelta = 0;

    // Game timer.
    ChronoGuard chrono(0.0f, 0.0f, 0.0f);
    Collision collision;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window.isOpen())
    {
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        spriteBatch.begin();
      
        deltaTime = chrono.getDeltaTime() * 200;
        processInput(playerHero, deltaTime);

        camera.setPosition(-playerHero.getPosition());
        spriteBatch.setProjectionMatrix(camera.getProjectionMatrix());
        spriteBatch.setViewMatrix(camera.getViewMatrix());

        world.draw(spriteBatch, wallSprite);

        if (window.getKey(GLFW_KEY_S))
        {
            animationDelta += deltaTime;
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
            animationDelta += deltaTime;
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
            animationDelta += deltaTime;
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
            animationDelta += deltaTime;
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

        spriteBatch.end();

        // glfw: обмен содержимым front- и back- буферов.
        // Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        window.swapBuffers();
        glfwPollEvents();
    }

    ourShader.destroy();
    wallTexture.destroy();
    heroTexture.destroy();
    spriteBatch.destroy();

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


