/*
 * @Author: your name
 * @Date: 2020-05-04 11:43:08
 * @LastEditTime: 2020-05-05 17:27:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /tvm/home/afly/work/afly_ai/src/graph.cpp
 */
#include <iostream>
#include "../include/fy/graph.h"
#include "../3rdparty/dmlc-core/include/dmlc/logging.h"


namespace fy {
namespace graph {

    using namespace fy::node;
    using namespace std;
    typedef std::shared_ptr<fy::node::OpNode> baseOpNodePtr;

    void afly_graph::addEdge(baseOpNodePtr node1,
                             baseOpNodePtr node2,
                             EdgeProperty edge){

        auto r1 = local_map_.find(node1);
        auto r2 = local_map_.find(node2);
        if(r1 == local_map_.end() && r2 == local_map_.end()){
            LOG(FATAL) << "should add node first!";
        }
        add_edge(r1->second, r2->second, edge, inter_graph);
    }

    void afly_graph::in_degree(baseOpNodePtr node){

    };

    void afly_graph::out_degree(baseOpNodePtr node){

    };
    inline std::vector<baseOpNodePtr> afly_graph::inNodes(){

    };
    inline std::vector<baseOpNodePtr> afly_graph::outNodes(){

    };

    std::vector<baseOpNodePtr> afly_graph::getAllNodes(){
        DLOG(INFO)<<"get all nodes:";
        std::vector<baseOpNodePtr> v;
        auto vertexprop = get(boost::vertex_name, inter_graph);

        vertex_range_t vrange = vertices(inter_graph);
        for(vertex_iter itr = vrange.first; itr!=vrange.second; ++itr){
            baseOpNodePtr vprop = vertexprop[*itr];
            v.push_back(vprop);
            DLOG(INFO)<<vprop;
        }
        return v;
    };

    void afly_graph::printAllNodes(){
        DLOG(INFO)<<"print all nodes:";
        vertex_range_t vrange = vertices(inter_graph);
        auto vertexprop = get(boost::vertex_name, inter_graph);
        for(vertex_iter itr = vrange.first; itr!=vrange.second; ++itr){
            baseOpNodePtr vprop = vertexprop[*itr];
            cout <<vprop->getName() <<"["<<*itr <<"]"<< endl;

            auto tmp = *itr;
        }
    };

    void afly_graph::printAllEdges(){
        DLOG(INFO)<<"print all edges:";
        edge_range_t erange = edges(inter_graph);
        if(erange.first == erange.second){
            DLOG(INFO)<<"None";
            return;
        }
        for(edge_iter itr = erange.first; itr != erange.second; ++itr){
            auto vertexprop = get(boost::edge_weight, inter_graph);
            auto s = get(boost::vertex_name, inter_graph, source(*itr, inter_graph));
            auto t = get(boost::vertex_name, inter_graph, target(*itr, inter_graph));
            // baseOpNodePtr vprop = vertexprop(*itr);
            cout <<s->getName() <<"["<<source(*itr, inter_graph)<<"]" << "-->" <<
                                t->getName() <<"["<<target(*itr, inter_graph) <<"]"<< endl;


        }
    }


}//namespace graph

} //namespace fy
