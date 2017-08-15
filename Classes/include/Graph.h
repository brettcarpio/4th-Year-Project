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
	int m_count;

	Graph() {}
	Graph(int size) : m_nodes(size)
	{
		for (int i = 0; i < size; i++)
			m_nodes[i] = 0;
		m_count = 0;
	}

	~Graph()
	{
		for (int i = 0; i < m_nodes.size(); i++)
		{
			if (m_nodes[i] != 0)
				delete m_nodes[i];
		}
	}

	bool AddNode(NodeType data, int index)
	{
		if (m_nodes[index] != 0)
			return false;

		m_nodes[index] = new Node;
		m_nodes[index]->m_data = data;
		m_nodes[index]->m_marked = false;
		m_count++;
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
