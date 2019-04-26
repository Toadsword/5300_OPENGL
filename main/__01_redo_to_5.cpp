/*
 MIT License

 Copyright (c) 2017 SAE Institute Switzerland AG

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include <iostream>
#include <engine.h>
#include <graphics.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TestProgram : public DrawingProgram
{
public:
	void Init() override;
	void Draw() override;
	void Destroy() override;
private:
	void ProcessInput();

	unsigned VAO;
	unsigned VBO;
	float vertices[36 * 5] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	glm::vec3 cubePositions[10] =
	{
		glm::vec3(-20.0f,  20.0f, -10.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader shaderProgram;

	GLuint textureStar;
};

void TestProgram::Init()
{
	programName = "BabaIsNotYou";

	Engine* engine = Engine::GetPtr();
	auto& config = engine->GetConfiguration();

	shaders.push_back(&shaderProgram);

	shaderProgram.CompileSource(
		"shaders/__01_redo_to_5/vert.vert",
		"shaders/__01_redo_to_5/frag.frag"
	);
	textureStar = stbCreateTexture("data/sprites/star.png");

	glGenBuffers(1, &VBO); //like new VBO()
	glGenVertexArrays(1, &VAO); // like new VAO()

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void TestProgram::Draw()
{
	ProcessInput();

	glEnable(GL_DEPTH_TEST);
	Engine* engine = Engine::GetPtr();
	Configuration& config = engine->GetConfiguration();

	glm::mat4 view = engine->GetCameraManager().GetViewMatrix();

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)config.screenWidth / config.screenHeight, 0.1f, 100.0f);

	shaderProgram.Bind();
	glBindTexture(GL_TEXTURE_2D, textureStar);
	glBindVertexArray(VAO);
	int viewLoc = glGetUniformLocation(shaderProgram.GetProgram(), "view");//camera transform matrix
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	int projectionLoc = glGetUniformLocation(shaderProgram.GetProgram(), "projection");//projection matrix
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	for (int i = 0; i < 10; i++)
	{
		glm::mat4 model = glm::mat4(1.0f); //model transform matrix
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, glm::radians(engine->GetTimeSinceInit()*45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(engine->GetTimeSinceInit()*45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		int modelLoc = glGetUniformLocation(shaderProgram.GetProgram(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36); // 36 est le nombre de points pour le cube
	}
}

void TestProgram::Destroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void TestProgram::ProcessInput()
{
	Engine * engine = Engine::GetPtr();
	auto& camera = engine->GetCameraManager();
	auto& inputManager = engine->GetInputManager();

#ifdef USE_SDL2
	if (inputManager.GetButton(SDLK_w))
	{
		camera.ProcessKeyboard(FORWARD, engine->GetDeltaTime());
	}
	if (inputManager.GetButton(SDLK_s))
	{
		camera.ProcessKeyboard(BACKWARD, engine->GetDeltaTime());
	}
	if (inputManager.GetButton(SDLK_a))
	{
		camera.ProcessKeyboard(LEFT, engine->GetDeltaTime());
	}
	if (inputManager.GetButton(SDLK_d))
	{
		camera.ProcessKeyboard(RIGHT, engine->GetDeltaTime());
	}
#endif

	auto mousePos = inputManager.GetMousePosition();

	camera.ProcessMouseMovement(mousePos.x, mousePos.y, true);

	camera.ProcessMouseScroll(inputManager.GetMouseWheelDelta());
}

int main(int argc, char **argv)
{
	Engine engine;

	auto& config = engine.GetConfiguration();
	config.screenWidth = 1024;
	config.screenHeight = 1024;
	//config.bgColor = sf::Color::Black;
	config.windowName = "Hello Texture";
	
	engine.AddDrawingProgram(new TestProgram());
	engine.Init();
	engine.GameLoop();
	return EXIT_SUCCESS;
}
