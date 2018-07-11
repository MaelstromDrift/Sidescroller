#include "Texture.h"
#include <iostream>
#include "Renderer.h"
#include "SDL.h"

namespace Vulture2D {

    Texture::Texture() {
        mTexture = nullptr;
        mWidth = mHeight = 0;
    }
    Texture::~Texture() {
        //mWidth = mHeight = 0;
        std::cout << "destroying Texture" << std::endl;
        if (mTexture) {
            SDL_DestroyTexture(mTexture);
        }
    }
    Texture::Texture(SDL_Texture* texture) {
        mTexture = texture;
    }
    Texture::Texture(string path) {
        SDL_Surface* temp;
        temp = IMG_Load(path.c_str());
        if (!temp) {
            std::cout << "Couldn't load image" << std::endl;
        }
        else {
            mWidth = temp->w;
            mHeight = temp->h;

            mTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), temp);
            SDL_FreeSurface(temp);
        }

    }

    const unsigned int Texture::getWidth() {
        return mWidth;
    }

    const unsigned int Texture::getHeight() {
        return mHeight;
    }

    SDL_Texture* Texture::getTexture() {
        return mTexture;
    }
}