# 程序设计实习 大作业

![](https://img.shields.io/badge/build-passing-success)

[《程序设计实习》](https://pkupop.github.io/QT-page/)课程的大作业. 项目代号 "AI 记卡".

## 介绍

"AI 记卡" 是一款记忆卡片软件. 软件基于间隔重复算法, 自动安排一组卡片的学习时间, 帮助用户记忆. 此外, 软件可根据用户提供的关键词, 利用生成式语言模型, 自动生成记忆卡片.

## 构建

依赖项:

- Qt 6.5,
- CMake 3.19 以上,
- 编译器: clang, GCC, MSVC 均可.

推荐使用 [aqt](https://github.com/miurahr/aqtinstall) 工具来安装依赖项.

1. 安装 aqt: `pip install aqtinstall`
2. 安装 Qt 框架:
   - Windows x64 平台, MinGW: `aqt install-qt windows desktop 6.5.1 win64_mingw --archives qttools qtbase MinGW`
   - Windows x64 平台, MSVC: `aqt install-qt windows desktop 6.5.1 win64_msvc2019_64 --archives qttools qtbase`
   - Mac 平台, clang: `aqt install-qt mac desktop 6.5.1 clang_64 --archives qttools qtbase`
3. 安装构建工具:
   - 例如, 在 Windows 平台安装 CMake: `aqt install-tool windows desktop tools_cmake`

这些命令仅供参考, 应当根据您的环境进行调整. 此外, 可以在 [aqt 网站](https://ddalcino.github.io/aqt-list-server/)上查找所需要的包和安装命令, 或使用 Qt 官方安装程序.

### 使用 Qt Creator 构建

1. 在 "项目 > 构建和运行" (Projects > Build & Run) 中选择合适的构建套件.
2. 构建项目.

### 使用 CMake 构建

1. 配置: `cmake -B build .`
2. 构建: `cmake --build build`

### 部署

1. 切换到 exe 文件或 app 文件夹所在目录.
2. 将 Qt 框架打包:
   - Windows 平台: `windeployqt Aijika.exe`
   - Mac 平台: `macdeployqt AI\ 记卡.app -dmg`
3. 在 Windows 平台上, 可用 InnoSetup 制作安装程序.
   详见本仓库 `.github/workflows/windows.yml` 中的流程.

<!-- 目前 Homebrew 安装的 macdeployqt 无法正常工作, 见 https://github.com/orgs/Homebrew/discussions/2823 -->

### 单元测试

1. 设置环境变量: `export AIJIKA_TEST=1`
2. 配置, 并从 GitHub 下载 GoogleTest 库: `cmake -B build .`
3. 构建: `cmake --build build`
4. 运行测试: `./build/aijika_test`

注意部分测试需访问 OpenAI 服务, 默认不会运行. 要运行这些测试:

1. 设置环境变量 `OPENAI_BASE_URL` 和 `OPENAI_API_KEY` (可选).
2. 运行测试: `./build/aijika_test --gtest_also_run_disabled_tests`
