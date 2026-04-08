cmake_minimum_required(VERSION 3.10)
project(cpp_ai_agent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main
    src/main.cpp
    src/agent.cpp
    src/echo_tool.cpp
    src/file_tool.cpp
    src/shell_tool.cpp
    src/tool_manager.cpp
    src/json_parser.cpp
    src/memory.cpp
    src/thread_pool.cpp
    src/task_queue.cpp
)