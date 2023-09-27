#pragma once

#include "Layer.h"

#include <map>

class Application
{
private:
	std::shared_ptr<Layer> currentLayer;

	std::shared_ptr<Layer> pendingLayer;

	sf::Clock deltaClock;
public:
	std::map<sf::Keyboard::Key, bool> keyPressedMap;
	sf::RenderWindow* window;
	sf::RenderTexture renderTexture;
	float deltaTime;

	static const float zoomModifier;

	static Application* instance;
public:
	void start();

	void update();
	void draw();

	void onQuit();

	void pushLayer(std::shared_ptr<Layer> layer);
	void popLayer();
};