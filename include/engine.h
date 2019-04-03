#pragma once

#include <functional>
#include <vector>
#include <string>

#ifdef USE_SDL2

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#ifdef WIN32
#include <SDL_main.h>
#endif
#endif

#include <chrono>
#include <input.h>

class DrawingProgram;


#ifdef USE_SDL2
typedef SDL_Color Color;
using ms = std::chrono::duration<float, std::milli>;
#endif

struct Configuration
{
	unsigned int screenWidth = 800;
	unsigned int screenHeight = 600;
	int vsync = 0;
	Color bgColor = {0,0,0,0};

	std::string windowName = "OpenGL";
};

class Engine
{
public:
	Engine();
	~Engine();
	void Init();
	void GameLoop();

	void UpdateUi();

	float GetDeltaTime();
	float GetTimeSinceInit();

	Configuration& GetConfiguration();
	InputManager& GetInputManager();
	void AddDrawingProgram(DrawingProgram* drawingProgram);


	static Engine* GetPtr();
private:
	void SwitchWireframeMode();
	static Engine* enginePtr;


#ifdef USE_SDL2

	void Loop();
	SDL_Window* window = nullptr;
	SDL_GLContext glContext;
	std::chrono::high_resolution_clock timer;

	std::chrono::high_resolution_clock::time_point engineStartTime;
	std::chrono::high_resolution_clock::time_point previousFrameTime;
	float dt;
#endif
	std::vector<DrawingProgram*> drawingPrograms;
	InputManager inputManager;
	Configuration configuration;

	int selectedDrawingProgram = -1;
	bool wireframeMode = false;
	bool debugInfo = true;
	bool drawingProgramsHierarchy = true;
	bool inspector = true;
	bool enableImGui = true;
	bool running = false;
};

