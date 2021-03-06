#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include "MenuScene.h"
#include "DungeonScene.h"
#include "CellScene.h"

#include "SFML/System/Time.hpp"
#include <vector>
#include <string>
#include <iostream>

class SceneManager {
public:
	SceneManager();
	SceneManager(sf::RenderWindow& window);
	~SceneManager();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);

	void SwitchScene(std::string scene);

private:
	Scene* m_currScene;
	std::vector<Scene*> m_scenes;
};

#endif // !SCENEMANAGER_H
