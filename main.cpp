/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2022/4/17 22:20
@Desc: 
***************************/

#include "material.h"
#include <WFHttpServer.h>

void buildManager(GPipelineManager& manager, int size) {
    for (int i = 0; i < size; i++) {
        manager.add(buildPipeline());
    }
}

void runServer() {
    GPipelineManager manager;
    int size = 3;    // 最多同时处理多少个请求
    buildManager(manager, size);
    manager.init();    // 初始化所有的pipeline信息

    // 注册一个回调函数
    WFHttpServer server([&manager] (WFHttpTask *task) {
        auto pipeline = manager.fetch();    // 获取一个可用的pipeline
        if (pipeline == nullptr) {
            task->get_resp()->append_output_body("no free pipeline");
            return;
        }

        pipeline->run();
        auto param = pipeline->getGParamWithNoEmpty<MyParam>(PARAM_KEY);
        const std::string& response = "val = " + std::to_string(param->val_) + ", loop = " + std::to_string(param->loop_);
        task->get_resp()->append_output_body(response);
        manager.release(pipeline);    // 放回pipeline，供下次请求使用
    });

    if (server.start(8888) == 0) {
        getchar();
        server.stop();    // 结束 server
        manager.destroy();
    }
    GPipelineFactory::clear();    // 清空所有的pipeline信息
}

int main()
{
    runServer();    // 执行server逻辑，内部是CGraph的 dag调度逻辑
    return 0;
}
