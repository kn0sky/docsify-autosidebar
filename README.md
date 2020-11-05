# docsify-autosidebar
 一个小工具用于自动生成Docsify的侧边栏文件_sidebar.md
 ## 准备:
 Docsify博客要需要提前安装好侧边栏折叠插件: https://github.com/iPeng6/docsify-sidebar-collapse
 
 ## 使用方法:
 1. 从[Release](https://github.com/kn0sky/docsify-autosidebar/releases)下载本软件
 2. 将本软件放入你的Docsify根目录下
 3. 双击运行即可自动生成_sidebar.md,当然,可以先备份自己原来的_sidebar.md以防万一

## 更新
### v1.1:
新增：sidebar.md 里不会添加以下划线_开头的目录文件，资源文件等可以下划线_开头来存储

修改：每个目录标题的链接为目录内的README.md，目录内的文件不再显示README.md

## 效果演示:
生成效果:
```md
<!-- docs/_sidebar.md created by koko-docsify_sidebarTool -->

- [Hook技术](Hook技术/README.md)
  - [InlineHook](Hook技术/InlineHook.md)
- [PE结构相关](PE结构相关/README.md)
  - [导入表-C-遍历](PE结构相关/导入表-C-遍历.md)
  - [导入表-Cpp-遍历](PE结构相关/导入表-Cpp-遍历.md)
  - [导出表-C-遍历](PE结构相关/导出表-C-遍历.md)
- [启动技术](启动技术/README.md)
  - [导出表-C-遍历](启动技术/导出表-C-遍历.md)
- [自启动技术](自启动技术/README.md)
  - [自启动-C-启动目录](自启动技术/自启动-C-启动目录.md)
  - [自启动-C-注册表](自启动技术/自启动-C-注册表.md)
  - [自启动-C-计划任务](自启动技术/自启动-C-计划任务.md)
- [README](README.md)
```
