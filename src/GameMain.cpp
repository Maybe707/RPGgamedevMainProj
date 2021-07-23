#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "window/Window.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/Buffer.h"
#include <stb_image.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "Map.h"
#include "Player.h"
#include "graphics/Camera2D.h"
#include "Collision.h"
#include "Input.h"
#include "Data.h"
#include "ChronoGuard.h"
#include "useless_files/MapSource.h"
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

char **genRandomLevel(const int l_height, const int l_width)
{

    char **arr_ptr = new char *[l_height];

    for (int r = 0; r < l_height; ++r)
        arr_ptr[r] = new char[l_width];

    for (int r2 = 0; r2 < l_height; ++r2)
        for (int c2 = 0; c2 < l_width; ++c2)
        {
            if (r2 == 0 || r2 == (l_height - 1) || c2 == 0 || c2 == (l_width - 1))
                arr_ptr[r2][c2] = '0';
            else
                arr_ptr[r2][c2] = ' ';
        }

    return arr_ptr;
}

void createHoleInWallNextLevel(char **arr_ptr, int rand_wall, int rand_id_next_level,
                               int level_height, int level_width)
{
    switch (rand_id_next_level)
    {
        case 1:
            arr_ptr[0][rand_wall - 1] = ' ';
            arr_ptr[0][rand_wall] = ' ';
            break;
        case 2:
            arr_ptr[rand_wall - 1][0] = ' ';
            arr_ptr[rand_wall][0] = ' ';
            break;
        case 3:
            arr_ptr[0][rand_wall - 1] = ' ';
            arr_ptr[0][rand_wall] = ' ';
            break;
        case 4:
            arr_ptr[rand_wall - 1][0] = ' ';
            arr_ptr[rand_wall][0] = ' ';
            break;
    }
}

const int createHoleInWall(char **arr_ptr, const int l_height, const int l_width,
                           int rand_id)
{
    int rand_wall = 0;

    switch (rand_id)
    {
        case 1:
            rand_wall = getRandomNumber2(1, l_width - 3);
            arr_ptr[0][rand_wall] = ' ';
            ++rand_wall;
            arr_ptr[0][rand_wall] = ' ';
            break;
        case 2:
            rand_wall = getRandomNumber2(1, l_height - 3);
            arr_ptr[rand_wall][0] = ' ';
            ++rand_wall;
            arr_ptr[rand_wall][0] = ' ';
            break;
        case 3:
            rand_wall = getRandomNumber2(1, l_width - 3);
            arr_ptr[l_height - 1][rand_wall] = ' ';
            ++rand_wall;
            arr_ptr[l_height - 1][rand_wall] = ' ';
            break;
        case 4:
            rand_wall = getRandomNumber2(1, l_height - 3);
            arr_ptr[rand_wall][l_width - 1] = ' ';
            ++rand_wall;
            arr_ptr[rand_wall][l_width - 1] = ' ';
            break;
    }

    return rand_wall;
}

int levelInRandId(int rand_id)
{
    switch (rand_id)
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

void nextLevelOffset(int *offset1, int *offset2, int rand_id)
{
    switch (rand_id)
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

char **createPipe(const int rand_id, const int size_1 = 4, const int size_2 = 10)
{
    char **arr_ptr = nullptr;

    if (rand_id == 1 || rand_id == 3)
    {
        arr_ptr = new char *[size_2];

        for (int r = 0; r < size_2; ++r)
            arr_ptr[r] = new char[size_1];

        for (int r2 = 0; r2 < size_2; ++r2)
            for (int c2 = 0; c2 < size_1; ++c2)
            {
                if (c2 == 0 || c2 == (size_1 - 1))
                    arr_ptr[r2][c2] = '0';
                else
                    arr_ptr[r2][c2] = ' ';
            }
    }
    if (rand_id == 2 || rand_id == 4)
    {
        arr_ptr = new char *[size_1];

        for (int l = 0; l < size_1; ++l)
            arr_ptr[l] = new char[size_2];

        for (int n2 = 0; n2 < size_1; ++n2)
            for (int m2 = 0; m2 < size_2; ++m2)
            {
                if (n2 == 0 || n2 == (size_1 - 1))
                    arr_ptr[n2][m2] = '0';
                else
                    arr_ptr[n2][m2] = ' ';
            }
    }

    return arr_ptr;
}

void summonDestructor3000(char **arr_obj, const int height, const int width)
{
    for (int count = 0; count < height; ++count)
        delete[] arr_obj[count];
    delete[] arr_obj;
    arr_obj = nullptr;
}

void inputCallback(Window *window, int key, int scancode, int action, int mods);

void resizeCallback(Window *window, int width, int height);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

KeyInputNotifier Input_Notifier;
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

    Texture wallTexture("../res/textures/enemy.png");
    Texture heroTexture("../res/textures/hero.png");

    // Указываем OpenGL какой сэмплер к какому текстурному блоку принадлежит (это нужно сделать единожды)
    ourShader.use();
    ourShader.setUniform("tex", 0);

    unsigned int seedDeb = static_cast<unsigned>(time(0));
    std::cout << "rand seed: " << seedDeb << std::endl;
    srand(seedDeb);

    int l_height = getRandomNumber2(4, 7) * 7 + 2;
    int l_width = getRandomNumber2(4, 7) * 7 + 2;
    int l_height2 = getRandomNumber2(4, 7) * 7 + 2;
    int l_width2 = getRandomNumber2(4, 7) * 7 + 2;

    Camera2D camera(glm::vec2(0), SCR_WIDTH, SCR_HEIGHT);
    WorldMap worldmap1(SCR_WIDTH, SCR_HEIGHT, l_height, l_width);
    WorldMap worldmap2(SCR_WIDTH, SCR_HEIGHT, l_height2, l_width2);

    char **level_array1 = genRandomLevel(l_height, l_width);
    int rand_id = getRandomNumber2(1, 4);
    int rand_wall = createHoleInWall(level_array1, l_height, l_width, rand_id);
    WorldMap *Pipe = nullptr;
    if (rand_id == 1 || rand_id == 3)
    {
        Pipe = new WorldMap(SCR_WIDTH, SCR_HEIGHT, WALL_SIZE_1, WALL_SIZE_2);
    }
    if (rand_id == 2 || rand_id == 4)
    {
        Pipe = new WorldMap(SCR_WIDTH, SCR_HEIGHT, WALL_SIZE_2, WALL_SIZE_1);
    }
    char **pipe_ptr = createPipe(rand_id);
    Pipe->initialize(pipe_ptr);

    int offset1 = 0;
    int offset2 = 0;

    setOffsetForPipe(rand_id, offset1, offset2, rand_wall, l_height, l_width);

    int offset1_1 = offset1;
    int offset2_2 = offset2;

    int rand_id_2 = levelInRandId(rand_id);
    nextLevelOffset(&offset1_1, &offset2_2, rand_id_2);

    worldmap1.initialize(level_array1);

    char **level_array2 = genRandomLevel(l_height2, l_width2);
    createHoleInWallNextLevel(level_array2, rand_wall, rand_id_2, l_height2, l_width2);
    worldmap2.initialize(level_array2);

    SpriteRandSet RandSprite(RAND_SPRITE_SIZE, RAND_SPRITE_SIZE);
//    RandSprite.setRandSprite(arraySpritesSet, 1);
    worldmap1.setRandomSprites(arraySpritesSet, RandSprite);
    worldmap2.setRandomSprites(arraySpritesSet, RandSprite);

    Player Player_Hero(450.0f, -150.0f, 2.0f);  // 450.0f, -150.0f
    Input_Notifier.attach(&Player_Hero);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int anim_index_array = 3;
    int anim_count = 0;
    float *Vertex_Animation[4][anim_index_array] = {
            {vertices,   vertices2,  vertices3},
            {vertices4,  vertices5,  vertices6},
            {vertices7,  vertices8,  vertices9},
            {vertices10, vertices11, vertices12}
    };
    float Delta_Time = 0;
    float Animation_Delta = 0;
    const int Map_Objects_Row = l_height;
    const int Map_Objects_Col = l_width;

//	const int Map_Objects_Row = mapHeight;
//	const int Map_Objects_Col = mapWidth;

    const int Map_Objects_Row2 = l_height2;
    const int Map_Objects_Col2 = l_width2;

    MapObjects **Map_Objects_Pointer = new MapObjects *[Map_Objects_Row];
    for (int counter = 0; counter < Map_Objects_Row; ++counter)
        Map_Objects_Pointer[counter] = new MapObjects[Map_Objects_Col];

    MapObjects **Map_Objects_Pointer2 = new MapObjects *[Map_Objects_Row2];
    for (int count = 0; count < Map_Objects_Row2; ++count)
        Map_Objects_Pointer2[count] = new MapObjects[Map_Objects_Col2];

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
        Delta_Time = Chrono.getDeltaTime();
        processInput(window.getGLFWwindow(), Player_Hero, Delta_Time);

        worldmap1.render(Map_Objects_Pointer, ourShader, vaoWalls.getId(), wallTexture, 0, 0, 3, 0);
        Collision.detection(Map_Objects_Pointer, Player_Hero, Delta_Time, worldmap1, window.getGLFWwindow());

        Pipe->render(Map_Objects_Pointer, ourShader, vaoWalls.getId(), wallTexture, offset1, offset2, rand_id, 0);
        Collision.detection(Map_Objects_Pointer, Player_Hero, Delta_Time, *Pipe, window.getGLFWwindow());

        worldmap2.render(Map_Objects_Pointer2, ourShader, vaoWalls.getId(), wallTexture, offset1_1, offset2_2, 0,
                         rand_id_2);
        Collision.detection(Map_Objects_Pointer2, Player_Hero, Delta_Time, worldmap2, window.getGLFWwindow());

        camera.setPosition(glm::vec2(-Player_Hero.getXAxis(), -Player_Hero.getYAxis()));
        ourShader.setUniform("projection", camera.getProjectionMatrix());
        ourShader.setUniform("view", camera.getViewMatrix());

        // Биндим объект вершинного буфера чтобы получить возможность загрузить новые данные,
        // так как до этого мы анбиндили все объекты данного типа.
        vbo.bind();

        if (Player_Hero.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            Animation_Delta += Delta_Time;
            if (Animation_Delta > 30.0f)
            {
                switch (anim_count)
                {
                    default:
                        anim_count = 0;
                    case 0:
                        vbo.setBufferData(Vertex_Animation[0][anim_count], sizeof(vertices), GL_STATIC_DRAW);
                        break;
                    case 1:
                        vbo.setBufferData(Vertex_Animation[0][anim_count], sizeof(vertices), GL_STATIC_DRAW);
                        break;
                    case 2:
                        vbo.setBufferData(Vertex_Animation[0][anim_count], sizeof(vertices), GL_STATIC_DRAW);
                        break;
                }
                ++anim_count;
                Animation_Delta = 0;
            }
        }
        else if (Player_Hero.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            Animation_Delta += Delta_Time;
            if (Animation_Delta > 30.0f)
            {
                switch (anim_count)
                {
                    default:
                        anim_count = 0;
                    case 0:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                    case 1:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                    case 2:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                }
                ++anim_count;
                Animation_Delta = 0;
            }
        }
        else if (Player_Hero.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS)
        {
            Animation_Delta += Delta_Time;
            if (Animation_Delta > 30.0f)
            {
                switch (anim_count)
                {
                    default:
                        anim_count = 0;
                    case 0:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                    case 1:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                    case 2:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                }
                ++anim_count;
                Animation_Delta = 0;
            }
        }
        else if (Player_Hero.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window.getGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS)
        {
            Animation_Delta += Delta_Time;
            if (Animation_Delta > 30.0f)
            {
                switch (anim_count)
                {
                    default:
                        anim_count = 0;
                    case 0:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                    case 1:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                    case 2:
                        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][anim_count],
                                     GL_STATIC_DRAW);
                        break;
                }
                ++anim_count;
                Animation_Delta = 0;
            }
        }

        Player_Hero.draw(SCR_WIDTH, SCR_HEIGHT, ourShader, vao.getId(), heroTexture);

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

    for (int counter2 = 0; counter2 < Map_Objects_Row; ++counter2)
        delete[] Map_Objects_Pointer[counter2];
    delete[] Map_Objects_Pointer;

    for (int counter3 = 0; counter3 < Map_Objects_Row2; ++counter3)
        delete[] Map_Objects_Pointer2[counter3];
    delete[] Map_Objects_Pointer2;

    summonDestructor3000(level_array1, 23, 37);
//    summon_Destructor3000(level_array2, 16, 24);

    return 0;
}

void inputCallback(Window *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        stack.push(key);
        Input_Notifier.notifier(stack.getElement(), action);
    }
    if (action == GLFW_RELEASE)
    {
        stack.popSearch(key);
        Input_Notifier.notifier(stack.getElement(), action);
    }
}

// всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void resizeCallback(Window *window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}


