# C++ AI Agent 架构文档

## 1. 总体概览

本项目实现了一个轻量级 C++ ReAct Agent 框架，支持多轮决策和工具调度。  
核心思路：

1. 用户输入请求
2. Agent 根据上下文与 LLM 模拟输出生成 action
3. JSON 解析 action
4. ToolManager 查找对应工具
5. TaskQueue 提交任务到 ThreadPool 并发执行
6. 工具执行结果返回并更新 memory
7. 重复 action / step limit 控制循环

---

## 2. 模块说明

| 模块 | 功能 |
|------|------|
| `Agent` | 控制循环逻辑，多轮决策，调用 TaskQueue 执行工具，管理 memory |
| `Tool` | 抽象接口，定义 name/run 方法 |
| `EchoTool/FileTool/ShellTool` | 三个基础工具，实现 Tool 接口 |
| `ToolManager` | 管理工具注册与查找 |
| `ThreadPool` | 线程池，执行异步任务 |
| `TaskQueue` | 提交工具任务到线程池并返回 future |
| `Memory` | 保存历史上下文，避免重复 action，提供 context |
| `JsonParser` | 解析 LLM 输出的 JSON 结构 |

## 3. Agent 执行流程

用户输入
   ↓
Agent.run()
   ↓
fakeLLM 输出 JSON
   ↓
JsonParser 解析
   ↓
ToolManager 查找工具
   ↓
TaskQueue.submit(tool, input)
   ↓
ThreadPool 执行工具
   ↓
工具返回结果
   ↓
Memory 记录历史
   ↓
检查重复 action / step limit
   ↓
下一轮循环或结束

## 4. 并发设计

TaskQueue 统一调度所有工具任务
ThreadPool 包含多线程 worker
lambda 封装任务 + packaged_task + future 获取结果
主循环无需阻塞等待线程创建，直接 future.get() 拿结果

## 5. 异常与鲁棒性

JSON 解析失败 → retry 一次 → fallback 到 echo
工具不存在 → 返回错误信息
重复 action → 停止循环
step limit → 限制最大执行轮数，避免死循环

## 6. 扩展能力

可以添加更多 Tool，实现新的功能（Web API、计算任务等）
可升级 memory 为会话级 / 长期上下文
可增加日志系统 / 监控
