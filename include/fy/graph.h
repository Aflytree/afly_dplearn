/*
 * @Author: your name
 * @Date: 2020-05-04 11:35:46
 * @LastEditTime: 2020-05-06 23:13:49
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /tvm/home/afly/work/afly_ai/include/fy/graph.h
 */
/*================================================================
*   Copyright (C) 2020 Lynxi Ltd. All rights reserved.
*
*   @file       ：graph.h
*   @author     ：afly
*   @date       ：2020.05.04
*   @description：
*
*================================================================*/
#pragma once
#ifndef _GRAPH_H
#define _GRAPH_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include <dmlc/logging.h>
#include "node.h"

namespace boost {

}

namespace fy{
namespace graph{

using namespace boost;
using namespace fy::node;

struct EdgeProperty{
    int src;
    int dst;
};

// enum vertex_properties_t { vertex_properties };
// enum edge_properties_t { edge_properties };

typedef std::shared_ptr<fy::node::OpNode> baseOpNodePtr;

template < typename NodeDataType, typename EdgeDataType>
class afly_graph{

    typedef struct edge_t{
        edge_t(NodeDataType src = nullptr,
               NodeDataType dst = nullptr) :
               src(src), dst(dst)
        {}
        NodeDataType srcNode;
        NodeDataType dstNode;
        EdgeProperty data;

    }UserEdge;

    typedef property<vertex_name_t, NodeDataType>
                                        VertexProperty;
    // typedef property<edge_properties_t, EdgeDataType>
    //                                     EdgeWeightProperty;
    typedef property<edge_weight_t, EdgeDataType>
                                        EdgeWeightProperty2;
    typedef boost::adjacency_list<listS, vecS, directedS,
                        VertexProperty, EdgeWeightProperty2> graph_type_;
    typedef typename graph_traits<graph_type_>::vertex_iterator
                                                        vertex_iter;
    // 边迭代器类型
    typedef typename graph_traits<graph_type_>::edge_iterator edge_iter;

    /* a bunch of graph-specific typedefs */
    typedef typename graph_traits<graph_type_>::vertex_descriptor Vertex;
    typedef typename graph_traits<graph_type_>::edge_descriptor Edge;
    typedef std::pair<Edge, Edge> EdgePair;

    typedef typename graph_traits<graph_type_>::adjacency_iterator adjacency_iter;
    typedef typename graph_traits<graph_type_>::out_edge_iterator out_edge_iter;

    typedef typename graph_traits<graph_type_>::degree_size_type degree_t;

    typedef std::pair<adjacency_iter, adjacency_iter> adjacency_vertex_range_t;
    typedef std::pair<out_edge_iter, out_edge_iter> out_edge_range_t;
    typedef std::pair<vertex_iter, vertex_iter> vertex_range_t;
    typedef std::pair<edge_iter, edge_iter> edge_range_t;

    public:
      /* default constructors etc. */
        afly_graph(){}
        /*deconstructors*/
        virtual ~afly_graph(){}

        /* structure modification methods */
        void Clear(){
            inter_graph.clear();
        }

        //不可用inline函数
        Vertex addNode(const NodeDataType& prop){
            auto v = add_vertex(prop, inter_graph);
            local_map_[prop] = v;
            return v;
        }

        void addEdge(NodeDataType node1, NodeDataType node2,
                                    EdgeDataType edge){
            auto r1 = local_map_.find(node1);
            auto r2 = local_map_.find(node2);
            if(r1 == local_map_.end() && r2 == local_map_.end()){
                LOG(FATAL) << "should add node first!";
            }
            add_edge(r1->second, r2->second, edge, inter_graph);

        }

        void in_degree(NodeDataType node);
        void out_degree(NodeDataType node);
        std::vector<NodeDataType> inNodes();
        std::vector<NodeDataType> outNodes();
        void printAllNodes();
        void printAllEdges();
        std::vector<NodeDataType> getAllNodes();
        std::vector<EdgeDataType> getEAlledges();
        vector<EdgeDataType>  getInEdges(const NodeDataType& data);
        //整个图的inputNodes
        vector<NodeDataType>  getInputNodes();
        //整个图的outputNodes
        vector<NodeDataType>  getOutputNodes(){
            //vector<NodeDataType> DFSNodes = DFS();
            //outdegree为0
        }

        size_t getOutDegree(const NodeDataType& data);
        size_t getInDegree(const NodeDataType& data);
        size_t removeNode(const NodeDataType& data);
        int32_t removeEdge(const EdgeDataType & edge);
        int32_t removeEdge(const NodeDataType& node1,const NodeDataType& node2);
        size_t getNumNodes() const{return num_vertices[inter_graph];};
        size_t getNumEdges() const{return num_edges[inter_graph];};
        std::string print();
        //boost dfs方法遍历图
        vector<NodeDataType> DFS();
        vector<NodeDataType> BFS();

        int32_t writeToPDF(char const *filename){
        }

    private:
        graph_type_ inter_graph;
        /*NodeDataType << -- >> Vertex*/
        std::map<NodeDataType, Vertex> local_map_;
        //std::vector<>
};

typedef fy::graph::afly_graph<baseOpNodePtr, EdgeProperty> FyGraphType;

}// namespace graph
}// namespace fy

#endif //GRAPH_H

