#include "Player.h"
#include <string>
#include <iostream>
#include "Projectile.h"
#include "InputHandler.h"
#include "SceneHandler.h"
int speed = 15;
Player::Player(int x, int y, int width, int height) {
    mPos.x = x;
    mPos.y = y;
    mHalfWidth = width/2;
    mHalfHeight = height/2;

	EventHandler::getInstance().listenEvent("fire_bullet", getName(), std::bind(&Player::fireBullet, this, std::placeholders::_1));
}
void Player::update() {
    handleInput();

    mPos.x += mVelocity.x;
    mPos.y += mVelocity.y;
}

void Player::handleInput() {
    if (InputHandler::getInstance().actionTriggered("move_right")) {
        mVelocity.x = speed;
    } else if (InputHandler::getInstance().actionTriggered("move_left")) {
        mVelocity.x = -speed;
    } else {
        mVelocity.x = 0;
    }

    if (InputHandler::getInstance().actionTriggered("move_up")) {
        mVelocity.y = -speed;
    } else if (InputHandler::getInstance().actionTriggered("move_down")) {
        mVelocity.y = speed;
    } else {
        mVelocity.y = 0;
    }
}

void Player::fireBullet(int val) {
	Projectile* bullet = new Projectile(mPos.x, mPos.y, 10, 10, Vector2D(10,0));
	bullet->createFromPath("images/block.png");
	bullet->setName("bullet");
	bullet->setLayer(1);
	bullet->setTrigger(true);
	SceneHandler::getInstance().getCurrentScene()->registerEntity(bullet);
}

void Player::setPosition(int x, int y) {
    mRect.x = x;
    mRect.y = y;

    mPos.x = x;
    mPos.y = y;
    mHalfHeight = 32;
    mHalfWidth = 32;
}

void Player::render(SDL_Rect* cameraRect) {
    SDL_Rect destRect;
    destRect.x = mPos.x - mHalfWidth - cameraRect->x;
    destRect.y = mPos.y - mHalfHeight - cameraRect->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;
    Renderer::getInstance().drawTexture(getTexture(), &destRect);
}

void Player::handleCollision(std::string name, AABBCollider col) {
    while (!mColliders.empty()) {
        //Skip collision resolution if we are colliding with a trigger
        if (mColliders.at(0)->isTrigger()) {
            mColliders.erase(mColliders.begin());
            continue;   
        }
        //Determine the collider that provides the greatest impact on this entity
        double greatest = 0;
        int greatestIndex = 0;
        for (int i = 0; i < mColliders.size(); i++) {
            double temp = getInterArea(*mColliders.at(i));
            if (i == 0) {
                greatest = temp;
            } else if (temp > greatest) {
                greatestIndex = i;
                greatest = temp;
            }
        }
        mPos = mPos + getProjectionVector(*mColliders.at(greatestIndex));
        mColliders.erase(mColliders.begin() + greatestIndex);
    }
}

void Player::updateAABB() {
    mPos.x = mRect.x + mHalfWidth;
    mPos.y = mRect.y + mHalfHeight;
}   
