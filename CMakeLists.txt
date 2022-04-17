cmake_minimum_required(VERSION 3.11)
project(CGraph-NIO)

set(CMAKE_CXX_STANDARD 17)

IF(APPLE)
    # 非mac平台，暂时不支持自动生成session信息
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -finline-functions -Wno-deprecated-declarations")
    add_definitions(-D_GENERATE_SESSION_)
    add_definitions(-D_ENABLE_LIKELY_)
ELSEIF(UNIX)
    # linux平台加入多线程内容
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -Wno-format-overflow")
    add_definitions(-D_ENABLE_LIKELY_)
ENDIF()

# 添加 workflow 相关内容
include_directories(3rd-party/workflow/src/include/workflow/)
include_directories(/opt/homebrew/opt/openssl/include/)
link_libraries(/opt/homebrew/opt/openssl/lib)

file(GLOB_RECURSE CGRAPH_SRC_LIST "./3rd-party/CGraph/src/*.cpp")
file(GLOB_RECURSE WF_SRC_LIST "./3rd-party/workflow/src/*.cc")

list(REMOVE_ITEM WF_SRC_LIST
        ./3rd-party/workflow/src/factory/KafkaTaskImpl.cc
        ./3rd-party/workflow/src/client/WFKafkaClient.cc
        ./3rd-party/workflow/src/protocol/KafkaDataTypes.cc
        ./3rd-party/workflow/src/protocol/KafkaMessage.cc
        ./3rd-party/workflow/src/protocol/KafkaResult.cc
        ./3rd-party/workflow/src/kernel/IOService_linux.cc
        )

add_executable(CGraph-NIO
        ${CGRAPH_SRC_LIST}
        ${WF_SRC_LIST}
        main.cpp
        )
