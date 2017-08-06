#ifndef GRAPH_ARC_H
#define GRAPH_ARC_H

#include "GraphNode.h"

template<class NodeType, class ArcType>
class GraphArc {
public:
	GraphNode<NodeType, ArcType>* m_node;
	ArcType m_weight;
};
#endif // !GRAPH_ARC_H
