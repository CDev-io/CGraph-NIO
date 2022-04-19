/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2022/4/17 22:20
@Desc: 
***************************/

#include <iostream>

#include "3rd-party/workflow/_include/workflow/WFHttpServer.h"
#include "3rd-party/CGraph/src/CGraph.h"
#include "3rd-party/CGraph/tutorial/MyGNode/HelloCGraphNode.h"

using namespace CGraph;

int main() {
    CStatus status;
    GElementPtr node = nullptr;
    auto pipeline = GPipelineFactory::create();
    pipeline->registerGElement<HelloCGraphNode>(&node, {}, "hcg", 1);
    pipeline->init();

    WFHttpServer server([&](WFHttpTask *task) {
        status = pipeline->run();    // 假装做了啥事情
        task->get_resp()->append_output_body("hello, CGraph-NIO...");
    });

    if (server.start(8888) == 0) { // start server on port 8888
        getchar(); // press "Enter" to end.
        server.stop();
    }

    pipeline->destroy();
    GPipelineFactory::clear();
    return 0;
}
