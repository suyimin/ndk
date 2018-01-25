# ndk

Ndk demos，use the NDK and CMake to compile C and C++ code into a native library.

对JNI不了解的同学，请移步
[JNI](https://github.com/suyimin/ndk/blob/master/jni.md)

对CMake不了解的同学，请移步
[CMake](https://github.com/suyimin/ndk/blob/master/CMake.md)

### app
app是jni示例。

返回类型 jstring 是在 Java 原生接口规格中定义的数据类型。 它是指向 Java 字符串的指针，并非真正的字符串。
返回 jstring 后，接下来是根据 Java 函数名和函数名所在文件的路径返回的函数名。 函数名根据以下规则构建：
* 在名称前面加上 Java_。
* 描述与顶级源目录相关的文件路径。
* 使用下划线代替正斜杠。
* 删掉 .java 文件扩展名。
* 在最后一个下划线后，附加函数名。
按照这些规则，此示例使用的函数名为 Java_com_example_ndk_MainActivity_stringFromJNI。 此名称描述 com/example/ndk/MainActivity.java 中一个名为 stringFromJNI()的 Java 函数。

JNIEnv* 是指向虚拟机的指针，jobject 是指向从 Java 端传递的隐式 this 对象的指针。


### classic-teapot more-teapots choreographer-30fps
* classic-teapot 普通3D茶壶的示例。<br>
* more-teapots 自动旋转的3D茶壶的阵列示例。<br>
* choreographer-30fps 限制最高帧率为30fps的3D茶壶的示例。<br><br>
此示例展示 ndk_helper 帮助程序类，其中包含的许多原生帮助程序函数是以原生应用的形式实现游戏和类似应用所必需的。 此类提供：<br>
* 用于处理某些 NDK 特有行为的抽象层 GLContext。<br>
* 虽然很有用，但 NDK 中却不存在的一些帮助程序函数（例如，点按侦测）。<br>
* 供 JNI 用于调用平台功能（例如，材质加载）的包装器。


### native
native是一个纯原生应用示例，不包含任何 Java 源代码。
Android SDK 提供帮助程序类 NativeActivity，可用于写入完全原生的 Activity。NativeActivity 可处理 Android 框架与原生代码之间的通信，因此您不必为其创建子类或调用其方法， 只需在 AndroidManifest.xml 文件中声明要设为原生的应用，然后开始创建原生应用。<br>
以下代码行将 android:hasCode 声明为 false，因为此应用仅包含原生代码 – 没有 Java 代码。<br>
\<application android:label="@string/app_name"
android:hasCode="false"><br>
下一行代码声明 NativeActivity 类。<br>
\<activity android:name="android.app.NativeActivity"<br>
最后，清单删掉开头的 lib 和末尾的 .so 扩展名，指定 android:value 作为要构建的共享库的名称。 此值必须与 CMakeLists.txt中 add_library 中配置的名称相同。<br>
\<meta-data android:name="android.app.lib_name"
        android:value="native-activity" /><br>
创建用于原生 Activity 的文件，并实现 ANativeActivity_onCreate 变量中指定的函数void android_main(struct android_app* state)。应用在原生 Activity 启动时会调用此函数。 此函数类似于 C/C++ 中的 main，用于接收 ANativeActivity 结构的指针，其中包含您需要写入的各个回调实现的函数指针。<br>

### audio-echo native-audio
audio-echo、 native-audio 是OpenSL ES 的 NDK 实现的示例。<br>
audio-echo是一个原生的回声应用。<br>
native-audio是一个原生的录音音频播放器。<br>

### bitmap-plasma、native-plasma
bitmap-plasma、native-plasma 是C生成的等离子表面应用示例。
bitmap-plasma 使用了java里面的View和Bitmap。
native-plasma 是一个纯原生应用。

### endless-tunnel
endless-tunnel(无尽的隧道)是一个纯原生游戏。

### sensor-graph
sensor-graph是利用感应器原生api获得加速度，OpenGL ES 2.0绘图的原生应用示例。

### san-angeles
OpenGL ES 1.0 3D模型展示。

### native-media
OpenMAXAL、 java MediaPlayer、native MediaPlayer示例。

### native-codec
OpenMAXAL mediandk 播放mp4示例。

### camera-basic camera-texture
本地照相机示例。

### display-p3
Api26新增加的 p3 显示图片和 sRGB 显示图片对比。

### nn_sample
Api27新增加的 NeuralNetworks Api 示例。

### webp
利用webp显示图片的纯原生应用示例。
