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

	bool AddNode(NodeType data)
	{
		Node* node = new Node;
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
			m_nodes[index] = 0;
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

};

#endif // !GRAPH_H
