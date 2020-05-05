/*
 * @Author: your name
 * @Date: 2020-05-04 11:35:46
 * @LastEditTime: 2020-05-05 22:11:20
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

enum vertex_properties_t { vertex_properties };
enum edge_properties_t { edge_properties };
// BOOST_INSTALL_PROPERTY(vertex, properties);
// BOOST_INSTALL_PROPERTY(edge, properties);
//template < typename VERTEXPROPERTIES, typename EDGEPROPERTIES >
class afly_graph{

    typedef std::shared_ptr<fy::node::OpNode> baseOpNodePtr;
    // typedef property<vertex_properties_t, baseOpNodePtr>
    //                                     VertexProperty;
    typedef property<vertex_name_t, baseOpNodePtr>
                                        VertexProperty;
    typedef property<edge_properties_t, EdgeProperty>
                                        EdgeWeightProperty;
    typedef property<edge_weight_t, EdgeProperty>
                                        EdgeWeightProperty2;
    typedef boost::adjacency_list<listS, vecS, directedS,
                        VertexProperty, EdgeWeightProperty2> graph_type_;
    // typedef graph_traits::edge_iterator edge_iter;
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
        Vertex addNode(const baseOpNodePtr& prop){
            auto v = add_vertex(prop, inter_graph);
            local_map_[prop] = v;
            return v;
        }

        // void addNode(baseOpNodePtr node);
        void addEdge(baseOpNodePtr node1, baseOpNodePtr node2,
                                            EdgeProperty edge);
        void in_degree(baseOpNodePtr node);
        void out_degree(baseOpNodePtr node);
        std::vector<baseOpNodePtr> inNodes();
        std::vector<baseOpNodePtr> outNodes();
        void printAllNodes();
        void printAllEdges();
        std::vector<baseOpNodePtr> getAllNodes();
        std::vector<EdgeProperty> getEAlledges();


    private:
        graph_type_ inter_graph;
        /*baseOpNodePtr << -- >> Vertex*/
        std::map<baseOpNodePtr, Vertex> local_map_;
        //std::vector<>
};

}// namespace graph
}// namespace fy

#endif //GRAPH_H

