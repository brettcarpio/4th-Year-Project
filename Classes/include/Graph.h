#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "GraphNode.h"
#include "GraphArc.h"

template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;

template<class NodeType, class ArcType>
class Graph {
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;
	
	std::vector<Node*> m_nodes;

	Graph() {}

	Graph(const Graph &g) : m_nodes(g.m_nodes.size())
	{
		for (int i = 0; i < g.m_nodes.size(); i++)
		{
			m_nodes[i] = new Node;
			m_nodes[i]->m_name = g.m_nodes[i]->m_name;
			m_nodes[i]->m_data = g.m_nodes[i]->m_data;
		}

		for (int i = 0; i < g.m_nodes.size(); i++)
		{
			for (int j = 0; j < g.m_nodes.size(); j++)
			{
				Arc* arc = g.m_nodes[i]->GetArc(g.m_nodes[j]);
				if (arc != nullptr)
				{
					AddArc(i, j, arc->m_weight);
				}
			}
		}
	}

	~Graph()
	{
		for (int i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes[i] != 0)
			{
				delete m_nodes[i];
				m_nodes[i] = nullptr;
			}
		}
	}

	bool AddNode(std::string name, NodeType data)
	{
		Node* node = new Node;
		node->m_name = name;
		node->m_data = data;
		node->m_marked = false;

		m_nodes.push_back(node);

		return true;
	}

	void RemoveNode(int index)
	{
		if (m_nodes[index] != 0)
		{
			Arc* arc = nullptr;

			for (int node = 0; node < m_nodes.size(); node++)
			{
				if (m_nodes[node] != 0)
					arc = m_nodes[node]->GetArc(m_nodes[index]);
				if (arc != nullptr)
					RemoveArc(node, index);
			}
			delete m_nodes[index];
			m_nodes.erase(std::remove(m_nodes.begin(), m_nodes.end(), m_nodes[index]), m_nodes.end());
		}
	}

	bool AddArc(int from, int to, ArcType weight)
	{
		if (m_nodes[from] == 0 || m_nodes[to] == 0)
			return false;
		else
			m_nodes[from]->AddArc(m_nodes[to], weight);
		return true;
		
	}

	void RemoveArc(int from, int to)
	{
		if (m_nodes[from] == 0 || m_nodes[to] == 0)
			std::cout << "node doesn't exist" << std::endl;
		else
			m_nodes[from]->RemoveArc(m_nodes[to]);
	}

	void AddGraph(const Graph<NodeType, ArcType> &g, Node* previous, Node* following, ArcType prevToCurr, ArcType follToCurr, ArcType currToPrev, ArcType currToFoll)
	{
		std::vector<Node*> temp;
		for (int i = 0; i < g.m_nodes.size(); i++)
		{
			Node* node = new Node;
			node->m_name = g.m_nodes[i]->m_name;
			node->m_data = g.m_nodes[i]->m_data;
			temp.push_back(node);
		}

		for (int i = 0; i < g.m_nodes.size(); i++)
		{
			for (int j = 0; j < g.m_nodes.size(); j++)
			{
				Arc* arc = g.m_nodes[i]->GetArc(g.m_nodes[j]);
				if (arc != nullptr)
				{
					temp[i]->AddArc(temp[j], arc->m_weight);
				}
			}
		}

		previous->AddArc(temp.front(), prevToCurr);
		following->AddArcFromFront(temp.back(), follToCurr);

		temp.front()->AddArc(previous, currToPrev);
		temp.back()->AddArc(following, currToFoll);

		for (int i = 0; i < temp.size(); i++)
		{
			m_nodes.push_back(temp[i]);
		}
	}
};

#endif // !GRAPH_H
