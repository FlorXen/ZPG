#pragma once

#include "Subject.h"
#include "LightSource.h"
#include "Observer.h"
#include "Camera.h"

class Flashlight : public LightSource, public Observer, public std::enable_shared_from_this<Flashlight>
{
public:
	Flashlight(std::shared_ptr<Camera> camera);

	void initializeObserver();

	void onCameraUpdate() override;
	void onLightSourceUpdate() override;

	std::shared_ptr<LightSource> lightSource;
	std::shared_ptr<Camera> camera;
};

