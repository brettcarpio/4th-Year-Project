#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <list>

template <typename NodeType, typename ArcType> class GraphArc;

template<class NodeType, class ArcType>
class GraphNode {
public:
	typedef GraphArc<NodeType, ArcType> Arc;
	typedef GraphNode<NodeType, ArcType> Node;

	std::string m_name;
	NodeType m_data;
	std::list<Arc> m_arcList;
	bool m_marked;

	GraphNode() {}

	GraphNode(const GraphNode & node)
	{
		m_name = node.m_name;
		m_data = node.m_data;
		m_arcList = node.m_arcList;
		m_marked = node.m_marked;
	}

	Arc* GetArc(Node* p_node)
	{
		for (std::list<Arc>::iterator itr = m_arcList.begin(); itr != m_arcList.end(); ++itr)
		{
			if ((*itr).m_node == p_node)
				return &(*itr);
		}
		return nullptr;
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
		std::list<Arc>::iterator itr = m_arcList.begin();
		std::list<Arc>::iterator end = m_arcList.end();
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