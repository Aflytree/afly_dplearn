#pragma once
#include <fy/graph.h>
#include <fy/node.h>
#include <fy/tensor.h>

namespace fy{
namespace session{
    typedef std::shared_ptr<fy::node::OpNode> baseOpNodePtr;

    class Session{
    	Session()
	{}
	int32_t run(afly_graph &InGraph));
    
    };

} //namespace session

} //namespace fy


