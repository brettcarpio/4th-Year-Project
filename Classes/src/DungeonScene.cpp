#include "..\include\DungeonScene.h"

DungeonScene::DungeonScene(sf::RenderWindow& window) : Scene("DungeonScene", false, sceneswitch(false, ""))
{
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

void DungeonScene::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
}
