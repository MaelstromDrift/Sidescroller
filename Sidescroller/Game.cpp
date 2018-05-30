#include "Game.h"

namespace Vulture2D {
    void Game::init() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL could not initialize!\n" << SDL_GetError() << std::endl;
        }
        if (IMG_Init(IMG_INIT_PNG) < 0) {
            std::cerr << "SDL_Img could not be initialized!\n" << IMG_GetError() << std::endl;
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "SDL_mixer could not initialize!\n" << Mix_GetError() << std::endl;
        }

        window = SDL_CreateWindow("Sidescroller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

        Renderer::getInstance().init(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        screenSurface = SDL_GetWindowSurface(window);

        running = true;
    }

    void Game::run() {
        //TODO: Should probably create a timer class to keep track of time instead of just always using SDL_GetTicks() and doing the checks 
        double deltaTime = 16.667;

        double currentTime = SDL_GetTicks();
        double backlog = 0;

        int fpsCounter = 0;
        int updateCounter = 0;

        double fpsTimerStart = SDL_GetTicks();
        double updateTimerStart = SDL_GetTicks();

        while (running) {
            double newTime = SDL_GetTicks();
            double frameTime = newTime - currentTime;

            currentTime = newTime;
            backlog += frameTime;

            while (backlog >= deltaTime) {
                InputHandler::getInstance().handleInput();
                SceneHandler::getInstance().getCurrentScene()->updateScene();
                backlog -= deltaTime;
                updateCounter++;
            }
            if ((currentTime - fpsTimerStart) >= 1000) {
                std::cout << fpsCounter << " " << updateCounter << std::endl;
                fpsCounter = 0;
                updateCounter = 0;
                fpsTimerStart = currentTime;
                updateTimerStart = currentTime;
            }

            SceneHandler::getInstance().getCurrentScene()->renderScene();
            fpsCounter++;

            //TODO: Not sure if this is a good way for checking when to end the game loop, it seems sketchy though.
            if (InputHandler::getInstance().actionHeld("quit_game"))
                running = false;
        }
    }

    void Game::registerInputs() {
        //TODO: Should really verify this is how I actually want InputHandler and EventHandler to work.
        InputHandler::getInstance().addKeyAction(SDLK_ESCAPE, "quit_game");

        //EventHandler::getInstance().subscribeToEvent("quit_game", "main", std::bind(&quitGame, std::placeholders::_1));
        InputHandler::getInstance().addKeyAction(SDLK_RIGHT, "move_right");
        InputHandler::getInstance().addKeyAction(SDLK_LEFT, "move_left");
        InputHandler::getInstance().addKeyAction(SDLK_t, "test_scene");
        InputHandler::getInstance().addKeyAction(SDLK_SPACE, "jump");

        //InputHandler::getInstance().addKeyAction(SDLK_m, music->getMuteActionName());
        //InputHandler::getInstance().addKeyAction(SDLK_MINUS, music->getVolumeLowerActionName());
        //InputHandler::getInstance().addKeyAction(SDLK_EQUALS, music->getVolumeHigherActionName());
    }

    void Game::destroy() {
        SceneHandler::getInstance().getCurrentScene()->destroy();

        SDL_FreeSurface(screenSurface);
        screenSurface = nullptr;

        SDL_DestroyWindow(window);
        window = nullptr;

        IMG_Quit();
        SDL_Quit();
    }
}