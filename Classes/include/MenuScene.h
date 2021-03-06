#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

class MenuScene : public Scene {
public:
	MenuScene(sf::RenderWindow& window);
	~MenuScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);
	void Start();
	void Stop();

private:
	sf::Texture m_logoTexture;
	sf::Sprite m_logo;

	sf::Texture m_dungeonBtnTex;
	sf::Texture m_caveBtnTex;
	sf::Sprite m_dungeonBtn;
	sf::Sprite m_caveBtn;

};

#endif // !MENUSCENE_H
