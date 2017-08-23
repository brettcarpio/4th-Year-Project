#ifndef GRAPH_ARC_H
#define GRAPH_ARC_H

#include "GraphNode.h"

template<class NodeType, class ArcType>
class GraphArc {
public:
	GraphArc() {}
	GraphArc(const GraphArc &a) { m_node = a.m_node; }

	GraphNode<NodeType, ArcType>* m_node;
	ArcType m_weight;
};
#endif // !GRAPH_ARC_H
