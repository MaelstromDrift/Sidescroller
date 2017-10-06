#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>

#include "CollisionHandler.h"
#include "InputHandler.h"

#include "Player.h"
#include "Box.h"
#include "Scene.h"

void initializeEntities();
void registerInputs();
void shutdown();

//SDL specific pointers
SDL_Window* window = nullptr;
SDL_Surface* screenSurface = nullptr;
CollisionHandler* collisionHandler = nullptr;

//Entities
Player* player;
Box* box;
TiledMap* map;
Camera* camera;

Scene scene;

bool running = true;

int main(int argc, char* argv[]) {
    collisionHandler = new CollisionHandler();
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        //error
    }
    if (IMG_Init(IMG_INIT_PNG)) {

    }

    window = SDL_CreateWindow("Sidescroller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1280, SDL_WINDOW_SHOWN);

    Renderer::getInstance().init(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenSurface = SDL_GetWindowSurface(window);

    registerInputs();
    initializeEntities();

    scene.setTiledMap(map);
    scene.registerEntity(player);
    scene.setCamera(camera);
    //scene.registerEntity(box);

    while (!InputHandler::getInstance().actionTriggered("SDL_QUIT")) {
        InputHandler::getInstance().handleInput();
        scene.updateScene();
    }

    shutdown();
    return 0;
}

void shutdown() {
    delete collisionHandler;

    SDL_FreeSurface(screenSurface);
    screenSurface = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}
void initializeEntities() {
    player = new Player();
    box = new Box();

    player->setName("Player");
    player->setDimensions(Vector2D(64, 64));
    player->createFromPath("images/ball.png");
    player->setLayer(1);

    box->setName("Box");
    box->setDimensions(Vector2D(64, 64));
    box->createFromPath("images/block.png");
    box->setLayer(1);

    Collidable* tempCollidable = dynamic_cast<Collidable*>(player);
    collisionHandler->registerCollider(tempCollidable);

    tempCollidable = dynamic_cast<Collidable*>(box);
    collisionHandler->registerCollider(tempCollidable);

    map = new TiledMap(15,10,128,128);
    map->setTileSheet("images/tilesheet_complete_2X.png");
    map->parseFile("tilesets/test_level.tmx");

    camera = new Camera();

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1920;
    cameraRect->h = 1080;
    camera->setCameraRect(cameraRect);
    camera->setParentRect(player->getRect());
}

void registerInputs() {
    InputHandler::getInstance().addKeyAction(SDLK_RIGHT, "move_right");
    InputHandler::getInstance().addKeyAction(SDLK_LEFT, "move_left");
    InputHandler::getInstance().addKeyAction(SDLK_UP, "move_up");
    InputHandler::getInstance().addKeyAction(SDLK_DOWN, "move_down");
}