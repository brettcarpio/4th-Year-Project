#ifndef DUNGEON_SCENE_H
#define DUNGEON_SCENE_H

#include "Scene.h"
#include "GrammarSystem.h"

class DungeonScene : public Scene {
public:
	DungeonScene(sf::RenderWindow& window);
	~DungeonScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);

private:
	GrammarSystem m_grammar;
};

#endif // !DUNGEON_SCENE_H
