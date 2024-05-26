# seccomp-jail

## 项目描述

在deepin操作系统中，基于seccomp开发一个程序。 其可以根据用户的选择动态地对该程序直接或间接启动的子进程产生的系统调用进行过滤。

## 赛题

能够根据固定的规则对直接/间接启动的进程的系统调用进行过滤;

能够动态地对直接/间接启动的进程的系统调用进行过滤， 指当系统调用发生以后弹出窗口展示程序的系统参数， 根据用户的选择对系统调用进行放行；

能够动态地根据用户输入生成对应系统调用的结果。

## 赛题完成情况

&#9745;能够根据固定的规则对直接/间接启动的进程的系统调用进行过滤;

&#9745;能够动态地对直接/间接启动的进程的系统调用进行过滤， 指当系统调用发生以后弹出窗口展示程序的系统参数， 根据用户的选择对系统调用进行放行；

&#9745;能够动态地根据用户输入生成对应系统调用的结果。

## 原理介绍

### PTRACE

ptrace是linux下一个强大的系统调用，可以通过它来调试其他进程。它提供了一种方法让一个进程（Tracer）可以观察和控制另一个进程的执行（Tracee），并检查和更改Tracee的存储和寄存器。它主要用于实现断点调试和系统调用跟踪。

### SECCOMP

seccomp是Linux内核提供的一种安全机制，用于在用户态应用程序执行系统调用时进行过滤和限制。其原理是基于对系统调用号的过滤和限制，以及对系统调用参数的校验。当一个应用程序启动时，它可以使用seccomp机制来加载一个过滤器，该过滤器指定了允许或禁止执行的系统调用。在应用程序执行系统调用时，seccomp会根据过滤器的规则进行匹配和处理。


### linux下的进（线）程

linux下的线程其实是“轻量级”进程，在内核中都用task_struct的结构表示。故ptrace和seccomp对进程和线程的行为大致是相同的。

### 软件架构

## 代码目录索引

## 使用说明

### 编译/安装

下载打包好的Release版本即可使用；如需自行编译源码运行，且环境中原已有Fluentui控件库，请注意编译此项目时会导致其中一些控件的行为被改变。

### 页面介绍

#### 主界面
![image](https://github.com/111usionn/seccomp-jail/assets/163122109/116b584a-1d9c-426e-a803-6e6910e27aaf)

在此界面启动程序、手动处理系统调用

#### 规则编辑
![image](https://github.com/111usionn/seccomp-jail/assets/163122109/cfd61963-021b-4344-832b-08e171b1f3dd)

在此界面创建、加载、修改、保存规则文件

#### 主动执行
![image](https://github.com/111usionn/seccomp-jail/assets/163122109/ea25ee29-8af4-4c08-a8bf-d682c1443263)

在此界面上方显示目标程序进程/线程树，下方提供主动执行系统调用的接口

#### 日志
![image](https://github.com/111usionn/seccomp-jail/assets/163122109/0c1e77bf-d668-4fab-974a-b448e0e093f4)

此界面显示日志，包括自动审批的和用户手动审批的。

### 使用流程

#### 编辑规则

#### 编辑目标程序路径和参数

#### 启动程序并监测系统调用

#### 主动执行系统调用

#### 查看日志

## 未来扩展功能

&#9744;启动并监控远程计算机上的程序

&#9744;可以对每个子进程（线程）应用不同的规则文件
