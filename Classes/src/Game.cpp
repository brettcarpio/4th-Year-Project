#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :
	m_window(sf::VideoMode(1440, 800, 32), "Dungeon Generator")
{
	m_scnMgr = new SceneManager(m_window);
}

Game::~Game()
{
	
}

void Game::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime; 
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			ProcessEvents();
			Update(TimePerFrame);
		}
		Render();
	}
}

void Game::Update(sf::Time dt)
{
	m_scnMgr->Update(dt);
}

void Game::Render()
{
	m_window.clear();
	m_scnMgr->Render(m_window);
	m_window.display();
}

void Game::ProcessEvents()
{
	sf::Event e;
	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_window.close();

		if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Escape))
			m_window.close();

		m_scnMgr->HandleInput(e);
	}
}

