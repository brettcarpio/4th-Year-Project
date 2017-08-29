#include "MenuScene.h"

MenuScene::MenuScene(sf::RenderWindow& window) : Scene("MenuScene", false, sceneswitch(false, ""))
{
	if (!m_logoTexture.loadFromFile("Assets/Menu/logo.png"))
		std::cout << "logo not loaded!" << std::endl;
	m_logo.setTexture(m_logoTexture);
	m_logo.setOrigin(sf::Vector2f(m_logoTexture.getSize().x / 2, m_logoTexture.getSize().y / 2));
	m_logo.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

MenuScene::~MenuScene()
{

}

void MenuScene::Update(sf::Time dt)
{

}

void MenuScene::Render(sf::RenderWindow & window)
{
	window.draw(m_logo);
}

void MenuScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num2))
	{
		m_switchingScene = sceneswitch(true, "DungeonScene");
	}
}

void MenuScene::Start()
{
	m_alive = true;
}

void MenuScene::Stop()
{
	m_alive = false;
	m_switchingScene = sceneswitch(false, "");
}
