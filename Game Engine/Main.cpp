


#define GLEW_STATIC
#include <GL/glew.h>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>

#include <vector>
#include <stdio.h>
#include "InputManager.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "windows.h"
#include <iostream>
#include "PhysicManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"
#include "GameObject.h"
// include all component headers here
#include "Transform.h"
#include "Sprite.h"
#include "Component.h"
#include "Controller.h"
#include "ObjectFactory.h"
#include "Body.h"
#include "EventManager.h"
#include "Shader.h"
#include "StateManager.h"
#include "ObjectName.h"


#define MAXFRAMERATE 60 // 0 is unlocked

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
GLFWwindow* gpWindow = nullptr;
// declaring global variables
InputManager* gpInputManager = nullptr;
ResourceManager* gpResourceManager = nullptr;
FrameRateController* pFrameRateController = nullptr;
GameObjectManager* gpGoManager = nullptr;
ObjectFactory* gpObjectFactory = nullptr;
PhysicManager* gpPhysicManager = nullptr;
CollisionManager *gpCollisionManger = nullptr;
EventManager *gpEventManager = nullptr;
StateManager *gpStateManager = nullptr;
//EventManager *gpEventManager = nullptr;

#pragma comment(lib, "legacy_stdio_definitions.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings

float SCR_WIDTH ;
float SCR_HEIGHT;

int main(int argc, char* args[])
{
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	
	
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = 1820;
	SCR_HEIGHT = 980;

	
	
	gpWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Asteroid", nullptr, nullptr);
	glfwMakeContextCurrent(gpWindow);

	glewInit();
	glewExperimental = GL_TRUE;
	
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}

	std::cout << SCR_WIDTH << "\n";
	std::cout << SCR_HEIGHT << "\n";

	 gpResourceManager = new ResourceManager();
	 gpInputManager = new InputManager();
	 pFrameRateController = new FrameRateController(30);
	 gpGoManager = new GameObjectManager();
	 gpObjectFactory = new ObjectFactory();
	 gpPhysicManager = new  PhysicManager();
	 gpCollisionManger = new CollisionManager();
	 gpEventManager = new EventManager();
	 gpStateManager = new StateManager();
	// gpEventManager = new EventManager();
	Uint32 posX = 0, posY = 0;
	//SDL_Surface *pMainCharacter = NULL;

	int error = 0;
	bool appIsRunning = true;
	
	
    gpObjectFactory->LoadLevel("Menu\\Menu.txt");
	int prev_State = 0;
	//SDL_UpdateWindowSurface(pWindow);
	Shader shader("vertex.vs", "fragment.frag");
	Shader shaderColor("vertexColor.vs", "fragmentColor.frag");
	glm::mat4 Projection = glm::ortho(0.0f, SCR_WIDTH, SCR_HEIGHT, 0.0f, -5.0f, 5.0f);
	// Game loop
	while (true == appIsRunning)
	{


		pFrameRateController->FrameStart();
		if (gpStateManager->Change_Shader == 0)
		{
			shader.use();
		}
		else
		{
			
			shaderColor.use();
		}
		
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(Projection));



		glfwPollEvents();

		glClearColor(0.0, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		gpStateManager->Update();
		if (prev_State != gpStateManager->state_tracker)
		{
			if (gpStateManager->state_tracker == MENUSTATE)
			{
				gpObjectFactory->LoadLevel("Menu\\Menu.txt");
			}
			else if (gpStateManager->state_tracker == CONTROLLS)
			{
				
					
				gpObjectFactory->LoadLevel("Controls\\Controls.txt");
			}
			else if (gpStateManager->state_tracker == LEVEL_SELECT)
			{

				
				gpObjectFactory->LoadLevel("LevelSelect\\LevelSelect.txt");
				
				
				
			
			}
			else if (gpStateManager->state_tracker == LEVEL_1)
			{


				gpObjectFactory->LoadLevel("Level1\\Level1.txt");
			}
			else if (gpStateManager->state_tracker == LEVEL_2)
			{


				gpObjectFactory->LoadLevel("Level2\\Level2.txt");
			}
			else if (gpStateManager->state_tracker == LEVEL_3)
			{


				gpObjectFactory->LoadLevel("Level3\\Level3.txt");
			}
			else if (gpStateManager->state_tracker == LEVEL_4)
			{


				gpObjectFactory->LoadLevel("Level4\\Level4.txt");
			}
			else if (gpStateManager->state_tracker == Game_OVER)
			{
				if (gpStateManager->win_lose == 1)
				{
					gpObjectFactory->LoadLevel("GameOver\\GameOver1.txt");
				}
				else if (gpStateManager->win_lose == 2)
				{
					gpObjectFactory->LoadLevel("GameOver\\GameOver2.txt");
				}

				
			}
			
				
			prev_State = gpStateManager->state_tracker;
		}
		else
		{
			gpInputManager->Update();

			float frameTime = (float)(pFrameRateController->GetFrameTime());
			//	printf("FrameTime: %u\n", frameTime);
			gpPhysicManager->Update(frameTime);
			gpEventManager->Update(frameTime);

			std::vector<GameObject*>::iterator it =gpGoManager->mGameObjects.begin();
			int size = gpGoManager->mGameObjects.size();
			for(int i=0;i<size;++i)
			{
				auto go = gpGoManager->mGameObjects[i];
				if (go == nullptr)
				{
					continue;
				}
				go->Update();

			}
			
			// Draw
			 it = gpGoManager->mGameObjects.begin();
			size = gpGoManager->mGameObjects.size();
			for (int i = 0; i<size; ++i)
			{
				auto go = gpGoManager->mGameObjects[i];
				if (go == nullptr)
				{
					continue;
				}
			
				
				if (go == nullptr)
				{
					
					continue;
				}
				Transform* pTr = static_cast<Transform*>(go->GetComponent(TRANSFORM));
				if (pTr == nullptr)
					continue;

				Sprite* pSp = static_cast<Sprite*>(go->GetComponent(SPRITE));
				
				if (gpStateManager->Change_Shader == 0)
				{
					GLuint transformLoc = glGetUniformLocation(shader.ID, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(pTr->mpTransform));
				}
				else
				{
					GLuint transformLoc = glGetUniformLocation(shaderColor.ID, "transform");
					glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(pTr->mpTransform_bounding_box));
					
				}
				

				if (pSp == nullptr)
				{
					continue;
				}
				else
				{
					pSp->DrawMesh();
				}
					
				//	//Draw Object
				


			}
		}
		

		
				//SDL_UpdateWindowSurface(pWindow);
		
		
		
		int size = gpGoManager->delete_GameObjects.size();
		for (int i = 0; i < size; ++i)
		{
		
			std::vector<GameObject*>::iterator it = std::find(gpGoManager->mGameObjects.begin(), gpGoManager->mGameObjects.end(), gpGoManager->delete_GameObjects[i]);

			if (it != gpGoManager->mGameObjects.end())
			{
				gpGoManager->mGameObjects.erase(it);
			}
		}

		gpGoManager->delete_GameObjects.clear();
		int aster_count = 0;
		int enemy_ship_count = 0;

		std::vector<GameObject*>::iterator it = gpGoManager->mGameObjects.begin();
		 size = gpGoManager->new_GameObjects.size();
		for (int i = 0; i<size; ++i)
		{
			auto go = gpGoManager->new_GameObjects[i];
			gpGoManager->mGameObjects.push_back(go);

			
		}

		

		gpGoManager->new_GameObjects.clear();



		size = gpGoManager->mGameObjects.size();
		for (int i = 0; i < size; ++i)
		{

			auto go = gpGoManager->mGameObjects[i];

			ObjectName* pObj_Name = static_cast<ObjectName *>(go->GetComponent(NAME));
			if (pObj_Name->mType_Name == ASTEROID)
			{
				aster_count += 1;
			}
			else if (pObj_Name->mType_Name == ENEMY_SHIP)
			{
				enemy_ship_count += 1;
			}
		}

		glfwSwapBuffers(gpWindow);
		pFrameRateController->FrameEnd();
		std::cout << aster_count + enemy_ship_count <<std::endl;
		if(aster_count + enemy_ship_count<=0&&gpStateManager->enemy_count<=40)
		{
			gpStateManager->enemy_count = 0;;
		}
		else
		{
			if(gpStateManager->enemy_count>40)
			gpStateManager->enemy_count -= 1;
		}
		

	}



	// free the managers
	delete gpEventManager;
	delete gpCollisionManger;
	delete gpPhysicManager;
	delete(gpInputManager);
	delete(pFrameRateController);
	delete(gpResourceManager);
	delete gpGoManager;
	delete gpObjectFactory;
	delete gpStateManager;
	// Close and destroy the window
	//SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	//SDL_Quit();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}