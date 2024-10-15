#include "Subject.h"

void Subject::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void Subject::removeObserver(std::shared_ptr<Observer> observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notifyObservers(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    for (auto& observer : observers) {
        observer->onCameraUpdate(viewMatrix, projectionMatrix);
    }
}
