#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

typedef std::pair<bool, std::string> sceneswitch;

class Scene {
public:
	Scene(std::string name, bool alive, sceneswitch sceneSwitch) : m_name(name), m_alive(alive), m_switchingScene(sceneSwitch) {}
	~Scene() {}

	virtual void Update(sf::Time dt) = 0;
	virtual void Render(sf::RenderWindow & window) = 0;
	virtual void HandleInput() = 0;

	virtual void Start() { m_alive = true; }
	virtual void Stop() { m_alive = false; m_switchingScene = sceneswitch(false, ""); }

	
	bool IsAlive() { return m_alive; }
	std::string GetName() { return m_name; }
	std::pair<bool, std::string> SwitchingScene() { return m_switchingScene; }

protected:
	bool m_alive;
	std::string	m_name;
	sceneswitch m_switchingScene;

};

#endif // !SCENE_H

