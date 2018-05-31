#include "core/SceneHandler.h"
#include "core/Scene.h"
#include "core/Game.h"

#include "entities/Player.h"
#include "entities/Box.h"
#include "entities/Camera.h"
#include "entities/Audio.h"
#include "entities/ResetBox.h"

#include "util/TiledParser.h"

using namespace Vulture2D;
//TODO: Should define a consistent unit of measurement instead of just using pixel size
void initializeEntities();

Player* player;
Camera* camera;

ResetBox* reset;
Scene scene;

//Music* music = nullptr;

Game* game = nullptr;

int main(int argc, char* argv[]) {
    
    game = new Game();

    game->init();

    //TODO: the following should be part of a default loaded scene to keep Main simple.
    initializeEntities();

    game->registerInputs();

    scene.setName("start");
    scene.registerEntity(player);
    scene.setCamera(camera);
    //music->subscribeToEvents();
    scene.registerEntity(reset);

    SceneHandler::getInstance().registerScene(&scene);

    game->run();
    game->destroy();

    return 0;
}

void initializeEntities() {
    //TODO: Should probably make player a unique entity that will only ever have one copy
    player = new Player(64, 300, 64, 64);

    player->setName("Player");
    player->createFromPath("resources/images/ball.png");

    TiledParser::parse("Level1.tmx", "resources/tilesets/", &scene);

    camera = new Camera();

    reset = new ResetBox(-1000, 1500, 10000, 128);
    reset->setName("reset_box");
    reset->setTrigger(true);

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1280;
    cameraRect->h = 720;
    camera->setCameraRect(cameraRect);
    camera->setParentPos(player->getPos());
}