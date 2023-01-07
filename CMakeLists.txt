cmake_minimum_required(VERSION 3.5.0)
project(CGraph-NIO)

set(CMAKE_CXX_STANDARD 17)

# 需要自行安装openssl库，并且提前编译workflow工程

set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl@1.1/")
set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib/")
set(OPENSSL_INC_DIR "${OPENSSL_ROOT_DIR}/include/")

set(WORKFLOW_INC_DIR "/usr/local/include/workflow/")
set(LOCAL_LIB_DIR "/usr/local/lib/")

include(3rd-party/CGraph/cmake/CGraph-env-include.cmake)

# 添加 workflow 相关内容
include_directories(${OPENSSL_INC_DIR})
include_directories(${WORKFLOW_INC_DIR})

file(GLOB_RECURSE CGRAPH_SRC_LIST "./3rd-party/CGraph/src/*.cpp")

add_executable(CGraph-NIO
        ${CGRAPH_SRC_LIST}
        main.cpp
        )

# 引入编译好的workflow库和ssl库的内容
TARGET_LINK_LIBRARIES(CGraph-NIO "${OPENSSL_LIB_DIR}/libssl.a")    # 连接ssl库相关内容
TARGET_LINK_LIBRARIES(CGraph-NIO "${OPENSSL_LIB_DIR}/libcrypto.a")
TARGET_LINK_LIBRARIES(CGraph-NIO "${LOCAL_LIB_DIR}/libworkflow.a")
