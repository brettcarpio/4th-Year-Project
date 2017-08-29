#include "CellScene.h"

CellScene::CellScene(sf::RenderWindow & window) : Scene("CellScene", false, sceneswitch(false, ""))
{
	SetupGraph();
	SetupGrammar();
}

CellScene::~CellScene()
{
}

void CellScene::Update(sf::Time dt)
{
}

void CellScene::Render(sf::RenderWindow & window)
{
}

void CellScene::HandleInput(sf::Event e)
{
	if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num1))
	{
		m_switchingScene = sceneswitch(true, "MenuScene");
	}
	else if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Num2))
	{
		m_switchingScene = sceneswitch(true, "DungeonScene");
	}
}

void CellScene::Start()
{
	m_alive = true;
}

void CellScene::Stop()
{
	m_alive = false;
	m_switchingScene = sceneswitch(false, "");
}

void CellScene::SetupGraph()
{
}

void CellScene::SetupGrammar()
{
}
