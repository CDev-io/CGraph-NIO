/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2022/4/17 22:20
@Desc: 
***************************/

#include "nio/NioInclude.h"

using namespace CGraph;

int main() {
    GElementPtr node = nullptr;
    auto pipeline = GPipelineFactory::create();
    CStatus status = pipeline->registerGElement<DWFServerNode>(&node, {}, "wf", 1);
    status = pipeline->process();
    if (!status.isOK()) {
        CGRAPH_ECHO("pipeline process failed");
    }

    GPipelineFactory::clear();
    return 0;
}
