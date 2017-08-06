#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "GraphNode.h"
#include "GraphArc.h"

template<class NodeType, class ArcType>
class Graph {
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	std::vector<Node*> m_nodes;
	int m_count;
	
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
};

#endif // !GRAPH_H
