# ndk

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

### native
native是一个非常简单的纯原生应用示例，不包含任何 Java 源代码。
以下代码行将 android:hasCode 声明为 false，因为此应用仅包含原生代码 – 没有 Java 代码。
<application android:label="@string/app_name"
android:hasCode="false">
下一行代码声明 NativeActivity 类。
<activity android:name="android.app.NativeActivity"
最后，清单删掉开头的 lib 和末尾的 .so 扩展名，指定 android:value 作为要构建的共享库的名称。 此值必须与 Android.mk 中 LOCAL_MODULE 的名称相同。
<meta-data android:name="android.app.lib_name"
        android:value="native-activity" />

