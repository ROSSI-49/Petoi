======================================
2 Petoi + Arduino开发例程
======================================

1.1 第一个Arduino程序：helloWorld：
==================================================
本例程为串口的简单使用，链接烧录器到电脑，配置串口接收器，就能够收到来自于Petoi发出的“helloWorld”

.. literalinclude:: helloWorldCode/helloWorldCode.ino
   :language: c
   :linenos:
   :name: hello.c

1.2 学会说话：串口通讯与串口监视器
==================================================
在前文中，我们已经简单的介绍了Arduino函数对于串口的使用，但ArduinoIDE的串口监视器还有一些设置的细节和应用。串行通讯的实质是协议，收发方按照一定的规则对数据进行编码，发送，接受，解码，从而实现串口的通讯。如果你想更深入的了解Arduino的串口数据形式，协议内容，硬件设计。请参阅： https://www.w3cschool.cn/arduino/arduino_communication.html 和官方文档

+ **串口绘图器的使用**
在进行实验时，经常需要通过串口持续的检测模拟输入的值，那么能将这些数据通过折线图的方式绘制出来，就能帮助我们更好的记录和了解输入情况和变化。

串口绘图仪实际上是从预设的串口获取值并将其绘制在xy轴图。X轴可以说是一个时间实例，读取数据的速度起快，滑动就越快。 Y轴代表来自串口的值，可以是单个也可以是一组 。在读取串口数据时遇到" ``\n`` "（换行或通过 ``Serial.println("")`` ）则表示切换到下一行数据，同行数据的不同组的数据通过( ``,`` )间隔。

例如，如下的数据形式：

    100, 200, 300

    100, 200, 300

    100, 200, 300

    100, 200, 300

最终可以得到三条直线。

在实际的输出中，常常是一个大小不断变化的数值，串口绘图器会根据这些数据自动调整量程，从而来回跳变，为了避免这种变化，可以输入一个很大的常数，绘制直线来限制量程的变化

1.3 模拟信号的读取
==================================================
本例程为模拟信号输入的一个简单例程，也是多种传感器使用的基础。代码如下：

.. literalinclude:: analogRead\analogRead.ino
   :language: c
   :linenos:
   :name: analogRead.c

Arduino的模拟输入的范围为0~1024，即使不接入传感器，我们同样也可以对模拟接口人为的进行干扰(晃一晃，按一按啥的),就能看到数值的变化。该模块的输出同样可以使用串口绘图器及逆行观察。

1.4 数字信号的读取（施工中）
==================================================

1.5 蜂鸣器
==================================================

+ tone()

``tone()`` 函数可以产生固定频率的PWM信号来驱动扬声器发声。发声时间长度和声调都可以通过参数控制。定义发声时间长度有两种方法，第一种是通过 ``tone()`` 函数的参数来定义发声时长，另一种是使用 ``noTone()`` 函数来停止发声。

参数

pin: 发声引脚（该引脚需要连接扬声器）

frequency: 发声频率（单位：赫兹） – 无符号整数型

duration: 发声时长（单位：微秒，此参数为可选参数) – 无符号长整型

返回值:
无

以下为蜂鸣器的示例程序：

.. literalinclude:: toneMelody\toneMelody.ino
   :language: c
   :linenos:
   :name: toneMelody.c

为了实现该程序，还需要使用头文件对声调和对应PWM进行如下的声明

.. literalinclude:: toneMelody\pitches.h
   :language: c
   :linenos:
   :name: pitches.h
   
1.6 光传感器
==================================================

单个光传感器的实例

.. literalinclude:: singleLight\singleLight.ino
   :language: c
   :linenos:
   :name: singleLight.ino

两个光传感器的实例，可以实现对光源的左右位置判断

.. literalinclude:: doubleLight\doubleLight.ino
   :language: c
   :linenos:
   :name: doubleLight.ino
   
1.7 手势传感器
==================================================

.. literalinclude:: gesture\gesture.ino
   :language: c
   :linenos:
   :name: gesture.ino
