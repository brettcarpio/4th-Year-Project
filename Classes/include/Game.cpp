#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :
	m_window(sf::VideoMode(1400, 800, 32), "Dungeon Generator")
{
	
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
	
}

void Game::Render()
{
	m_window.clear();
	m_window.display();
}

void Game::ProcessEvents()
{
	sf::Event Event;
	while (m_window.pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			m_window.close();

		if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
			m_window.close();

	}
}

