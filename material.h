/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: material.h
@Time: 2023/1/15 20:44
@Desc: 设定几个
***************************/

#ifndef CGRAPH_NIO_MATERIAL_H
#define CGRAPH_NIO_MATERIAL_H


#include "3rd-party/CGraph/src/CGraph.h"

using namespace CGraph;

static const char* PARAM_KEY = "my-param";
struct MyParam : public GParam {
    int loop_ = 0;
    int val_ = 0;
    void reset() override {
        val_ = 0;        // 计算数值复位
        loop_++;         // 记录轮询次数
    }
};

class MyNode : public GNode {
public:
    CStatus init() override {
        return CGRAPH_CREATE_GPARAM(MyParam, PARAM_KEY)    // 创建参数
    }

    CStatus run() override {
        auto param = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, PARAM_KEY)
        param->val_++;    // 获取参数，并且给参数赋值
        return CStatus();
    }
};

// 构建流水线逻辑
GPipelinePtr buildPipeline() {
    auto pipeline = GPipelineFactory::create();
    GElementPtr a, b = nullptr;
    pipeline->registerGElement<MyNode>(&a, {}, "A");
    pipeline->registerGElement<MyNode>(&b, {a}, "B");    // 注册一个链路信息，a->b
    return pipeline;
}

#endif //CGRAPH_NIO_MATERIAL_H
