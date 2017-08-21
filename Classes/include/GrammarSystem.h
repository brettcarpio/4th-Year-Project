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

		
		for (int i = 0; i < data.size(); i++)
		{
			std::istringstream ss(data[i]);
			std::string line;
			
			std::vector<std::string> ruleData;
			while (std::getline(ss, line, '/'))
			{
				ruleData.push_back(line);
			}

			int nodecount = 0;
			std::istringstream ssNodeCount(ruleData[1]);
			while (std::getline(ssNodeCount, line, ','))
			{
				nodecount++;
			}

			Graph<std::string, std::string> * subGraph = new Graph<std::string, std::string>(nodecount);
			std::istringstream ssNodes(ruleData[1]);
			int index = 0;
			while (std::getline(ssNodes, line, ','))
			{
				subGraph->AddNode(line, index);
				index++;
			}

			std::istringstream ssArcs(ruleData[2]);
			while (std::getline(ssArcs, line, ','))
			{
				int from, to;
				std::stringstream arcData(line);
				while (arcData >> from >> to)
					subGraph->AddArc(from, to, "");
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
					//Graph<NodeType, ArcType> replacementGraph = SearchForRule(current->m_data);
					//1.remove node from the graph and all arcs connected to it
					
					//2.add replacement graph and add arc between first node from replacement graph and all nodes
					//connecting from  previous node
					//from the removed node.
					//3.add arc between last node from the replacement graph and all the nodes connecting from the removed node.
				}
			}
			
			nodeQueue.pop();
		}
		return newGraph;
	}

private:
	std::vector<std::pair<std::string, Graph<NodeType, ArcType>*>> m_rules;

	Graph<NodeType, ArcType> SearchForRule(std::string code)
	{
		return 0;
	}

};

#endif
