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

using namespace CGraph;

int main() {
    auto pipeline = GPipelineFactory::create();
    CStatus status = pipeline->process();    // 假装做了啥事情
    CGRAPH_ECHO("pipeline run ...");

    WFHttpServer server([](WFHttpTask *task) {
        task->get_resp()->append_output_body("hello, CGraph-NIO...");
    });

    if (server.start(8888) == 0) { // start server on port 8888
        getchar(); // press "Enter" to end.
        server.stop();
    }

    GPipelineFactory::clear();
    return 0;
}
