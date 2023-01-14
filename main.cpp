/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: main.cpp
@Time: 2022/4/17 22:20
@Desc: 
***************************/

#include "3rd-party/CGraph/src/CGraph.h"
#include <WFHttpServer.h>

using namespace CGraph;

static const char* PARAM_KEY = "my-param";
struct MyParam : public GParam {
    int loop_ = 0;
    int val_ = 0;
    void reset() override {
        val_ = 0;    // 计算数值复位
        loop_++;    // 记录轮询次数
    }
};

struct MyNode : public GNode {
    CStatus init() override {
        return CGRAPH_CREATE_GPARAM(MyParam, PARAM_KEY)    // 创建参数
    }

    CStatus run() override {
        auto param = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, PARAM_KEY)
        param->val_++;    // 获取参数，并且给参数赋值
        return CStatus();
    }
};

void process() {
    auto pipeline = GPipelineFactory::create();
    GElementPtr a, b = nullptr;
    pipeline->registerGElement<MyNode>(&a, {}, "A");
    pipeline->registerGElement<MyNode>(&b, {a}, "B");    // 注册一个链路信息，a->b
    pipeline->init();
    std::mutex mtx;

    WFHttpServer server([pipeline, &mtx] (WFHttpTask *task) {
        CGRAPH_LOCK_GUARD lk(mtx);    // 防止重复进入（这里可以优化掉么？）
        pipeline->run();    // 执行链路逻辑，参数信息是有状态的
        auto param = pipeline->getGParamWithNoEmpty<MyParam>(PARAM_KEY);
        task->get_resp()->append_output_body("val is : " + std::to_string(param->val_) + ", loop is " + std::to_string(param->loop_));
    });

    if (server.start(8888) == 0) {
        getchar();
        server.stop();
        pipeline->destroy();
        GPipelineFactory::clear();
    }
}


int main()
{
    process();
    return 0;
}
