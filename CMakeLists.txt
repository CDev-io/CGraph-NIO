cmake_minimum_required(VERSION 3.5.0)
project(CGraph-NIO)

set(CMAKE_CXX_STANDARD 17)

# 需要自行安装openssl库，并且提前编译workflow工程
set(OPENSSL_ROOT_DIR "/opt/homebrew/opt/openssl")

set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib/")
set(OPENSSL_INC_DIR "${OPENSSL_ROOT_DIR}/include/")

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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/workflow/_include/workflow/)
include_directories(${OPENSSL_INC_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/workflow/_lib)

file(GLOB_RECURSE CGRAPH_SRC_LIST "./3rd-party/CGraph/src/*.cpp")

add_executable(CGraph-NIO
        ${CGRAPH_SRC_LIST}
        main.cpp
        )

# 引入编译好的workflow库和ssl库的内容
TARGET_LINK_LIBRARIES(CGraph-NIO "${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/workflow/_lib/libworkflow.a")
TARGET_LINK_LIBRARIES(CGraph-NIO "${OPENSSL_LIB_DIR}libssl.a")    # 连接ssl库相关内容
TARGET_LINK_LIBRARIES(CGraph-NIO "${OPENSSL_LIB_DIR}libcrypto.a")
