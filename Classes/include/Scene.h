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
	virtual void HandleInput(sf::Event e) = 0;

	virtual void Start() = 0;
	virtual void Stop() = 0;
	
	bool IsAlive() { return m_alive; }
	std::string GetName() { return m_name; }
	std::pair<bool, std::string> SwitchingScene() { return m_switchingScene; }

protected:
	bool m_alive;
	std::string	m_name;
	sceneswitch m_switchingScene;
	sf::Vector2i mousepos;
	std::vector<sf::Sprite> m_sprites;

};

#endif // !SCENE_H

