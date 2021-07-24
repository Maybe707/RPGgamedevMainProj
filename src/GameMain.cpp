#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/Buffer.h"
#include "Map.h"
#include "Player.h"
#include "graphics/Camera2D.h"
#include "Collision.h"
#include "Input.h"
#include "Data.h"
#include "ChronoGuard.h"
#include "KeyInputNotifier.h"
#include "utils/Stack.h"
#include "ElementsForRandSprites.h"
#include "graphics/Texture.h"

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
Stack stack(4);

int main()
{
    // fglfw: инициализация и конфигурирование
    glfwInit();

    // Создание окна
    Window window(SCR_WIDTH, SCR_HEIGHT, "TRUE RPG");
    window.makeContextCurrent();
    window.setInputCallback(inputCallback);
    window.setResizeCallback(resizeCallback);

    // Компилирование нашей шейдерной программы
    Shader ourShader = Shader::createShader("../res/shaders/shader.vs", "../res/shaders/shader.fs");

    VertexArray vao;
    Buffer vbo(GL_ARRAY_BUFFER);

    vao.bind();

    vbo.bind();
    vbo.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);

    // Координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Атрибуты текстурных координат
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    vbo.unbind();
    vao.unbind();

    VertexArray vaoWalls;
    Buffer vboWalls(GL_ARRAY_BUFFER);

    vaoWalls.bind();

    vboWalls.bind();
    vboWalls.setBufferData(vertices, sizeof(vertices), GL_STATIC_DRAW);

    // Координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // Атрибуты текстурных координат
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    vboWalls.unbind();

    Texture wallTexture = Texture::create("../res/textures/enemy.png");
    Texture heroTexture = Texture::create("../res/textures/hero.png");

    // Указываем OpenGL какой сэмплер к какому текстурному блоку принадлежит (это нужно сделать единожды)
    ourShader.use();
    ourShader.setUniform("tex", 0);

    unsigned int seedDeb = static_cast<unsigned>(time(0));
    std::cout << "rand seed: " << seedDeb << std::endl;
    srand(seedDeb);

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

    Player playerHero(glm::vec2(450.0f, -150.0f), 2.0f);
    inputNotifier.attach(&playerHero);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int animIndexArray = 3;
    int animCount = 0;
    float *Vertex_Animation[4][animIndexArray] = {
            {vertices,   vertices2,  vertices3},
            {vertices4,  vertices5,  vertices6},
            {vertices7,  vertices8,  vertices9},
            {vertices10, vertices11, vertices12}
    };
    float deltaTime = 0;
    float animationDelta = 0;
    const int mapObjectsRow = lHeight;
    const int mapObjectsCol = lWidth;

//	const int mapObjectsRow = mapHeight;
//	const int mapObjectsCol = mapWidth;

    const int mapObjectsRow2 = lHeight2;
    const int mapObjectsCol2 = lWidth2;

    MapObject **mapObjectsPointer = new MapObject *[mapObjectsRow];
    for (int counter = 0; counter < mapObjectsRow; ++counter)
        mapObjectsPointer[counter] = new MapObject[mapObjectsCol];

    MapObject **mapObjectsPointer2 = new MapObject *[mapObjectsRow2];
    for (int count = 0; count < mapObjectsRow2; ++count)
        mapObjectsPointer2[count] = new MapObject[mapObjectsCol2];

    // Game timer.
    ChronoGuard Chrono(0.0f, 0.0f, 0.0f);
    Collision Collision;

    glEnable(GL_DEPTH_TEST);

    while (window.isOpen())
    {
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Chrono.setNewFrameTime();
        deltaTime = Chrono.getDeltaTime();
        processInput(window.getGLFWwindow(), playerHero, deltaTime);

        worldMap1.render(mapObjectsPointer, ourShader, vaoWalls.getId(), wallTexture, 0, 0, 3, 0);
        Collision.detection(mapObjectsPointer, playerHero, deltaTime, worldMap1, window.getGLFWwindow());

        pipe->render(mapObjectsPointer, ourShader, vaoWalls.getId(), wallTexture, offset1, offset2, randId, 0);
        Collision.detection(mapObjectsPointer, playerHero, deltaTime, *pipe, window.getGLFWwindow());

        worldMap2.render(mapObjectsPointer2, ourShader, vaoWalls.getId(), wallTexture, offset1and1, offset2and2, 0,
                         randId2);
        Collision.detection(mapObjectsPointer2, playerHero, deltaTime, worldMap2, window.getGLFWwindow());

        camera.setPosition(-playerHero.getPosition());
        ourShader.setUniform("projection", camera.getProjectionMatrix());
        ourShader.setUniform("view", camera.getViewMatrix());

        // Биндим объект вершинного буфера чтобы получить возможность загрузить новые данные,
        // так как до этого мы анбиндили все объекты данного типа.
        vbo.bind();

        if (playerHero.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            animationDelta += deltaTime;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        vbo.setBufferData(Vertex_Animation[0][animCount], sizeof(vertices), GL_STATIC_DRAW);
                        break;
                    case 1:
                        vbo.setBufferData(Vertex_Animation[0][animCount], sizeof(vertices), GL_STATIC_DRAW);
                        break;
                    case 2:
                        vbo.setBufferData(Vertex_Animation[0][animCount], sizeof(vertices), GL_STATIC_DRAW);
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }
        else if (playerHero.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            animationDelta += deltaTime;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][animCount],
                                     GL_STATIC_DRAW);
                        break;
                    case 1:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][animCount],
                                     GL_STATIC_DRAW);
                        break;
                    case 2:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][animCount],
                                     GL_STATIC_DRAW);
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }
        else if (playerHero.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            animationDelta += deltaTime;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][animCount],
                                     GL_STATIC_DRAW);
                        break;
                    case 1:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][animCount],
                                     GL_STATIC_DRAW);
                        break;
                    case 2:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][animCount],
                                     GL_STATIC_DRAW);
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }
        else if (playerHero.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            animationDelta += deltaTime;
            if (animationDelta > 30.0f)
            {
                switch (animCount)
                {
                    default:
                        animCount = 0;
                    case 0:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][animCount],
                                     GL_STATIC_DRAW);
                        break;
                    case 1:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][animCount],
                                     GL_STATIC_DRAW);
                        break;
                    case 2:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][animCount],
                                     GL_STATIC_DRAW);
                        break;
                }
                ++animCount;
                animationDelta = 0;
            }
        }

        playerHero.draw(ourShader, vao.getId(), heroTexture);

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        window.swapBuffers();
        glfwPollEvents();
    }

    ourShader.destroy();
    wallTexture.destroy();
    heroTexture.destroy();

    vbo.destroy();
    vboWalls.destroy();

    vao.destroy();
    vaoWalls.destroy();

    // glfw: завершение, освобождение всех выделенных ранее GLFW-реурсов
    glfwTerminate();

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
        stack.push(key);
        inputNotifier.notifier(stack.getElement(), action);
    }
    if (action == GLFW_RELEASE)
    {
        stack.popSearch(key);
        inputNotifier.notifier(stack.getElement(), action);
    }
}

// всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void resizeCallback(Window *window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}


