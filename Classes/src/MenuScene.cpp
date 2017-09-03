#include "MenuScene.h"

MenuScene::MenuScene(sf::RenderWindow& window) : Scene("MenuScene", false, sceneswitch(false, ""))
{
	if (!m_logoTexture.loadFromFile("Assets/Menu/logo.png"))
		std::cout << "logo not loaded!" << std::endl;
	if (!m_caveBtnTex.loadFromFile("Assets/Menu/Cave_btn.png"))
		std::cout << "C.A button not loaded!" << std::endl;
	if (!m_dungeonBtnTex.loadFromFile("Assets/Menu/Dungeon_btn.png"))
		std::cout << "Dungeon button not loaded!" << std::endl;

	m_logo.setTexture(m_logoTexture);
	m_logo.setOrigin(sf::Vector2f(m_logoTexture.getSize().x / 2, m_logoTexture.getSize().y / 2));
	m_logo.setPosition(window.getSize().x / 2, window.getSize().y / 4);

	m_dungeonBtn.setTexture(m_dungeonBtnTex);
	m_dungeonBtn.setPosition(window.getSize().x / 2 - (m_dungeonBtnTex.getSize().x / 2), window.getSize().y / 2);

	m_caveBtn.setTexture(m_caveBtnTex);
	m_caveBtn.setPosition(window.getSize().x / 2 - (m_caveBtnTex.getSize().x / 2), m_dungeonBtn.getPosition().y + 100);

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
	window.draw(m_caveBtn);
	window.draw(m_dungeonBtn);
	mousepos = sf::Mouse::getPosition(window);
}

void MenuScene::HandleInput(sf::Event e)
{
	if (mousepos.x >= (m_dungeonBtn.getPosition().x) &&
		mousepos.x <= (m_dungeonBtn.getPosition().x + m_dungeonBtnTex.getSize().x) &&
		mousepos.y >= (m_dungeonBtn.getPosition().y) &&
		mousepos.y <= (m_dungeonBtn.getPosition().y + m_dungeonBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_switchingScene = sceneswitch(true, "DungeonScene");
	}
	else if (mousepos.x >= (m_caveBtn.getPosition().x) &&
		mousepos.x <= (m_caveBtn.getPosition().x + m_caveBtnTex.getSize().x) &&
		mousepos.y >= (m_caveBtn.getPosition().y) &&
		mousepos.y <= (m_caveBtn.getPosition().y + m_caveBtnTex.getSize().y) &&
		sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_switchingScene = sceneswitch(true, "CellScene");
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
