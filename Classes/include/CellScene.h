#ifndef CELL_SCENE_H
#define CELL_SCENE_H

#include "Scene.h"
#include "GrammarSystem.h"
#include "Graph.h"
#include "Grid.h"

#include <fstream>

struct Cave
{
	sf::Vector2f m_position;
	std::string m_rule;
	int m_exitPos;
	int m_chance;
};

class CellScene : public Scene {
public:
	typedef GraphArc<Cave, std::string> Arc;
	typedef GraphNode<Cave, std::string> Node;

	CellScene(sf::RenderWindow& window);
	~CellScene();

	void Update(sf::Time dt);
	void Render(sf::RenderWindow & window);
	void HandleInput(sf::Event e);
	void Start();
	void Stop();

private:
	std::vector<std::pair<std::string, Cave>> LoadRules();
	void SetupGraph();
	void SetupGrammar();
	void RenderDungeon();
	void ClearDrawables();
	void RestartScene();

	void CreateRoom(Node* node, Node* parent, int count);
	void CreateExits(Node* node, Node* parent, Grid &g);
	void RandomFill(Grid &g, const int chance);
	void EvolveMap(Grid &g, std::string rule);
	bool PlaceWallLogic(Grid &g, int row, int col, std::string rule);
	int GetSurroundingWalls(Grid &g, int row, int col, int scopeX, int scopeY);
	bool IsWall(Grid &g, int row, int col);
	bool IsOutOfBound(Grid &g, int row, int col);

private:
	GrammarSystem<Cave, std::string> m_grammar;
	Graph<Cave, std::string>* m_graph;
	Graph<Cave, std::string>* m_translatedGraph;
	Grid m_grid;

	std::vector<Grid> m_grids;

	sf::Texture m_logoTexture;
	sf::Texture m_mainBtnTex;
	sf::Texture m_dungeonBtnTex;
	sf::Texture m_generateBtnTex;

	sf::Sprite m_logo;
	sf::Sprite m_mainBtn;
	sf::Sprite m_dungeonBtn;
	sf::Sprite m_generateBtn;

};

#endif // !CELL_SCENE_H
