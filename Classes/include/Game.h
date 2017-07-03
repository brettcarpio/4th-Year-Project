#ifndef GAME_H
#define GAME_H


#include "SFML/Graphics.hpp"

class Game {
public:
	Game();
	~Game();

	void Run();
	void Update(sf::Time dt);
	void Render();
	void ProcessEvents();

private: //functions


private: //variables
	sf::RenderWindow m_window;
	static const sf::Time TimePerFrame;
};

#endif // !GAME_H