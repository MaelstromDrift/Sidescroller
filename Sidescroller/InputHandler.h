#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>
#include "EventHandler.h"
#include "Entity.h"

class InputHandler {
public:
    static InputHandler& getInstance();

    void handleInput();
    void addKeyAction(int key, std::string tag);
    void removeKeyAction(int key);
    bool actionTriggered(std::string action);
    bool actionHeld(std::string action);

    bool keyHeld(int key);
    bool keyPressed(int key);
    bool keyReleased(int key);

private:
    ~InputHandler() { if (instance) { delete instance; } instance = nullptr; }
    InputHandler() {}
    InputHandler(InputHandler const&) {}
    InputHandler& operator=(InputHandler const& e) {}

    SDL_Event mEvent;
    static InputHandler* instance;

    std::unordered_map<int, bool> mPressedKeys;
    std::unordered_map <int, bool> mHeldKeys;
    std::unordered_map <int, bool> mReleasedKeys;

    std::unordered_map<int, std::string> mKeyMap;
    std::unordered_map<std::string, int> mActionMap;
};