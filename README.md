# 程序设计实习 大作业

![](https://img.shields.io/badge/build-passing-success)

[《程序设计实习》](https://pkupop.github.io/QT-page/)课程的大作业. 项目代号 "AI 记卡".

## 介绍

"AI 记卡" 是一款记忆卡片软件. 软件基于间隔重复算法, 自动安排一组卡片的学习时间, 帮助用户记忆. 此外, 软件可根据用户提供的关键词, 利用生成式语言模型, 自动生成记忆卡片.

## 构建

依赖项:

- Qt 6.5,
- CMake 3.19 以上.

Mac 平台: `brew install qt cmake` 即可.
Windows 平台: 下载[在线安装器](https://mirrors.tuna.tsinghua.edu.cn/help/qt/), 勾选并安装 Qt、MinGW.

### 使用 Qt Creator 构建

1. 在 "项目 > 构建和运行" (Projects > Build & Run) 中选择合适的构建套件.
2. 构建项目.

### 使用 CMake 构建

1. 配置: `cmake -B build .`
2. 构建: `cmake --build build`

### 单元测试

1. 设置环境变量: `export AIJIKA_TEST=1`
2. 配置, 并从 GitHub 下载 GoogleTest 库: `cmake -B build .`
3. 构建: `cmake --build build`
4. 运行测试: `./build/aijika_test`

注意部分测试需访问 OpenAI 服务, 默认不会运行. 要运行这些测试:

1. 设置环境变量 `OPENAI_BASE_URL` 和 `OPENAI_API_KEY` (可选).
2. 运行测试: `./build/aijika_test --gtest_also_run_disabled_tests`
