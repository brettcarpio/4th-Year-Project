#ifndef GRAMMARSYSTEM_H
#define GRAMMARSYSTEM_H

#include "Graph.h"
#include "GraphNode.h"
#include "GraphArc.h"

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <fstream>
#include <sstream>

template<class NodeType, class ArcType>
class GrammarSystem {
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	GrammarSystem() {}
	~GrammarSystem() {}

	void CreateRules(std::string path)
	{
		std::ifstream file;
		file.open(path);

		std::vector<std::string> data;
		std::string line;

		while (std::getline(file, line))
			data.push_back(line);

		file.close();

		m_rules.reserve(data.size());
		for (int i = 0; i < data.size(); i++)
		{
			std::istringstream ss(data[i]);
			std::string line;
			
			std::vector<std::string> ruleData;
			while (std::getline(ss, line, '/'))
			{
				ruleData.push_back(line);
			}

			Graph<std::string, std::string> subGraph = Graph<std::string, std::string>();
			std::istringstream ssNodes(ruleData[1]);
			while (std::getline(ssNodes, line, ','))
			{
				subGraph.AddNode(line);
			}

			std::istringstream ssArcs(ruleData[2]);
			while (std::getline(ssArcs, line, ','))
			{
				int from, to;
				std::stringstream arcData(line);
				while (arcData >> from >> to)
					subGraph.AddArc(from, to, "");
			}
			m_rules.push_back(std::make_pair(ruleData[0], subGraph));
		}
	}

	Graph<NodeType, ArcType> Translate(Graph<NodeType, ArcType> &graph)
	{
		Graph<NodeType, ArcType> newGraph = graph;
		std::queue<Node*> nodeQueue;
		for (int i = 0; i < newGraph.m_nodes.size(); i++)
		{
			nodeQueue.push(newGraph.m_nodes.at(i));
		}
		
		while (nodeQueue.size() != 0)
		{
			Node* current = nodeQueue.front();

			for (char &c : current->m_data)
			{
				if (isupper(c))
				{
					Graph<NodeType, ArcType> replacementGraph = SearchForRule(current->m_data);
					newGraph.RemoveNode(0);
					Node* previous = current->m_arcList.front().m_node;
					Node* following = current->m_arcList.back().m_node;

					previous->RemoveArc(current);
					following->RemoveArc(current);
				}
			}
			
			nodeQueue.pop();
		}
		return newGraph;
	}

private:
	std::vector<std::pair<std::string, Graph<NodeType, ArcType>>> m_rules;

	Graph<NodeType, ArcType> SearchForRule(std::string code)
	{
		std::vector<Graph<NodeType, ArcType>> rules;
		for (int i = 0; i < m_rules.size(); i++)
		{
			if (m_rules.at(i).first == code)
			{
				rules.push_back(m_rules.at(i).second);
			}
		}

		if (rules.size() == 0)
		{
			std::cout << "no rule found!" << std::endl;
			return Graph<std::string, std::string>();
		}
		else if (rules.size() == 1)
		{
			return rules.at(0);
		}
		else if (rules.size() > 1)
		{
			int i = rand() % m_rules.size();
			return rules.at(i);
		}
	}

};

#endif
