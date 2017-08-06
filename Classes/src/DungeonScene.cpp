#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
	m_grammar = GrammarSystem();
}

DungeonScene::~DungeonScene()
{
}

void DungeonScene::Update(sf::Time dt)
{
}

void DungeonScene::Render(sf::RenderWindow & window)
{
}

void DungeonScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::A))
	{
		m_grammar.ConvertToLowercase("TESt123 house TREE food");
	}
}
