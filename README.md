# ndk
### ndk demo

返回类型 jstring 是在 Java 原生接口规格中定义的数据类型。 它是指向 Java 字符串的指针，并非真正的字符串。
返回 jstring 后，接下来是根据 Java 函数名和函数名所在文件的路径返回的函数名。 函数名根据以下规则构建：
* 在名称前面加上 Java_。
* 描述与顶级源目录相关的文件路径。
* 使用下划线代替正斜杠。
* 删掉 .java 文件扩展名。
* 在最后一个下划线后，附加函数名。
按照这些规则，此示例使用的函数名为 Java_com_example_ndk_MainActivity_stringFromJNI。 此名称描述 com/example/ndk/MainActivity.java 中一个名为 stringFromJNI()的 Java 函数。

JNIEnv* 是指向虚拟机的指针，jobject 是指向从 Java 端传递的隐式 this 对象的指针。
