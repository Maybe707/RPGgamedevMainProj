#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <algorithm>
#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/Buffer.h"
#include "Map.h"
#include "Player.h"
#include "graphics/Camera2D.h"
#include "Collision.h"
#include "Input.h"
#include "Data.h"
#include "ChronoGuard.h"
#include "KeyInputNotifier.h"
#include "ElementsForRandSprites.h"
#include "graphics/Texture.h"
#include "graphics/SpriteBatch.h"
#include "graphics/Font.h"
#include "graphics/Text.h"

#define WALL_SIZE_1 10
#define WALL_SIZE_2 4
#define RAND_SPRITE_SIZE 7

// Никто не забыт, ничто не забыто

void setOffsetForPipe(int &randId, int &offset1, int &offset2, int &randWall,
                      int &l_height, int &l_width)
{
    switch (randId)
    {
        case 1:
            offset1 = 1;
            offset2 = randWall - 2;
            break;

        case 2:
            offset1 = randWall - 2;
            offset2 = 1;
            break;

        case 3:
            offset1 = l_height;
            offset2 = randWall - 2;
            break;

        case 4:
            offset1 = randWall - 2;
            offset2 = l_width;
            break;
    }
}

int getRandomNumber2(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    // Равномерно распределяем рандомное число в нашем диапазоне
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

char **genRandomLevel(const int lHeight, const int lWidth)
{

    char **arr_ptr = new char *[lHeight];

    for (int r = 0; r < lHeight; ++r)
        arr_ptr[r] = new char[lWidth];

    for (int r2 = 0; r2 < lHeight; ++r2)
        for (int c2 = 0; c2 < lWidth; ++c2)
        {
            if (r2 == 0 || r2 == (lHeight - 1) || c2 == 0 || c2 == (lWidth - 1))
                arr_ptr[r2][c2] = '0';
            else
                arr_ptr[r2][c2] = ' ';
        }

    return arr_ptr;
}

void createHoleInWallNextLevel(char **arrPtr, int randWall, int randIdNextLevel,
                               int levelHeight, int levelWidth)
{
    switch (randIdNextLevel)
    {
        case 1:
            arrPtr[0][randWall - 1] = ' ';
            arrPtr[0][randWall] = ' ';
            break;
        case 2:
            arrPtr[randWall - 1][0] = ' ';
            arrPtr[randWall][0] = ' ';
            break;
        case 3:
            arrPtr[0][randWall - 1] = ' ';
            arrPtr[0][randWall] = ' ';
            break;
        case 4:
            arrPtr[randWall - 1][0] = ' ';
            arrPtr[randWall][0] = ' ';
            break;
    }
}

const int createHoleInWall(char **arrPtr, const int lHeight, const int lWidth,
                           int randId)
{
    int rand_wall = 0;

    switch (randId)
    {
        case 1:
            rand_wall = getRandomNumber2(1, lWidth - 3);
            arrPtr[0][rand_wall] = ' ';
            ++rand_wall;
            arrPtr[0][rand_wall] = ' ';
            break;
        case 2:
            rand_wall = getRandomNumber2(1, lHeight - 3);
            arrPtr[rand_wall][0] = ' ';
            ++rand_wall;
            arrPtr[rand_wall][0] = ' ';
            break;
        case 3:
            rand_wall = getRandomNumber2(1, lWidth - 3);
            arrPtr[lHeight - 1][rand_wall] = ' ';
            ++rand_wall;
            arrPtr[lHeight - 1][rand_wall] = ' ';
            break;
        case 4:
            rand_wall = getRandomNumber2(1, lHeight - 3);
            arrPtr[rand_wall][lWidth - 1] = ' ';
            ++rand_wall;
            arrPtr[rand_wall][lWidth - 1] = ' ';
            break;
    }

    return rand_wall;
}

int levelInRandId(int randId)
{
    switch (randId)
    {
        case 4:
            return 2;
        case 2:
            return 4;
        case 3:
            return 1;
        case 1:
            return 3;
    }

    return 0;
}

void nextLevelOffset(int *offset1, int *offset2, int randId)
{
    switch (randId)
    {
        case 4:
            *offset2 += 10;
            *offset1 = 0;
            break;
        case 2:
            *offset2 += 10;
            *offset1 = 0;
            break;
        case 1:
            *offset1 += 10;
            *offset2 = 0;
            break;
        case 3:
            *offset1 += 10;
            *offset2 = 0;
            break;
    }
}

char **createPipe(const int randId, const int size1 = 4, const int size2 = 10)
{
    char **arrPtr = nullptr;

    if (randId == 1 || randId == 3)
    {
        arrPtr = new char *[size2];

        for (int r = 0; r < size2; ++r)
            arrPtr[r] = new char[size1];

        for (int r2 = 0; r2 < size2; ++r2)
            for (int c2 = 0; c2 < size1; ++c2)
            {
                if (c2 == 0 || c2 == (size1 - 1))
                    arrPtr[r2][c2] = '0';
                else
                    arrPtr[r2][c2] = ' ';
            }
    }
    if (randId == 2 || randId == 4)
    {
        arrPtr = new char *[size1];

        for (int l = 0; l < size1; ++l)
            arrPtr[l] = new char[size2];

        for (int n2 = 0; n2 < size1; ++n2)
            for (int m2 = 0; m2 < size2; ++m2)
            {
                if (n2 == 0 || n2 == (size1 - 1))
                    arrPtr[n2][m2] = '0';
                else
                    arrPtr[n2][m2] = ' ';
            }
    }

    return arrPtr;
}

void summonDestructor3000(char **arrObj, const int height, const int width)
{
    for (int count = 0; count < height; ++count)
        delete[] arrObj[count];
    delete[] arrObj;
    arrObj = nullptr;
}

void inputCallback(Window *window, int key, int scancode, int action, int mods);

void resizeCallback(Window *window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

KeyInputNotifier inputNotifier;
std::vector<int> inputVec{};

int main()
{
    // Создание окна
    auto &window = Window::getInstance(SCR_WIDTH, SCR_HEIGHT, "TRUE RPG");
    window.makeContextCurrent();
    // window.setInputCallback(inputCallback);
    window.setResizeCallback(resizeCallback);

    // Создание шейдерной программы
    Shader ourShader = Shader::createShader("../res/shaders/shader.vs", "../res/shaders/shader.fs");

    // Создание батча, который будет рисовать наши спрайты
    SpriteBatch spriteBatch(ourShader);

    Font font("../res/fonts/vt323.ttf", 32);
    Text text(font, "True RPG!\n Welcome!");
    text.setOrigin(glm::vec2(text.getWidth() / 2, text.getHeight()));

    Text fpsText(font, "FPS: ");
    fpsText.setScale(glm::vec2(0.8f, 0.8f));
    float t = 0;

    Texture wallTexture = Texture::create("../res/textures/enemy.png");
    Texture heroTexture = Texture::create("../res/textures/hero.png");

    unsigned int seedDeb = static_cast<unsigned>(time(0));
    std::cout << "rand seed: " << seedDeb << std::endl;
    srand(seedDeb);

    // FIXME: Нужно исправить генерацию размера что бы избавиться от рандомного SIGSEGV
    int lHeight = getRandomNumber2(4, 7) * 7 + 2;
    int lWidth = getRandomNumber2(4, 7) * 7 + 2;
    int lHeight2 = getRandomNumber2(4, 7) * 7 + 2;
    int lWidth2 = getRandomNumber2(4, 7) * 7 + 2;

    Camera2D camera(glm::vec2(0), SCR_WIDTH, SCR_HEIGHT);

    WorldMap worldMap1(SCR_WIDTH, SCR_HEIGHT, lHeight, lWidth);
    WorldMap worldMap2(SCR_WIDTH, SCR_HEIGHT, lHeight2, lWidth2);

    char **levelArray1 = genRandomLevel(lHeight, lWidth);
    int randId = getRandomNumber2(1, 4);
    int randWall = createHoleInWall(levelArray1, lHeight, lWidth, randId);
    WorldMap *pipe = nullptr;
    if (randId == 1 || randId == 3)
    {
        pipe = new WorldMap(SCR_WIDTH, SCR_HEIGHT, WALL_SIZE_1, WALL_SIZE_2);
    }
    if (randId == 2 || randId == 4)
    {
        pipe = new WorldMap(SCR_WIDTH, SCR_HEIGHT, WALL_SIZE_2, WALL_SIZE_1);
    }
    char **pipePtr = createPipe(randId);
    pipe->initialize(pipePtr);

    int offset1 = 0;
    int offset2 = 0;

    setOffsetForPipe(randId, offset1, offset2, randWall, lHeight, lWidth);

    int offset1and1 = offset1;
    int offset2and2 = offset2;

    int randId2 = levelInRandId(randId);
    nextLevelOffset(&offset1and1, &offset2and2, randId2);

    worldMap1.initialize(levelArray1);

    char **levelArray2 = genRandomLevel(lHeight2, lWidth2);
    createHoleInWallNextLevel(levelArray2, randWall, randId2, lHeight2, lWidth2);
    worldMap2.initialize(levelArray2);

    SpriteRandSet randSprite(RAND_SPRITE_SIZE, RAND_SPRITE_SIZE);
//    randSprite.setRandSprite(arraySpritesSet, 1);
    worldMap1.setRandomSprites(arraySpritesSet, randSprite);
    worldMap2.setRandomSprites(arraySpritesSet, randSprite);

    // Подготовка спрайтов
    Sprite wallSprite(wallTexture);
    wallSprite.setTextureRect(IntRect(0, 224, 96, 96));
    wallSprite.setScale(glm::vec2(2.f / 3.f, 2.f / 3.f));
    wallSprite.setOrigin(glm::vec2(48, 48));

    Sprite heroSprite(heroTexture);
    heroSprite.setTextureRect(IntRect(32, 96, 32, 32));
    heroSprite.setScale(glm::vec2(2.f, 2.f));
    heroSprite.setOrigin(glm::vec2(16, 16));

    // Создание игрока
    Player playerHero(heroSprite, 2.0f);
    playerHero.setPosition(glm::vec2(450.0f, -150.0f));

    inputNotifier.attach(&playerHero);

    const int animIndexArray = 3;
    int animCount = 0;
    float deltaTime = 0;
    float animationDelta = 0;
    const int mapObjectsRow = lHeight;
    const int mapObjectsCol = lWidth;

    const int mapObjectsRow2 = lHeight2;
    const int mapObjectsCol2 = lWidth2;

    MapObject **mapObjectsPointer = new MapObject *[mapObjectsRow];
    for (int counter = 0; counter < mapObjectsRow; ++counter)
        mapObjectsPointer[counter] = new MapObject[mapObjectsCol];

    MapObject **mapObjectsPointer2 = new MapObject *[mapObjectsRow2];
    for (int count = 0; count < mapObjectsRow2; ++count)
        mapObjectsPointer2[count] = new MapObject[mapObjectsCol2];

    // Game timer.
    ChronoGuard chrono(0.0f, 0.0f, 0.0f);
    Collision collision;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (window.isOpen())
    {
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spriteBatch.begin();

        deltaTime = chrono.getDeltaTime() * 200;
        processInput(playerHero, deltaTime);

        worldMap1.render(mapObjectsPointer, spriteBatch, wallSprite, 0, 0, 3, 0);
        collision.detection(mapObjectsPointer, playerHero, deltaTime, worldMap1);

        pipe->render(mapObjectsPointer, spriteBatch, wallSprite, offset1, offset2, randId, 0);
        collision.detection(mapObjectsPointer, playerHero, deltaTime, *pipe);

        worldMap2.render(mapObjectsPointer2, spriteBatch, wallSprite, offset1and1, offset2and2, 0, randId2);
        collision.detection(mapObjectsPointer2, playerHero, deltaTime, worldMap2);

        camera.setPosition(-playerHero.getPosition());
        spriteBatch.setProjectionMatrix(camera.getProjectionMatrix());
        spriteBatch.setViewMatrix(camera.getViewMatrix());

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

        text.setPosition(-camera.getPosition() + glm::vec2(0.f, (int) SCR_HEIGHT / 2));
        text.draw(spriteBatch);
        // Анимация просто для теста
        text.setColor(glm::vec4(
                (std::sin(t) + 1) / 2,
                (std::sin(2 * t + 1) + 1) / 2,
                (std::sin(0.5 * t) + 2) / 2, 1.f
        ));
        t += deltaTime / 100;

        fpsText.setText("FPS: " + std::to_string(chrono.getFps()));
        fpsText.setPosition(-camera.getPosition() + glm::vec2(-(int) SCR_WIDTH / 2, -(int) SCR_HEIGHT / 2));
        fpsText.setOrigin(glm::vec2(0, 0));
        fpsText.draw(spriteBatch);

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
    font.destroy();

    window.destroy();

    // for (int counter2 = 0; counter2 < mapObjectsRow; ++counter2)
    // delete[] mapObjectsPointer[counter2];
    // delete[] mapObjectsPointer;

    for (int counter3 = 0; counter3 < mapObjectsRow2; ++counter3)
        delete[] mapObjectsPointer2[counter3];
    delete[] mapObjectsPointer2;

    summonDestructor3000(levelArray1, 23, 37);
//    summon_Destructor3000(levelArray2, 16, 24);

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
