======================================
2 Petoi + Arduino开发例程
======================================

1.0 准备工作——烧写Opencat框架
=======================================

下述例程中，有以下的几个例程需要在Opencat框架下进行开发：

+ 通过token+cmd的方式对机器人实现代码控制

+ 动作组详解（Petoi的方法调用和设计动作组）

+ 实现光线跟随

+ 根据手势完成动作组

+ 写一个自己的蓝牙遥控器

+ 超声波实现跟随

这些代码请在Opencat框架下进行修改，Opencat的烧录请参阅： https://docs.petoi.com/v/chinese/arduino-ide/wei-nyboard-shang-chuan-cheng-xu#xia-zai-opencat-ruan-jian-bao

关于代码包中的文件框架以及token+cmd控制解读请参阅： `OpenCat程序框架 <https://petoi-temp.readthedocs.io/en/latest/Petoi/petoi_guide/introduce.html#petoi-opencat>`_

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

.. literalinclude:: analogRead/analogRead.ino
   :language: c
   :linenos:
   :name: analogRead.c

Arduino的模拟输入的范围为0~1024，即使不接入传感器，我们同样也可以对模拟接口人为的进行干扰(晃一晃，按一按啥的),就能看到数值的变化。该模块的输出同样可以使用串口绘图器及逆行观察。

1.4 数字信号的读取（施工中）
==================================================

1.5 输出PWM信号
==================================================

PWM波常用来进行舵机等的控制，在Arduino的内置库中集成了 ``Servo.h`` 用来完成对于伺服电机的控制。库提供了两种方法：

``Knob`` : 用电位器控制伺服的位置。

``Sweep`` : 扫描伺服电机前进后退的轴。

具体的使用可查看IDE中所提供的示例

同样，Arduino也设计了用来控制步进电机的库文件 ``Stepper.h``。
更普遍的情况是，你需要自己来产生一个具有特定性质(频率，参考电压，占空比等)的PWM波，有两种较为常见的方法来实现：

1、利用循环和延时在主程序中实现PWM波的输出，代码如下：

.. code-block:: c
   :linenos:

   void loop()
   {
      digitalWrite(13, HIGH);
      delayMicroseconds(100); // Approximately 10% duty cycle @ 1KHz
      digitalWrite(13, LOW);
      delayMicroseconds(1000);
   }

这样实现的PWM波的漏洞是很大的他对于资源的占用很多，且由于循环本身存在延时，程序较为繁杂的时候，延时误差很大，如果是其他的单片机，我们常常通过一个中断的方式输出PWM，利用现有的时钟进行触发，仅通过分频就能够实现十分精准的周期控制。Arduino也有类似的操作。Arduino内置了三个定时器：Timer0负责控制delay等函数，一般不做改动；Timer1的计数器是16位的；因此我们一般对Timer2来进行分频，实现不同的频率，占空比的PWM输出，参考代码如下：

.. code-block:: c
   :linenos:

   void setup() {
      // put your setup code here, to run once:

      pinMode(3, OUTPUT); 
      pinMode(11, OUTPUT); 
      
      TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); //Set Timer2 to varying top limit fast PWM mode
      TCCR2B = _BV(WGM22) | _BV(CS22) | _BV(CS21) | _BV(CS20);//another way to set prescaler CS2=fff
      
      OCR2A = 155; //Top value A
      OCR2B = 30; //Toggle value B, Output at pin 3
      
      //CS2  Divisor  Frequency
      //001    1        31372.55
      //010    8        3921.16
      //011    32       980.39
      //100    64       490.20   <--DEFAULT
      //101    128      245.10
      //110    256      122.55
      //111    1024     30.64
   }

   void loop() {
   // put your main code here, to run repeatedly:

   }

接下来简要解读这部分的代码。首先是 ``pinMode()`` 这个函数的功能已经在前文中叙述过了。可以发现这里选择的引脚是 ``pin3`` 和 ``pin4`` 这是因为 ``Timer2`` 所控制的 ``pin`` 脚正是3和11；如果想了解其他 ``pin`` 的设置，请参阅Arduino对应开发板的官方手册(datasheet)。

TCCR2A/B是用来控制Timer2计数器的模式与预除数的大小从而实现对于主时钟的分频，它名字中的2就是此意，CS2位是来控制Timer2计数器预除数的。以本示例中的代码为例： _BV(CS22) | _BV(CS21) | _BV(CS20)的三部分由逻辑按位或“|”连接；每个BV是按位赋注（bit value）的意思；_BV(CS22 )= 在CS2里，1<<2(把1左移2位) = 00000100；得到三部分分别是00000100，00000010，00000001；按位或最终得到0111；查代码里的表得到对应的预除数是1024。这样，我们所得到的实际频率就是：16 MHz / 1024

OCR2A/B：这是计时器中的两个比较寄存器，OCR2A控制pin11的占空比，OCR2B控制pin3的占空比。计时器中还有一个0~255的计数器。每过一个时钟周期，这个计数器的数目就+1，当数目达到255后就自动清零。这个比较寄存器的实际作用是当计数器的数比其小的时候，输出为高电平，比其高的时候输出为低电平。

显然，经过0~255的过程才是完成了一个PWM的周期，所以实际的PWM输出就是 16 MHz / 1024 / 64

1.6 蜂鸣器
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

.. literalinclude:: toneMelody/toneMelody.ino
   :language: c
   :linenos:
   :name: toneMelody.c

为了实现该程序，还需要使用头文件对声调和对应PWM进行如下的声明

.. literalinclude:: toneMelody/pitches.h
   :language: c
   :linenos:
   :name: pitches.h
   
1.7 光传感器
==================================================

单个光传感器的实例

.. literalinclude:: singleLight/singleLight.ino
   :language: c
   :linenos:
   :name: singleLight.ino

两个光传感器的实例，可以实现对光源的左右位置判断

.. literalinclude:: doubleLight/doubleLight.ino
   :language: c
   :linenos:
   :name: doubleLight.ino
   
1.8 手势传感器
==================================================

.. literalinclude:: gesture/gesture.ino
   :language: c
   :linenos:
   :name: gesture.ino

1.9 动作组详解
==================================================

Bittle的动作数据通过数组的形式储存在文件InstinctBittle.h中，通过cmd＋token的方式来实现调用。接下来让我们来看一下数组中的每个变量的具体含义，示例代码如下：

.. code-block:: c
   :linenos:

   const int8_t balance[] PROGMEM = { 
   1, 0, 0, 1,
      0,   0,   0,   0,   0,   0,   0,   0,  30,  30,  30,  30,  30,  30,  30,  30,};

首先是第一个数，此处为1，这个数的主要作用有两个，给出动作执行的帧以及动作执行的种类，Opencat设计了三种动作分类：

+ **行为**:这个数为负数的时候表示为一个行为，一般可以包含多帧，负几就是几帧，行为的特点是一般单次调用只被执行一次，就会还原

+ **步态**:第一个数为＞1的正数，一个不太可以包含多帧，实际调用时，每次调用都会循环执行这个动作，直到停止

+ **姿势**:第一个数为1，只包含一个动作帧

数组中第 2 个元素和第 3 个元素表示身体方向期望值（对应身体的横滚角和俯仰角），单位是度。如果开启了陀螺仪mpu6050，则机器狗会在不稳定的时候，尽可能保持该身体的俯仰角。

这三个是较为常用的改动位置，其余的数据只要了解即可，实际使用的时候，通过桌面程序生成要方便的多。

技能数组中第4个元素表示角度比率。由于数据结构的限制，数字中的每一位的储存空间为-127~127，当需要存储超出 -128 到 127 范围内的角度值时，可以增大角度比率值。比如将角度比率设置为 2，技能数组中所有关节舵机的角度值乘以2才是舵机的实际旋转角度。

之后的一行数据表示了一个帧内，机器狗的相关动作，实际上也就是机器狗各个舵机的角度，具体的角度换算，已经在官方文档中给出，请参阅： https://docs.petoi.com/v/chinese/ying-yong-shi-li/ji-neng-chuang-zuo#duo-ji-xu-hao-ji-qi-jiao-du-zhi-indexed-joint-angles

了解了动作组的数据结构，我们来尝试设计实现一个动作组吧！让机器狗实现一个动作组，主要需要了解以下的问题：

+ 如何设计一个动作组

+ 如何将自己设计的动作组写入程序

+ 如何完成对于动作组的调用

首先是如何实际一个自己想要的动作组，这里推荐的是使用桌面程序导出的方式，这样能够近似于可视化的实现设计，官方文档已经给出了操作方法，请查阅： https://docs.petoi.com/v/chinese/zhuo-mian-ying-yong/ji-neng-chuang-zuo-fang

如何将设计好的动作写入程序，首先需要了解Opencat对于动作的分类，Opencat框架为了节省有限的存储空间，将动作分为两类：本能和技能；I2C EEPROM (8KB) 存储本能，而Flash (与Arduino程序代码分享32KB存储空间) 存储技能。每个技能数组名称加了一个后缀，“N”表示是新技，“I”表示是本能。一个代码的示例如下：

.. code-block:: c
   :linenos:

     const char* skillNameWithType[]={"bdFI","bkI","bkLI","crFI","crLI","mhFI","mhLI","pcFI","phFI","phLI","trFI","trLI","vtFI","vtLI","wkFI","wkLI","balanceI","buttUpI","calibI","droppedI","liftedI","restI","sitI","strI","zeroN","bfI","ckI","climbCeilI","fdI","hiI","jyI","pdI","peeI","puI","rcI","rtI","stpI","testServoI",};
   #if !defined(MAIN_SKETCH) || !defined(I2C_EEPROM)
         //if it's not the main sketch to save data or there's no external EEPROM, 
         //the list should always contain all information.
      const int8_t* progmemPointer[] = {bdF, bk, bkL, crF, crL, mhF, mhL, pcF, phF, phL, trF, trL, vtF, vtL, wkF, wkL, balance, buttUp, calib, dropped, lifted, rest, sit, str, zero, bf, ck, climbCeil, fd, hi, jy, pd, pee, pu, rc, rt, stp, testServo, };
   #else	//only need to know the pointers to newbilities, because the intuitions have been saved onto external EEPROM,
         //while the newbilities on progmem are assigned to new addresses
      const int8_t* progmemPointer[] = {zero, };

``skillNameWithType`` 中，储存了所有补全后缀的动作的名称，添加新动作的时候，请根据种类将其添加到该列表中；下面的 ``#if`` 中的语句主要用于上传配置程序时读取， ``else`` 中的语句则用于上传主程序的时候重新读取对应的动作组。这个比喻是很形象的，就像本能是先天就会(配置在主板EEPROM上，掉电不会消失)的，而新技能是要重新学习的，可以改变的(存储在Flash中，每次烧写主程序的时候都会改变)本能和技能的区别体现在程序上是，在完成主板配置之后，只烧录主程序，则职能修改其技能，而对于本能的修改不会生效。

那么如何将一个动作添加到程序中呢？首先进行程序代码的修改，先把代表对应动作组的数组复制到 ``InstinctBittle.h`` 中，如果想添加一个技能，就要在上述的三个列表中，都增加对应的一项；如果想要添加一个本能，则需要在前两个项目中添加对应的项。之后需要进行配置文件的烧写，注意：不是主程序文件，烧写方法参考 `配置方法 <https://docs.petoi.com/v/chinese/arduino-ide/wei-nyboard-shang-chuan-cheng-xu#shang-chuan-cheng-xu-gu-jian>`_ 之后在进行主程序代码的烧写即可。

如果想对现有的动作进行修改，且修改的是技能，则直接在 ``InstinctBittle.h`` 中进行修改后重新烧写主程序即可，若是对本能进行修改，则需要进行配置文件的烧写。

最后，如何控制其做出相关动作呢？Petoi采用的是token和cmd的方式，想要更具体的了解请查看 `token+cmd <https://petoi-temp.readthedocs.io/en/latest/Petoi/petoi_guide/introduce.html#opencat-tokencmd>`_ 这里只提供一个简单的示例，假如我想调用已经写好的 ``zero`` 动作组，这只需要使用以下段的代码：

.. code-block:: c
   :linenos:

   strcpy(newCmd, "zero");
   token = T_SKILL;

另外一种方式是直接通过串口通讯来发出指令，这种方式在多个设备间的通讯以及远程烧录调试的时候显得尤其方便。同时他是的我们能够把一些繁复的计算通过其他外设的主板(例如openmv)中来进行，只需要对机器狗发出命令就可以了。他的实质与token+cmd的方法是一样的，只是定义了一套串口通信协议，关于这套串口协议的说明， `官方文档 <https://docs.petoi.com/v/chinese/api/chuan-kou-xie-yi>`_ 给出了详细的说明。