#include "Engine.h"
#include "Mouse.h"
#include "Keyboard.h"

int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow* Engine::window = nullptr;
float Engine::dt = 0;
//in here we initialize the engine that runs the flappy bird like game (constructor and deconstructor
Engine::Engine()
{

}

Engine::~Engine()
{

}


bool Engine::Initialize(const char* windowTitle)//here is the initialization with GLFW, creating the window and swapping the buffers
{
	if (!glfwInit())
	{
		cout << "Error initializing GLFW" << endl;
		return false;
	}

	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
	if (window == NULL)
	{
		cout << "Error creating window" << endl;
		return false;
	}

	//GLFW Setup
	glfwMakeContextCurrent(window);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSwapInterval(1);

	glfwSetCursorPosCallback(window, Mouse::MousePosCallBack);
	glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallBack); //getting the call backs for the cursor, mouse and key to use them
	glfwSetKeyCallback(window, Keyboard::KeyCallBack);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos = (mode->width - SCREEN_WIDTH) / 2;
	int yPos = (mode->height - SCREEN_HEIGHT) / 2;
	glfwSetWindowPos(window, xPos, yPos);

	//GL Setup
	//Viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	//Alpha blending
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	lastTime = (float)glfwGetTime();

	return true;
}

void Engine::Update()
{
	float now = (float)glfwGetTime();//engine update method so anything we change is done here
	dt = (now - lastTime);
	lastTime = now;
	glfwPollEvents();
}

void Engine::BeginRender()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender()
{
	glfwSwapBuffers(window);
}

float Engine::getDT()
{
	return dt;//dt is delta time, more or less
}
