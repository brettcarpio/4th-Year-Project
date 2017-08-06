#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <list>

// Forward references
template <typename NodeType, typename ArcType> class GraphArc;

// -------------------------------------------------------
// Name:        GraphNode
// Description: This is the node class. The node class 
//              contains data, and has a linked list of 
//              arcs.
// -------------------------------------------------------
template<class NodeType, class ArcType>
class GraphNode {
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	NodeType m_data;
	std::list<Arc> m_arcList;
	bool m_marked;
	Arc* GetArc(Node* p_node)
	{
		typename list<Arc>::iterator itr = m_arcList.begin();
		typename list<Arc>::iterator end = m_arcList.end();

		for (; itr != end; ++itr)
		{
			if ((*itr).m_node == p_node)
				return &(*itr);
		}
		return 0;
	}

	void AddArc(Node* p_node, ArcType p_weight)
	{
		Arc a;
		a.m_node = p_node;
		a.m_weight = p_weight;
		m_arcList.push_back(a);
	}

	void RemoveArc(Node* p_node)
	{
		typename list<Arc>::iterator itr = m_arcList.begin();
		typename list<Arc>::iterator end = m_arcList.end();
		for (; itr != end; ++itr)
		{
			if ((*itr).m_node == p_node)
			{
				m_arcList.erase(itr);
				return;
			}
		}
	}
};

#include "GraphArc.h"
#endif