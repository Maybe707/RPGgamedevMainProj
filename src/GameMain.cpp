#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bits/types/stack_t.h>
#include "shader.h"
#include <stb_image.h>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Player_Implementation.h"
#include "Map_Objects.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "GL_Window.h"
#include "GL_Initializasion.h"
#include "Data.h"
#include "Chrono_Guard.h"
#include "Map_Source.h"
#include "Key_Input_Notifier.h"
#include "Stack_Engine.h"
#include "ElementsForRandSprites.h"

#define wall_size1 10
#define wall_size2 4
#define rand_sprite_size 7

void set_offset_for_pipe(int& rand_id, int& offset1, int& offset2, int& rand_wall,
                         int& l_height, int& l_width)
{
    switch(rand_id)
    {
    case 1:
        offset1 = 1;
        offset2 = rand_wall - 2;
        break;
    case 2:
        offset1 = rand_wall - 2;
        offset2 = 1;
        break;
    case 3:
        offset1 = l_height;
        offset2 = rand_wall - 2;
        break;
    case 4:
        offset1 = rand_wall - 2;
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

char** gen_Random_Level(const int l_height, const int l_width)
{
    
    char** arr_ptr = new char*[l_height];

    for(int r = 0; r < l_height; ++r)
        arr_ptr[r] = new char[l_width];

    for(int r2 = 0; r2 < l_height; ++r2)
        for(int c2 = 0; c2 < l_width; ++c2)
        {
            if(r2 == 0 || r2 == (l_height - 1) || c2 == 0 || c2 == (l_width - 1))
                arr_ptr[r2][c2] = '0';
            else
                arr_ptr[r2][c2] = ' ';
        }
    
    return arr_ptr;
}

void create_hole_inwall_next_level(char** arr_ptr, int rand_wall, int rand_id_next_level,
                                   int level_height, int level_width)
{
    switch(rand_id_next_level)
    {
    case 1:
        arr_ptr[0][rand_wall-1] = ' ';
        arr_ptr[0][rand_wall] = ' ';
        break;
    case 2:
        arr_ptr[rand_wall-1][0] = ' ';
        arr_ptr[rand_wall][0] = ' ';
        break;
    case 3:
        arr_ptr[0][rand_wall-1] = ' ';
        arr_ptr[0][rand_wall] = ' ';
        break;
    case 4:
        arr_ptr[rand_wall-1][0] = ' ';
        arr_ptr[rand_wall][0] = ' ';
        break;
    }
}

const int create_Hole_InWall(char** arr_ptr, const int l_height, const int l_width,
    int rand_id)
{
    int rand_wall = 0;

    switch(rand_id)
    {
    case 1:
        rand_wall = getRandomNumber2(1, l_width-3);
        arr_ptr[0][rand_wall] = ' ';
        ++rand_wall;
        arr_ptr[0][rand_wall] = ' ';
        break;
    case 2:
        rand_wall = getRandomNumber2(1, l_height-3);
        arr_ptr[rand_wall][0] = ' ';
        ++rand_wall;
        arr_ptr[rand_wall][0] = ' ';
        break;
    case 3:
        rand_wall = getRandomNumber2(1, l_width-3);
        arr_ptr[l_height-1][rand_wall] = ' ';
        ++rand_wall;
        arr_ptr[l_height-1][rand_wall] = ' ';
        break;
    case 4:
        rand_wall = getRandomNumber2(1, l_height-3);
        arr_ptr[rand_wall][l_width-1] = ' ';
        ++rand_wall;
        arr_ptr[rand_wall][l_width-1] = ' ';
        break;
    }

    return rand_wall;
}

int level_in_rand_id(int rand_id)
{
    switch(rand_id)
    {
    case 4:
        return rand_id = 2;
        break;
    case 2:
        return rand_id = 4;
        break;
    case 3:
        return rand_id = 1;
        break;
    case 1:
        return rand_id = 3;
        break;
    }
}

void next_level_offset(int* offset1, int* offset2, int rand_id)
{
    switch(rand_id)
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

char** create_Pipe(const int rand_id, const int size_1 = 4, const int size_2 = 10)
{
    char** arr_ptr = nullptr;
    
    if(rand_id == 1 || rand_id == 3)
    {
        arr_ptr = new char*[size_2];

        for(int r = 0; r < size_2; ++r)
            arr_ptr[r] = new char[size_1];

        for(int r2 = 0; r2 < size_2; ++r2)
            for(int c2 = 0; c2 < size_1; ++c2)
            {
                if(c2 == 0 || c2 == (size_1 - 1))
                    arr_ptr[r2][c2] = '0';
                else
                    arr_ptr[r2][c2] = ' ';
            }
    }
    if(rand_id == 2 || rand_id == 4)
    {
        arr_ptr = new char*[size_1];

        for(int l = 0; l < size_1; ++l)
            arr_ptr[l] = new char[size_2];

        for(int n2 = 0; n2 < size_1; ++n2)
            for(int m2 = 0; m2 < size_2; ++m2)
            {
                if(n2 == 0 || n2 == (size_1 - 1))
                    arr_ptr[n2][m2] = '0';
                else
                    arr_ptr[n2][m2] = ' ';
            }
    }

    return arr_ptr;
}

void summon_Destructor3000(char** arr_obj, const int height, const int width)
{
    for(int count = 0; count < height; ++count)
		delete [] arr_obj[count];
	delete [] arr_obj;
    arr_obj = nullptr;
}
        
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void Input_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 1280;

Key_Input_Notifier Input_Notifier;
Stack_Engine stack(4);

int main()
{
    // fglfw: инициализация и конфигурирование
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // glfw: создание окна
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RPG", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
	//glfwSwapInterval(1); - Turn on vertical synchronization.
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, Input_Callback);
    
    // glad: загрузка всех указателей на OpenGL-функции
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Компилирование нашей шейдерной программы
    Shader ourShader("../res/shaders/shader.vs", "../res/shaders/shader.fs");
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Атрибуты текстурных координат
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	unsigned int VBO_Walls, VAO_Walls;
	glGenVertexArrays(1, &VAO_Walls);
    glGenBuffers(1, &VBO_Walls);

    glBindVertexArray(VAO_Walls);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_Walls);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Координатные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Атрибуты текстурных координат
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // Загрузка и создание текстуры
    unsigned int texture1, texture2;
    // Текстура №1 - Деревянный ящик
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // Установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Загрузка изображения, создание текстуры и генерирование мипмап-уровней
    int width, height, nrChannels;

	stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("../res/textures/enemy.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // установка параметров наложения текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // установка метода наложения текстуры GL_REPEAT (стандартный метод наложения)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Установка параметров фильтрации текстуры
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load("../res/textures/hero.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // Указываем OpenGL какой сэмплер к какому текстурному блоку принадлежит (это нужно сделать единожды)
    ourShader.use(); // не забудьте активировать шейдер перед настройкой uniform-переменных!

	// Устанавливаем вручную…
    glUniform1i(glGetUniformLocation(ourShader.ID, "tex"), 0);
    // …или с помощью шейдерного класса
    ourShader.setInt("texture2", 1);

    srand(static_cast<unsigned int>(time(0)));

    int l_height = getRandomNumber2(4, 7) * 7 + 2;
    int l_width = getRandomNumber2(4, 7) * 7 + 2;
    int l_height2 = getRandomNumber2(4, 7) * 7 + 2;
    int l_width2 = getRandomNumber2(4, 7) * 7 + 2;
    
    Camera_2D Camera_View(0.0f, 0.0f, 0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f, 100.0f);
    WorldMap Tile_Map(SCR_WIDTH, SCR_HEIGHT, l_height, l_width); 
    WorldMap Tile_Map2(SCR_WIDTH, SCR_HEIGHT, l_height2, l_width2);

    char** level_array1 = gen_Random_Level(l_height, l_width);
    int rand_id = getRandomNumber2(1, 4);
    int rand_wall = create_Hole_InWall(level_array1, l_height, l_width, rand_id);
    WorldMap* Pipe = nullptr;
    if(rand_id == 1 || rand_id == 3)
    {
        Pipe = new WorldMap(SCR_WIDTH, SCR_HEIGHT, wall_size1, wall_size2);
    }
    if(rand_id == 2 || rand_id == 4)
    {
        Pipe = new WorldMap(SCR_WIDTH, SCR_HEIGHT, wall_size2, wall_size1);
    }
    char** pipe_ptr = create_Pipe(rand_id);
    Pipe->Initializing(pipe_ptr);

    int offset1 = 0;
    int offset2 = 0;

    set_offset_for_pipe(rand_id, offset1, offset2, rand_wall, l_height, l_width);
    
    int offset1_1 = offset1;
    int offset2_2 = offset2;

    int rand_id_2 = level_in_rand_id(rand_id);
    next_level_offset(&offset1_1, &offset2_2, rand_id_2);
    
    Tile_Map.Initializing(level_array1);

    char** level_array2 = gen_Random_Level(l_height2, l_width2);
    create_hole_inwall_next_level(level_array2, rand_wall, rand_id_2, l_height2, l_width2);
    Tile_Map2.Initializing(level_array2);

    Sprite_RandSet RandSprite(rand_sprite_size, rand_sprite_size);
//    RandSprite.setRandSprite(Array_Sprites_Set, 1);
    Tile_Map.set_RandomSprites(Array_Sprites_Set, RandSprite);
    Tile_Map2.set_RandomSprites(Array_Sprites_Set, RandSprite);
        
    Player_Implementation Player_Hero(450.0f, -150.0f, 2.0f);  // 450.0f, -150.0f
    Input_Notifier.Attach(&Player_Hero);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   	Camera_View.Set_View(ourShader);

   	const int anim_index_array = 3;
	int anim_count = 0;
	float* Vertex_Animation[4][anim_index_array] = {
		{vertices, vertices2, vertices3},
		{vertices4, vertices5, vertices6},
		{vertices7, vertices8, vertices9},
		{vertices10, vertices11, vertices12}
	};
	float Delta_Time = 0;
	float Animation_Delta = 0;
    const int Map_Objects_Row = l_height;
	const int Map_Objects_Col = l_width;

//	const int Map_Objects_Row = map_height;
//	const int Map_Objects_Col = map_width;

	const int Map_Objects_Row2 = l_height2;
	const int Map_Objects_Col2 = l_width2;
    
	Map_Objects** Map_Objects_Pointer = new Map_Objects*[Map_Objects_Row];
	for(int counter = 0; counter < Map_Objects_Row; ++counter)
		Map_Objects_Pointer[counter] = new Map_Objects[Map_Objects_Col];

	Map_Objects** Map_Objects_Pointer2 = new Map_Objects*[Map_Objects_Row2];
	for(int count = 0; count < Map_Objects_Row2; ++count)
		Map_Objects_Pointer2[count] = new Map_Objects[Map_Objects_Col2];

	// Game timer.
	Chrono_Guard Chrono(0.0f, 0.0f, 0.0f);
	Collision Collision;

	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        // Рендеринг
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		Chrono.set_New_Frame_Time();
		Delta_Time = Chrono.get_Delta();
        Process_Input(window, Player_Hero, Delta_Time);

		Tile_Map.Render(Map_Objects_Pointer, ourShader, VAO_Walls, texture1, 0, 0, 3, 0);
		Collision.Detection(Map_Objects_Pointer, Player_Hero, Delta_Time, Tile_Map, SCR_WIDTH, SCR_HEIGHT, window);

        Pipe->Render(Map_Objects_Pointer, ourShader, VAO_Walls, texture1, offset1, offset2, rand_id, 0);
		Collision.Detection(Map_Objects_Pointer, Player_Hero, Delta_Time, *Pipe, SCR_WIDTH, SCR_HEIGHT, window);

        Tile_Map2.Render(Map_Objects_Pointer2, ourShader, VAO_Walls, texture1, offset1_1, offset2_2, 0, rand_id_2);
		Collision.Detection(Map_Objects_Pointer2, Player_Hero, Delta_Time, Tile_Map2, SCR_WIDTH, SCR_HEIGHT, window);

		Camera_View.Set_Position(-Player_Hero.get_xAxis(), -Player_Hero.get_yAxis(), 0.0f, 1.0f);
		Camera_View.Set_View(ourShader);

		// Биндим объект вершинного буфера чтобы получить возможность загрузить новые данные, так как до этого мы анбиндили все объекты данного типа.

		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		if(Player_Hero.getKeyAxis() == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Animation_Delta += Delta_Time;
			if(Animation_Delta > 30.0f)
			{
				switch(anim_count)
				{
					default:
						anim_count = 0;
					case 0:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[0][anim_count], GL_STATIC_DRAW);
						break;
					case 1:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[0][anim_count], GL_STATIC_DRAW);
						break;
					case 2:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[0][anim_count], GL_STATIC_DRAW);
						break;
				}
				++anim_count;
				Animation_Delta = 0;
			}
		}
		else if(Player_Hero.getKeyAxis() == GLFW_KEY_A && glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Animation_Delta += Delta_Time;
			if(Animation_Delta > 30.0f)
			{
				switch(anim_count)
				{
					default:
						anim_count = 0;
					case 0:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][anim_count], GL_STATIC_DRAW);
						break;
					case 1:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][anim_count], GL_STATIC_DRAW);
						break;
					case 2:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[1][anim_count], GL_STATIC_DRAW);
						break;
				}
				++anim_count;
				Animation_Delta = 0;
			}
		}
		else if(Player_Hero.getKeyAxis() == GLFW_KEY_D && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Animation_Delta += Delta_Time;
			if(Animation_Delta > 30.0f)
			{
				switch(anim_count)
				{
					default:
						anim_count = 0;
					case 0:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][anim_count], GL_STATIC_DRAW);
						break;
					case 1:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][anim_count], GL_STATIC_DRAW);
						break;
					case 2:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[2][anim_count], GL_STATIC_DRAW);
						break;
				}
				++anim_count;
				Animation_Delta = 0;
			}
		} 
		else if(Player_Hero.getKeyAxis() == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Animation_Delta += Delta_Time;
			if(Animation_Delta > 30.0f)
			{
				switch(anim_count)
				{
					default:
						anim_count = 0;
					case 0:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][anim_count], GL_STATIC_DRAW);
						break;
					case 1:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][anim_count], GL_STATIC_DRAW);
						break;
					case 2:
						glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), Vertex_Animation[3][anim_count], GL_STATIC_DRAW);
						break;
				}
				++anim_count;
				Animation_Delta = 0;
			}
		}

		Player_Hero.Draw(SCR_WIDTH, SCR_HEIGHT, ourShader, VAO, texture2);

        // glfw: обмен содержимым front- и back- буферов. Отслеживание событий ввода/вывода (была ли нажата/отпущена кнопка, перемещен курсор мыши и т.п.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Опционально: освобождаем все ресурсы, как только они выполнили свое предназначение
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: завершение, освобождение всех выделенных ранее GLFW-реурсов
    glfwTerminate();

	for(int counter2 = 0; counter2 < Map_Objects_Row; ++counter2)
		delete [] Map_Objects_Pointer[counter2];
	delete [] Map_Objects_Pointer;

	for(int counter3 = 0; counter3 < Map_Objects_Row2; ++counter3)
		delete [] Map_Objects_Pointer2[counter3];
	delete [] Map_Objects_Pointer2;

    summon_Destructor3000(level_array1, 23, 37);
//    summon_Destructor3000(level_array2, 16, 24);
    
    return 0;
}

// glfw: всякий раз, когда изменяются размеры окна (пользователем или операционной системой), вызывается данная callback-функция
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Убеждаемся, что окно просмотра соответствует новым размерам окна.
    // Обратите внимание, что высота и ширина будут значительно больше, чем указано, на Retina-дисплеях
    glViewport(0, 0, width, height);
}

void Input_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		stack.Push(key);
		Input_Notifier.Notifier(stack.getElement(), action);
	}
	if (action == GLFW_RELEASE)
	{
		stack.Pop_Search(key);
		Input_Notifier.Notifier(stack.getElement(), action);
	}
}

  
