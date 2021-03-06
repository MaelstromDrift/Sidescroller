#pragma once
#include "../core/SceneHandler.h"
#include "../core/Entity.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"
#include "../core/Sound.h"
#include "../core/Game.h"
#include <iostream>

class Projectile : public Vulture2D::Entity, public Vulture2D::Renderable, public AABBCollider {
public:
	Projectile(double x, double y, int w, int h, Vector2D velocity) : AABBCollider(x,y,w,h), sound(Game::getAssetManager().getSound("bullet")) {
        std::swap(this->velocity, velocity);
        Game::getSoundMixer().playSound(&sound);
        startPosition.x = x;
        startPosition.y = y;
        trigger = true;
    };

    virtual ~Projectile() {
    }

    void destroy();
	void update();
	virtual void handleCollisions(AABBCollider*);
	void render(SDL_Rect*);

private:
    Vector2D startPosition;
    Sound sound;

};
