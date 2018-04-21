# 配置开发环境
为了能够使项目跨平台开发、运行，我们计划配置如下开发环境：

* OS：&ensp; &ensp; &ensp; &ensp; &ensp;  Mac OS (10.13.4), Windows 10
* Library: &ensp; &ensp; &ensp; Cocos2d-x
* Compiler: &ensp; CMake 3.10.1
* IDE: &ensp; &ensp;&ensp; &ensp; &ensp; &ensp; Qt Creator 4.5.0 (Based on Qt 5.10.0) or CLion 2018.1.1


## 步骤

首先从 [cocos2d-x](http://www.cocos.com/cocos2dx) 官网下载 cocos2d-x zip 包，并解压到一个你能找得到的地方。

我下载的是 cocos2d-x-3.16.zip 以后的版本可能会与这次文档有所出入。

### Mac

打开 Terminal，输入 `nano ~/.bash_profile` ，并按回车打开环境变量配置文件。

增加两行：

``` 
# added by <your name> at <time> for cocos2d-x
export PATH="/Users/<directory>/cocos2d-x-<version>/tools/cocos2d-console/bin:$PATH"
```

其中，\<your name> 替换成你的名字，\<time> 替换成你添加这两行内容时的时间，\<diretory> 替换成你解压到的目录，\<version> 替换成你下载的 cocos2d-x 版本。

如我的解压路径在 “文档” 下，版本为3.16，则代码为：

``` 
# added by Brando at 2018-04-19 22:46:56 for cocos2d-x
export PATH="/Users/brando/Documents/cocos2d-x-3.16/tools/cocos2d-console/bin:$PATH"
```

按 control + x，点击 Y 保存修改，回车确定。

重启 Terminal 后，输入 cocos 可以看到：


```
使用Cocos命令行工具开发时，Cocos会搜集开发环境下的使用数据。该数据仅用于汇总分析，并不断创新和改进Cocos产品。收集的数据是匿名的，只位于开发端，包括但不限于：唯一的设备标识，软件版本号，Cocos相关工具产品和具体功能的使用情况。我们将严格保密您的个人隐私，绝不会分享或出售这些数据。您可以选择拒绝分享这些数据，但通过分享这些数据可以帮助Cocos成长。

您是否同意发送数据？[Y]同意，[N]不同意
```

根据自身需要选择。

接着它会提示：

``` 
可用的命令：
	run              在设备或者模拟器上编译，部署和运行工程。
	gen-libs         生成引擎的预编译库。生成的库文件会保存在引擎根目录的 'prebuilt' 文件夹。
	luacompile       对 lua 文件进行加密和编译为字节码的处理。
	deploy           编译并在设备或模拟器上部署工程。
	package          管理 cocos 中的 package。
	compile          编译并打包工程。
	gen-simulator    生成 Cocos 模拟器。
	new              创建一个新的工程。
	jscompile        对 js 文件进行加密和压缩处理。

可用的参数：
	-h, --help			显示帮助信息。
	-v, --version			显示命令行工具的版本号。
	--ol ['en', 'zh', 'zh_tr']	指定输出信息的语言。
	--agreement ['y', 'n']		使用指定的值来同意或拒绝协议。

示例：
	cocos new --help
	cocos run --help
```

若出现上述内容则说明 cocos 命令已加入环境变量。

输入 `cocos new --help` 查看新建 cocos 项目的命令帮助。

``` 
usage: cocos new [-h] [-p PACKAGE_NAME] [-d DIRECTORY] [-t TEMPLATE_NAME]
                 [--ios-bundleid IOS_BUNDLEID] [--mac-bundleid MAC_BUNDLEID]
                 [-e ENGINE_PATH] [--portrait] -l {cpp,lua,js}
                 [PROJECT_NAME]

创建一个新的工程。

positional arguments:
  PROJECT_NAME          设置工程名称。

optional arguments:
  -h, --help            show this help message and exit
  -p PACKAGE_NAME, --package PACKAGE_NAME
                        设置工程的包名。
  -d DIRECTORY, --directory DIRECTORY
                        设置工程存放路径。
  -t TEMPLATE_NAME, --template TEMPLATE_NAME
                        设置使用的模板名称。
  --ios-bundleid IOS_BUNDLEID
                        设置工程的 iOS Bundle ID。
  --mac-bundleid MAC_BUNDLEID
                        设置工程的 Mac Bundle ID。
  -e ENGINE_PATH, --engine-path ENGINE_PATH
                        设置引擎路径。
  --portrait            设置工程为竖屏。
  -l {cpp,lua,js}, --language {cpp,lua,js}
                        设置工程使用的编程语言，可选值：[cpp |
                        lua | js]
```

接着执行命令：

```
cocos new -l cpp --mac-bundleid MAC_BUNDLEID -d /Users/brando/Documents/GitHub/BombingAdventure_central BombingAdventure
```

以在工作目录下生成一个名为 `BombingAdventure` 的 cocos 工程文件。（如果已经在 GitHub 中 clone 了该项目，则不用执行此命令新建项目）

在 ` BombingAdventure/cocos2d/cocos/audio/apple/AudioEngine-inl.h` line 36 中加入 

` #include <list>` 

以解决

```
/Users/brando/Documents/GitHub/testCocos/MyCppGame/cocos2d/cocos/audio/apple/AudioEngine-inl.h:77: error: no template named 'list' in namespace 'std'
    std::list<ALuint> _unusedSourcesPool;
    ~~~~~^
```

之类的 error。

在 IDE 中选择 `打开文件或项目` ，选择用 CMake 作为编译器，选中 `CMakeLists.txt` ，点击 `构建 (Build)` 再运行一下，检查环境是否配置正常。

**注意每次 push 到 GitHub 之前先 clean 一下项目，并在 GitHub 客户端检查一下代码的增删部分，避免意料之外的编译错误** 

### Windows

待补充，应该也是解压完之后先将 cocos 命令添加进环境变量中，其他内容应该是一样的。




