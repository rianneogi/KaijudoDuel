#include "DuelInterface.h"

const int MAX_FPS = 60;

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

const float ZOOM_MIN = 8.f;
const float ZOOM_MAX = 20.f;

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

Model gTableModel;
Camera gCamera;
DuelInterface* gDuelInterface;

float gZoomDistance = 16.f;
const float gCameraSpeed = 0.0001f;

bool initSDL()
{
	const GLubyte* glVersion(glGetString(GL_VERSION));
	printf("OpenGL max version supported: %s\n", glVersion);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		_getch();
	}

	//Initialize DevIL
	ilInit();
	ilClearColour(255, 255, 255, 000);

	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		printf("Error initializing DevIL! %s\n", iluErrorString(ilError));
		_getch();
	}

	gWindow = SDL_CreateWindow("Kaijudo Duel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		_getch();
	}

	//SDL_WarpMouseInWindow(gWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	///*SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);*/
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	gContext = SDL_GL_CreateContext(gWindow);
	if (gContext == NULL)
	{
		printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		_getch();
	}
	SDL_GL_MakeCurrent(gWindow, gContext);
	glEnable(GL_MULTISAMPLE);

	return true;
}

bool initGL()
{
	//Initialize GLEW
	//glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return false;
	}

	//Make sure OpenGL 3.1 is supported
	if (!GLEW_VERSION_3_1)
	{
		printf("OpenGL 3.1 not supported!\n");
		//return false;
	}

	if (!GLEW_ARB_vertex_program)
	{
		printf("ARB not supported\n");
		_getch();
	}

	if (!GLEW_ARB_framebuffer_object)
	{
		printf("framebuffer objects not supported\n");
		_getch();
	}

	//Set the viewport
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Initialize clear color
	glClearColor(0, 0, 0, 1);

	//Enable texturing
	//glEnable(GL_TEXTURE_2D);
	//glEnable(GL_TEXTURE_3D);
	//glEnable(GL_TEXTURE_CUBE_MAP);

	//Depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		_getch();
		return false;
	}

	return true;
}

bool initGame()
{
	if (!initCards())
	{
		printf("ERROR initializing cards\n");
		return false;
	}

	gTableModel.setMesh(&gMeshs[MESH_TABLE]);
	gTableModel.setTexture(&gTableTexture);
	gTableModel.setPosition(glm::vec3(0, 0, 0));
	gTableModel.mModelMatrix = glm::scale(gTableModel.mModelMatrix, glm::vec3(3, 3, 3));

	gCamera.setPosition(glm::vec3(0, 0, 0));
	gCamera.setHorizontalAngle(0);
	gCamera.setVerticalAngle(-M_PI/2);
	gCamera.update();
	gCamera.mPosition = -gCamera.mDirection * gZoomDistance;
	gCamera.update();

	gDuelInterface = new DuelInterface();
	ActiveDuel = &(gDuelInterface->duel);
	ActiveDuel->setDecks("Decks\\My Decks\\LFN Starter Deck.txt", "Decks\\My Decks\\FL Burning Light Base Set.txt");
	ActiveDuel->startDuel();
	ActiveDuel->dispatchAllMessages();

	return true;
}

void cleanup()
{
	cleanupCards();
}

void handleEvent(const SDL_Event& e, unsigned int deltaTime)
{
	glm::vec3 dir = gCamera.mDirection;

	// Movement
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			//gCamera.direction = glm::rotate(gCamera.direction, gCameraSpeed*deltaTime, glm::vec3(0, 0, 1));
			gCamera.setVerticalAngle(gCamera.verticalAngle - gCameraSpeed*deltaTime);
			gCamera.update();
			gCamera.mPosition = -gCamera.mDirection * gZoomDistance;
			gCamera.update();
			//mCamera.position += dir * (deltaTime * gSpeed);
		}

		if (e.key.keysym.sym == SDLK_s)
		{
			gCamera.setVerticalAngle(gCamera.verticalAngle + gCameraSpeed*deltaTime);
			gCamera.update();
			gCamera.mPosition = -gCamera.mDirection * gZoomDistance;
			gCamera.update();
		}

		if (e.key.keysym.sym == SDLK_a)
		{
			gCamera.setHorizontalAngle(gCamera.horizontalAngle - gCameraSpeed*deltaTime);
			gCamera.update();
			gCamera.mPosition = -gCamera.mDirection * gZoomDistance;
			gCamera.update();
		}

		if (e.key.keysym.sym == SDLK_d)
		{
			gCamera.setHorizontalAngle(gCamera.horizontalAngle + gCameraSpeed*deltaTime);
			gCamera.update();
			gCamera.mPosition = -gCamera.mDirection * gZoomDistance;
			gCamera.update();
		}
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		gZoomDistance += e.wheel.y;
		if (gZoomDistance < ZOOM_MIN)
		{
			gZoomDistance = ZOOM_MIN;
		}
		if (gZoomDistance > ZOOM_MAX)
		{
			gZoomDistance = ZOOM_MAX;
		}
		gCamera.mPosition = -gCamera.mDirection * gZoomDistance;
		gCamera.update();
	}
}

void render()
{
	glm::mat4 view, projection;
	gCamera.render(view, projection);
	gActiveShader = SHADER_BASIC;
	gShaders[gActiveShader].bind();
	gShaders[gActiveShader].setUniformMat4f(0, gTableModel.mModelMatrix);
	gShaders[gActiveShader].setUniformMat4f(1, view);
	gShaders[gActiveShader].setUniformMat4f(2, projection);
	gTableModel.render();
	Vector2i mpos;
	SDL_GetMouseState(&mpos.x, &mpos.y);
	gDuelInterface->render(gCamera, mpos);
}

void update(int deltaTime)
{
	Vector2i mpos;
	SDL_GetMouseState(&mpos.x, &mpos.y);
	gDuelInterface->update(deltaTime, gCamera, mpos);
}

void mainLoop()
{
	bool running = true;
	SDL_Event e;

	//sf::Clock FPSTimer;
	//Uint32 time = SDL_GetTicks();
	Timer timer;
	unsigned int frameCount = 0;
	while (running)
	{
		// handle events
		//sf::Event event;
		//while (gWindow.pollEvent(event))

		//sf::Int64 deltaTime = gTimer.getElapsedTime().asMicroseconds();
		//gTimer.restart();
		//Uint32 deltaTime = SDL_GetTicks() - time;
		Uint32 deltaTime = timer.getElaspedTime();
		//time = SDL_GetTicks();

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				// end the program
				running = false;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					running = false;
				}
			}
			//else if (e.type == SDL_WINDOWEVENT)
			//{
			//	// adjust the viewport when the window is resized
			//	SCREEN_WIDTH = event.size.width;
			//	SCREEN_HEIGHT = event.size.height;
			//	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			//}
			handleEvent(e, deltaTime);
			//break;
		}
		update(deltaTime);
		//gTimer.restart();

		// clear the buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// draw...
		render();

		//glBindFramebuffer(GL_FRAMEBUFFER, gWorld->mShadowMap.mFBO);

		// end the current frame (internally swaps the front and back buffers)
		//gWindow.display();
		SDL_GL_SwapWindow(gWindow);

		frameCount++;
		//sf::Int32 t = FPSTimer.getElapsedTime().asMilliseconds();
		//Uint32 t = SDL_GetTicks() - time;
		Uint32 t = timer.getElaspedTime();
		if (t >= 1000)
		{
			//FPSTimer.restart();
			//time = SDL_GetTicks();
			timer.restart();
			printf("FPS: %d\n", frameCount);
			frameCount = 0;
		}
		while (frameCount*(1000.f / MAX_FPS) > t)
		{
			//t = FPSTimer.getElapsedTime().asMilliseconds();
			//t = SDL_GetTicks() - time;
			t = timer.getElaspedTime();
		}
	}
}

int main(int argc, char* args[])
{
	if (!initSDL())
	{
		printf("ERROR initializing SDL\n");
		_getch();
	}

	if (!initGL())
	{
		printf("ERROR initializing Opengl\n");
		_getch();
	}

	//Use Vsync
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	if (!loadResources())
	{
		printf("ERROR loading resources\n");
		_getch();
	}

	if (!initGame())
	{
		printf("ERROR initializing game\n");
		_getch();
	}

	mainLoop();

	cleanup();

	return 0;
}