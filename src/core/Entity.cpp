#include "Entity.h"

namespace Vulture2D {

    int Entity::nextValidID = 0;

    Entity::~Entity() {
        std::cout << "Deleteing Entity " << id << " " << name << std::endl;
    }

    void Entity::setID(int id) {
        this->id = id;
    }
    
    void Entity::setName(string name) {
        this->name = name;
    }

    int Entity::getID() {
        return id;
    }
    
    int Entity::getNextValidID() {
        return nextValidID;
    }

    string Entity::getName() {
        return name;
    }
}