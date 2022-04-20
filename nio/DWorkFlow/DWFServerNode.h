/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: DWorkFlowNode.h
@Time: 2022/4/20 21:24
@Desc: 
***************************/

#ifndef CGRAPH_NIO_DWFSERVERNODE_H
#define CGRAPH_NIO_DWFSERVERNODE_H

#include "../../../CGraph/src/CGraph.h"
#include "DWorkFlowParam.h"
#include "../../3rd-party/workflow/_include/workflow/WFHttpServer.h"

const static char* WF = "workflow";

class DWFServerNode : public CGraph::GNode {

public:
    explicit DWFServerNode() {
        server_ = new WFHttpServer([&](WFHttpTask *task) {
            int result = serverFunction();
            task->get_resp()->append_output_body("hello, CGraph-NIO, val is " + std::to_string(result));
        });
    }

    int serverFunction() {
        // 假设，server的作用，就是做 i++;
        auto param = CGRAPH_GET_GPARAM(DWorkFlowParam, WF)
        return param->val_++;
    }

    CStatus init() override {
        CGRAPH_FUNCTION_BEGIN
        CGRAPH_ASSERT_NOT_NULL(server_)

        status = CGRAPH_CREATE_GPARAM(DWorkFlowParam, WF)
        if (!status.isOK()) {
            return CStatus("create param failed...");
        }

        auto param = CGRAPH_GET_GPARAM(DWorkFlowParam, WF)
        int ret = server_->start(param->port_);
        if (0 != ret) {
            return CStatus(std::to_string(param->port_) + " port init failed...");
        }

        CGraph::CGRAPH_ECHO("[%d] port init success ...", param->port_);
        CGRAPH_FUNCTION_END
    }

    CStatus run() final {
        CGraph::CGRAPH_ECHO("begin run...");
        getchar();

        CGraph::CGRAPH_ECHO("finish run...");
        return CStatus();
    }

    CStatus destroy() override {
        CGRAPH_ASSERT_NOT_NULL(server_)
        server_->stop();
        CGraph::CGRAPH_ECHO("server stop...");
        return CStatus();
    }

    ~DWFServerNode() override {
        CGRAPH_DELETE_PTR(server_)
    }

private:
    WFHttpServer* server_ = nullptr;
};



#endif //CGRAPH_NIO_DWFSERVERNODE_H
