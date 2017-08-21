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

	Graph(const Graph& g)
	{
		for (int i = 0; i < g.m_nodes.size(); i++)
		{
			Node* node = new Node;
			node = g.m_nodes.at(i);
			m_nodes.push_back(node);
		}
	}

	~Graph()
	{
		for (int i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes[i] != 0)
				delete m_nodes[i];
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
			int node;
			Arc* arc;

			for (node = 0; node < m_nodes.size(); node++)
			{
				if (m_nodes[node] != 0)
					arc = m_nodes[node]->GetArc(m_nodes[index]);
				if (arc != 0)
					RemoveArc(node, index);
			}
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
			return false;
		else
			m_nodes[from]->RemoveArc(m_nodes[to]);
	}

};

#endif // !GRAPH_H
