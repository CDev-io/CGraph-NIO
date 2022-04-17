/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2022/4/17 22:20
@Desc: 
***************************/

#include <iostream>

#include "3rd-party/workflow/src/include/workflow/WFHttpServer.h"
#include "3rd-party/CGraph/src/CGraph.h"

using namespace CGraph;

int main() {
    auto pipeline = GPipelineFactory::create();
    WFHttpServer server([](WFHttpTask *task) {
        task->get_resp()->append_output_body("<html>Hello World!</html>");
    });

    if (server.start(8888) == 0) { // start server on port 8888
        getchar(); // press "Enter" to end.
        server.stop();
    }

    return 0;
}
