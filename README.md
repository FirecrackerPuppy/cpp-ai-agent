#  C++ AI Agent（轻量级 ReAct 框架）

##  项目简介

本项目基于 C++ 从零实现了一个轻量级 AI Agent 框架，模拟了大模型（LLM）驱动的工具调用流程（ReAct 模式），支持多轮决策、工具调度、并发执行与基础鲁棒性机制。

该项目重点关注 **系统设计与工程能力**，而非依赖现成框架，适合作为 C++ 后端 / 系统设计 / AI Agent 方向的项目展示。

---

##  项目目标

将一个简单的 Agent Demo，升级为：

* 支持 ReAct 多轮推理
* 支持 Tool 插件化扩展
* 支持并发任务调度（ThreadPool）
* 支持 JSON 结构化解析
* 支持 retry / fallback 提升鲁棒性
* 支持 memory / 去重 / step limit
* 具备完整工程结构，可部署 / 扩展

---

##  核心架构

```text
User Input
   ↓
Agent
   ↓
(fake LLM / future real LLM)
   ↓
JSON Action
   ↓
ToolManager
   ↓
TaskQueue
   ↓
ThreadPool
   ↓
Tool Execution
   ↓
Result + Memory
```

---

##  项目结构

```text
cpp-ai-agent/
├── include/
│   ├── agent.h
│   ├── tool.h
│   ├── tool_manager.h
│   ├── thread_pool.h
│   ├── task_queue.h
│   ├── memory.h
│   ├── json_parser.h
│   ├── echo_tool.h
│   ├── file_tool.h
│   ├── shell_tool.h
├── src/
│   ├── main.cpp
│   ├── agent.cpp
│   ├── thread_pool.cpp
│   ├── task_queue.cpp
│   ├── memory.cpp
│   ├── json_parser.cpp
│   ├── echo_tool.cpp
│   ├── file_tool.cpp
│   ├── shell_tool.cpp
```

---

##  核心功能

### 1️ ReAct Agent 执行流程

* 支持 Thought → Action → Observation 循环
* 多 step 执行（step limit 控制）
* 支持 finish action 结束流程

---

### 2️ Tool 抽象与注册

* 基于虚函数实现 Tool 接口
* 使用 `ToolManager` 管理工具（unordered_map）
* 支持插件式扩展

当前实现工具：

* EchoTool（字符串处理）
* FileTool（文件读取）
* ShellTool（命令执行）

---

### 3️ 并发执行（ThreadPool + TaskQueue）

* 使用线程池执行工具任务
* TaskQueue 统一调度
* 使用：

  * lambda 封装任务
  * `std::packaged_task`
  * `std::future` 获取结果


### 4️ JSON 结构化解析

* 模拟 LLM 输出：

```json
{"action": "read_file", "input": "test.txt"}
```

* 解析后自动调度对应 Tool

👉 类似 function calling 机制

---

### 5️ retry / fallback 机制

* JSON 解析失败 → 自动 retry 一次
* retry 失败 → fallback 到默认工具
* 防止系统崩溃

---

### 6️ Memory / 去重 / Step 控制

* 记录执行历史（memory）
* 避免重复 action 死循环
* step limit 限制最大执行轮数

---

##  编译与运行

### 编译

```bash
g++ src/main.cpp src/agent.cpp src/echo_tool.cpp src/file_tool.cpp src/shell_tool.cpp src/tool_manager.cpp src/json_parser.cpp src/memory.cpp src/thread_pool.cpp src/task_queue.cpp -Iinclude -o main
```

---

### 运行

```bash
.\main.exe
```

---

### 示例输入

```text
read file
```

```text
hello
```

---

##  项目亮点（面试可用）

* 基于 C++ 实现轻量级 ReAct Agent 框架
* Tool 插件化设计（支持扩展）
* ThreadPool + TaskQueue 实现任务并发调度
* JSON 结构化解析模拟 function calling
* retry / fallback 提升系统鲁棒性
* memory + 去重 + step limit 防止死循环
* 模块化设计，具备良好工程结构


## 📌技术栈

* C++17
* STL（thread / future / mutex / condition_variable）
* 多线程编程
* 面向对象设计

---

