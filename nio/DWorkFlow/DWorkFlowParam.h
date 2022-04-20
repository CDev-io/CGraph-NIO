/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: DWorkFlowParam.h
@Time: 2022/4/20 21:24
@Desc: 
***************************/

#ifndef CGRAPH_NIO_DWORKFLOWPARAM_H
#define CGRAPH_NIO_DWORKFLOWPARAM_H

#include "../../../CGraph/src/CGraph.h"

struct DWorkFlowParam : public CGraph::GParam {
public:
    int val_ = 0;
    int port_ = 8888;

    CVoid reset() override {
    }
};

#endif //CGRAPH_NIO_DWORKFLOWPARAM_H
