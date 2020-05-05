/*
 * @Author: your name
 * @Date: 2020-05-04 12:21:00
 * @LastEditTime: 2020-05-05 17:24:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /tvm/home/afly/work/afly_ai/src/main.cpp
 */
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#if 0
#include <dmlc-core/include/dmlc/logging.h>
#endif
#include <boost/version.hpp>
#include "../3rdparty/dmlc-core/include/dmlc/logging.h"
// #include "../include/fy/node.h"
#include "../include/fy/graph.h"

using namespace std;
using namespace fy::node;
using namespace fy::graph;

typedef fy::node::OpNode base1OpNode;

int main(int argc, char *argv[])
{
    DLOG(INFO)<<"main test";
    std::cout << "Boost version: "  //1.58.0
          << BOOST_VERSION / 100000
          << "."
          << BOOST_VERSION / 100 % 1000
          << "."
          << BOOST_VERSION % 100
          << std::endl;
    auto absNode1 = std::make_shared<AbsNode>(1,"abs");
    std::shared_ptr <base1OpNode> absNode =
                        std::make_shared<AbsNode>(1,"abs");
    std::shared_ptr <base1OpNode> logNode =
                        std::make_shared<LogNode>(2,"log");
    std::shared_ptr <base1OpNode> logNode1 =
                        std::make_shared<LogNode>(2,"log1");
    // fy::graph::afly_graph* graph =  new fy::graph::afly_graph();
    fy::graph::afly_graph graph;
    EdgeProperty ep;
    ep.src = 10;
    ep.dst = 11;
    graph.addNode(absNode);
    graph.addNode(logNode);
    graph.addNode(logNode1);
    graph.addEdge(absNode, logNode, ep);
    graph.addEdge(logNode, logNode1, ep);


    graph.printAllNodes();
    graph.printAllEdges();
    auto s = graph.getAllNodes();
    DLOG(INFO) <<" nodes size: "<<s.size();

    // graph->AddVertex(logNode);
    // DLOG(INFO)<<"add abs node.";

    // EdgeProperty edge;
    // edge.src=0;
    // edge.dst=1;
    // graph->addEdge(baseNode, absNode1, edge);
    // DLOG(INFO)<<"add log node.";
    // graph->addNode(logNode);
    // DLOG(INFO)<<"get all node.";
    // graph->getAllNodes();
    // graph->print();

    return 0;
}




