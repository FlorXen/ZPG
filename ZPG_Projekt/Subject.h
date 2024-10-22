#pragma once

#include <glm/mat4x4.hpp> // glm::mat4
#include <vector>
#include "Observer.h"
#include <memory>

class Subject {
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    void notifyObservers();

protected:
    std::vector<std::shared_ptr<Observer>> observers;
};
