/*
 * @Author: your name
 * @Date: 2020-05-04 11:04:29
 * @LastEditTime: 2020-05-05 16:39:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings EditO
 * @FilePath: /tvm/home/afly/work/afly_ai/include/fy/node.h
 */
/*================================================================
*   Copyright (C) 2020 Lynxi Ltd. All rights reserved.
*
*   @file       ：Node.h
*   @author     ：afly
*   @date       ：2020.05.04
*   @description：
*
*================================================================*/
#pragma once
#ifndef _OP_NODE_H
#define _OP_NODE_H
#include <string>

using namespace std;

namespace fy{
namespace node{

class node{
    public:
        node(){}
        node(int id, const std::string name){
            this->id = id;
            this->name = name;
        }
    private:
        int id;
        std::string name;
};

class OpNode : public node{
    public:
        OpNode(){}
        OpNode(int id, std::string name)
        : node(id, name)
        {
            this->id = id;
            this->name = name;
        }
        std::string getName(){
            return name;
        }
    private:
        int id;
        std::string name;
};

class LogNode : public OpNode{
    public:
        LogNode(){}
        LogNode(int id, const std::string name = "")
        : OpNode{id, name}
        {
            this->id = id;
            this->name = name;
        }
    private :
        int id;
        std::string name;
};

class AbsNode : public OpNode{
    public:
        AbsNode(){}
        AbsNode(int id, const std::string name = "")
        : OpNode{id, name}
        {
            this->id = id;
            this->name = name;
        }
    private :
        int id;
        std::string name;
};



} // namespace node
} // namespace fy

#endif //NODE_H



