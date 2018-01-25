# CMake入门
Android Studio 用于构建原生库的默认工具是 CMake。<br>
使用CMake之前，请确认SDK Manager已经安装了LLDB、CMake 和 NDK。<br>

### 创建支持 C/C++ 的新项目
在向导的 Configure your new project 部分，选中 Include C++ Support 复选框。<br>
在向导的 Customize C++ Support 部分，您可以使用下列选项自定义项目：<br>
C++ Standard：使用下拉列表选择您希望使用哪种 C++ 标准。选择 Toolchain Default 会使用默认的 CMake 设置。<br>
Exceptions Support：如果您希望启用对 C++ 异常处理的支持，请选中此复选框。如果启用此复选框，Android Studio 会将 -fexceptions 标志添加到模块级 build.gradle 文件的 cppFlags 中，Gradle 会将其传递到 CMake。<br>
Runtime Type Information Support：如果您希望支持 RTTI，请选中此复选框。如果启用此复选框，Android Studio 会将 -frtti 标志添加到模块级 build.gradle 文件的 cppFlags 中，Gradle 会将其传递到 CMake。<br>

在 Android Studio 完成新项目的创建后，请从 IDE 左侧打开 Project 窗格并选择 Android 视图。Android Studio 将添加 cpp 和 External Build Files 组：<br>
在 cpp 组中，您可以找到属于项目的所有原生源文件、标头和预构建库。对于新项目，Android Studio 会创建一个示例 C++ 源文件 native-lib.cpp，并将其置于应用模块的 src/main/cpp/ 目录中。示例代码提供了一个简单的 C++ 函数 stringFromJNI()，此函数可以返回字符串“Hello from C++”。<br>
在 External Build Files 组中，Android Studio 会创建一个 CMake 构建脚本 CMakeLists.txt，并将其置于模块的根目录中。与 build.gradle 文件指示 Gradle 如何构建应用一样，CMake构建脚本指示如何构建您的原生库。<br>

### 构建和运行示例应用
点击 Run 从菜单栏运行应用 后，Android Studio 将在您的 Android 设备或者模拟器上构建并启动一个显示文字“Hello from C++”的应用。下面的概览介绍了构建和运行示例应用时会发生的事件：<br>
Gradle 调用您的外部构建脚本 CMakeLists.txt。<br>
CMake 按照构建脚本中的命令将 C++ 源文件 native-lib.cpp 编译到共享的对象库中，并命名为 libnative-lib.so，Gradle 随后会将其打包到 APK 中。<br>
运行时，应用的 MainActivity 会使用 System.loadLibrary() 加载原生库。现在，应用可以使用库的原生函数 stringFromJNI()。<br>
MainActivity.onCreate() 调用 stringFromJNI()，这将返回“Hello from C++”并使用这些文字更新 TextView。<br>
注：Instant Run 与使用原生代码的项目不兼容。Android Studio 会自动停用此功能。<br>
>如果您想要验证 Gradle 是否已将原生库打包到 APK 中，可以使用 APK 分析器：<br>
>选择 Build > Analyze APK。<br>
>从 app/build/outputs/apk/ 目录中选择 APK 并点击 OK。<br>
>您会在 APK 分析器窗口的 lib/\<ABI>/ 下看到 libnative-lib.so。<br>

### 向现有项目添加 C/C++ 代码
如果您希望向现有项目添加原生代码，请执行以下步骤：<br>
创建新的原生源文件并将其添加到您的 Android Studio 项目中。<br>
创建 CMake 构建脚本，将您的原生源代码构建到库中。如果导入和关联预构建库或平台库，您也需要此构建脚本。<br>
提供一个指向您的 CMake 脚本文件的路径，将 Gradle 关联到您的原生库。Gradle 使用构建脚本将源代码导入您的 Android Studio 项目并将原生库（SO 文件）打包到 APK 中。<br>
配置完项目后，您可以使用 JNI 框架从 Java 代码中访问您的原生函数。要构建和运行应用，只需点击 Run 从菜单栏运行应用。Gradle 会以依赖项的形式添加您的外部原生构建流程，用于编译、构建原生库并将其随 APK 一起打包。<br>

### 创建新的原生源文件
要在应用模块的主源代码集中创建一个包含新建原生源文件的 cpp/ 目录，请按以下步骤操作：<br>
从 IDE 的左侧打开 Project 窗格并从下拉菜单中选择 Project 视图。<br>
导航到 您的模块 > src，右键点击 main 目录，然后选择 New > Directory。<br>
为目录输入一个名称（例如 cpp）并点击 OK。<br>
右键点击您刚刚创建的目录，然后选择 New > C/C++ Source File。<br>
为您的源文件输入一个名称，例如 native-lib。<br>
从 Type 下拉菜单中，为您的源文件选择文件扩展名，例如 .cpp。<br>
点击 Edit File Types ，您可以向下拉菜单中添加其他文件类型，例如 .cxx 或 .hxx。在弹出的 C/C++ 对话框中，从 Source Extension 和 Header Extension 下拉菜单中选择另一个文件扩展名，然后点击 OK。<br>
如果您还希望创建一个标头文件，请选中 Create an associated header 复选框。<br>
点击 OK。<br>

### 创建 CMake 构建脚本
如果您的原生源文件还没有 CMake 构建脚本，则您需要自行创建一个并包含适当的 CMake 命令。CMake 构建脚本是一个纯文本文件，您必须将其命名为 CMakeLists.txt。<br>
要创建一个可以用作 CMake 构建脚本的纯文本文件，请按以下步骤操作：<br>
从 IDE 的左侧打开 Project 窗格并从下拉菜单中选择 Project 视图。<br>
右键点击 您的模块 的根目录并选择 New > File。<br>
注：您可以在所需的任意位置创建构建脚本。不过，在配置构建脚本时，原生源文件和库的路径将与构建脚本的位置相关。<br>
输入“CMakeLists.txt”作为文件名并点击 OK。<br>
现在，您可以添加 CMake 命令，对您的构建脚本进行配置。要指示 CMake 从原生源代码创建一个原生库，请将 cmake_minimum_required() 和 add_library() 命令添加到您的构建脚本中：<br>
\# Sets the minimum version of CMake required to build your native library.<br>
\# This ensures that a certain set of CMake features is available to<br>
\# your build.<br>
cmake_minimum_required(VERSION 3.4.1)<br>
\# Specifies a library name, specifies whether the library is STATIC or<br>
\# SHARED, and provides relative paths to the source code. You can<br>
\# define multiple libraries by adding multiple add.library() commands,<br>
\# and CMake builds them for you. When you build your app, Gradle<br>
\# automatically packages shared libraries with your APK.<br>
add_library( # Specifies the name of the library.<br>
             native-lib<br>
             # Sets the library as a shared library.<br>
             SHARED<br>
             # Provides a relative path to your source file(s).<br>
             src/main/cpp/native-lib.cpp )<br>
使用 add_library() 向您的 CMake 构建脚本添加源文件或库时，Android Studio 还会在您同步项目后在 Project 视图下显示关联的标头文件。不过，为了确保 CMake 可以在编译时定位您的标头文件，您需要将 include_directories() 命令添加到 CMake 构建脚本中并指定标头的路径：<br>
add_library(...)<br>
\# Specifies a path to native header files.<br>
include_directories(src/main/cpp/include/)<br>
CMake 使用以下规范来为库文件命名：<br>
lib库名称.so<br>
例如，如果您在构建脚本中指定“native-lib”作为共享库的名称，CMake 将创建一个名称为 libnative-lib.so 的文件。不过，在 Java 代码中加载此库时，请使用您在 CMake 构建脚本中指定的名称：<br>
static {<br>
    System.loadLibrary(“native-lib”);<br>
}<br>
注：如果您在 CMake 构建脚本中重命名或移除某个库，您需要先清理项目，Gradle 随后才会应用更改或者从 APK 中移除旧版本的库。要清理项目，请从菜单栏中选择 Build > Clean Project。<br>
Android Studio 会自动将源文件和标头添加到 Project 窗格的 cpp 组中。使用多个 add_library() 命令，您可以为 CMake 定义要从其他源文件构建的更多库。<br>

### 添加 NDK API
Android NDK 提供了一套实用的原生 API 和库。通过将 NDK 库包含到项目的 CMakeLists.txt 脚本文件中，您可以使用这些 API 中的任意一种。<br>
预构建的 NDK 库已经存在于 Android 平台上，因此，您无需再构建或将其打包到 APK 中。由于 NDK 库已经是 CMake 搜索路径的一部分，您甚至不需要在您的本地 NDK 安装中指定库的位置 - 只需要向 CMake 提供您希望使用的库的名称，并将其关联到您自己的原生库。<br>
将 find_library() 命令添加到您的 CMake 构建脚本中以定位 NDK 库，并将其路径存储为一个变量。您可以使用此变量在构建脚本的其他部分引用 NDK 库。以下示例可以定位 Android 特定的日志支持库并将其路径存储在 log-lib 中：<br>
find_library( # Defines the name of the path variable that stores the<br>
              \# location of the NDK library.<br>
              log-lib<br>
              \# Specifies the name of the NDK library that<br>
              \# CMake needs to locate.<br>
              log )<br>
为了确保您的原生库可以在 log 库中调用函数，您需要使用 CMake 构建脚本中的 target_link_libraries() 命令关联库：<br>
find_library(...)<br>
\# Links your native library against one or more other native libraries.<br>
target_link_libraries( # Specifies the target library.<br>
                       native-lib<br>
                       \# Links the log library to the target library.<br>
                       \${log-lib} )<br>
NDK 还以源代码的形式包含一些库，您在构建和关联到您的原生库时需要使用这些代码。您可以使用 CMake 构建脚本中的 add_library() 命令，将源代码编译到原生库中。要提供本地 NDK 库的路径，您可以使用 ANDROID_NDK 路径变量，Android Studio 会自动为您定义此变量。<br>
以下命令可以指示 CMake 构建 android_native_app_glue.c，后者会将 NativeActivity 生命周期事件和触摸输入置于静态库中并将静态库关联到 native-lib：<br>
add_library( app-glue<br>
             STATIC<br>
             \${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c )<br>
\# You need to link static libraries against your shared native library.<br>
target_link_libraries( native-lib app-glue ${log-lib} )<br>
### 添加其他预构建库
添加预构建库与为 CMake 指定要构建的另一个原生库类似。不过，由于库已经预先构建，您需要使用 IMPORTED 标志告知 CMake 您只希望将库导入到项目中：<br>
add_library( imported-lib<br>
             SHARED<br>
             IMPORTED )<br>
然后，您需要使用 set_target_properties() 命令指定库的路径，如下所示。<br>
某些库为特定的 CPU 架构（或应用二进制接口 (ABI)）提供了单独的软件包，并将其组织到单独的目录中。此方法既有助于库充分利用特定的 CPU 架构，又能让您仅使用所需的库版本。要向 CMake 构建脚本中添加库的多个 ABI 版本，而不必为库的每个版本编写多个命令，您可以使用 ANDROID_ABI 路径变量。此变量使用 NDK 支持的一组默认 ABI，或者您手动配置 Gradle 而让其使用的一组经过筛选的 ABI。例如：<br>
add_library(...)<br>
set_target_properties( # Specifies the target library.<br>
                       imported-lib<br>
                       \# Specifies the parameter you want to define.<br>
                       PROPERTIES IMPORTED_LOCATION<br>
                       \# Provides the path to the library you want to import.<br>
                       imported-lib/src/${ANDROID_ABI}/libimported-lib.so )<br>
为了确保 CMake 可以在编译时定位您的标头文件，您需要使用 include_directories() 命令，并包含标头文件的路径：<br>
include_directories( imported-lib/include/ )<br>
注：如果您希望打包一个并不是构建时依赖项的预构建库（例如在添加属于 imported-lib 依赖项的预构建库时），则不需要执行以下说明来关联库。<br>
要将预构建库关联到您自己的原生库，请将其添加到 CMake 构建脚本的 target_link_libraries() 命令中：<br>
target_link_libraries( native-lib imported-lib app-glue ${log-lib} )<br>
在您构建应用时，Gradle 会自动将导入的库打包到 APK 中。您可以使用 APK 分析器验证 Gradle 将哪些库打包到您的 APK 中。<br>

### 将 Gradle 关联到您的原生库
要将 Gradle 关联到您的原生库，您需要提供一个指向 CMake 脚本文件的路径。在您构建应用时，Gradle 会以依赖项的形式运行 CMake ，并将共享的库打包到您的 APK 中。Gradle 还使用构建脚本来了解要将哪些文件添加到您的 Android Studio 项目中，以便您可以从 Project 窗口访问这些文件。如果您的原生源文件没有构建脚本，则需要先创建 CMake 构建脚本，然后再继续。<br>
将 Gradle 关联到原生项目后，Android Studio 会更新 Project 窗格以在 cpp 组中显示您的源文件和原生库，在 External Build Files 组中显示您的外部构建脚本。<br>
注：更改 Gradle 配置时，请确保通过点击工具栏中的 Sync Project  应用更改。此外，如果在将 CMake 脚本文件关联到 Gradle 后再对其进行更改，您应当从菜单栏中选择 Build > Refresh Linked C++ Projects，将 Android Studio 与您的更改同步。<br>

#### 手动配置 Gradle
要手动配置 Gradle 以关联到您的原生库，您需要将 externalNativeBuild {} 块添加到模块级 build.gradle 文件中，并使用 cmake {} 对其进行配置：<br>
android {<br>
  ...<br>
  defaultConfig {...}<br>
  buildTypes {...}<br>
  // Encapsulates your external native build configurations.<br>
  externalNativeBuild {<br>
    // Encapsulates your CMake build configurations.<br>
    cmake {<br>
      // Provides a relative path to your CMake build script.<br>
      path "CMakeLists.txt"<br>
    \}<br>
  \}<br>
\}<br>

#### 指定可选配置
您可以在模块级 build.gradle 文件的 defaultConfig {} 块中配置另一个 externalNativeBuild {} 块，为 CMake 指定可选参数和标志。与 defaultConfig {} 块中的其他属性类似，您也可以在构建配置中为每个产品风味重写这些属性。<br>
例如，如果您的 CMake 项目定义多个原生库，您可以使用 targets 属性仅为给定产品风味构建和打包这些库中的一部分。以下代码示例说明了您可以配置的部分属性：<br>
android {<br>
  ...<br>
  defaultConfig {<br>
    ...<br>
    // This block is different from the one you use to link Gradle<br>
    // to your CMake or ndk-build script.<br>
    externalNativeBuild {<br>
      // For ndk-build, instead use ndkBuild {}<br>
      cmake {<br>
        // Passes optional arguments to CMake.<br>
        arguments "-DANDROID_ARM_NEON=TRUE", "-DANDROID_TOOLCHAIN=clang"<br>
        // Sets optional flags for the C compiler.<br>
        cFlags "-D_EXAMPLE_C_FLAG1", "-D_EXAMPLE_C_FLAG2"<br>
        // Sets a flag to enable format macro constants for the C++ compiler.<br>
        cppFlags "-D__STDC_FORMAT_MACROS"<br>
      \}<br>
    \}<br>
  \}<br>
  buildTypes {...}<br>
  productFlavors {<br>
    ...<br>
    demo {<br>
      ...<br>
      externalNativeBuild {<br>
        cmake {<br>
          ...<br>
          // Specifies which native libraries to build and package for this<br>
          // product flavor. If you don't configure this property, Gradle<br>
          // builds and packages all shared object libraries that you define<br>
          // in your CMake or ndk-build project.<br>
          targets "native-lib-demo"<br>
        }<br>
      }<br>
    }<br>
    paid {<br>
      ...<br>
      externalNativeBuild {<br>
        cmake {<br>
          ...<br>
          targets "native-lib-paid"<br>
        }<br>
      }<br>
    }<br>
  }<br>
  // Use this block to link Gradle to your CMake or ndk-build script.<br>
  externalNativeBuild {<br>
    cmake {...}<br>
    // or ndkBuild {...}<br>
  }<br>
}<br>
要详细了解配置产品风味和构建变体，请参阅配置构建变体。如需了解您可以使用 arguments 属性为 CMake 配置的变量列表，请参阅使用 CMake 变量。<br>

#### 指定 ABI
默认情况下，Gradle 会针对 NDK 支持的 ABI 将您的原生库构建到单独的 .so 文件中，并将其全部打包到您的 APK 中。如果您希望 Gradle 仅构建和打包原生库的特定 ABI 配置，您可以在模块级 build.gradle 文件中使用 ndk.abiFilters 标志指定这些配置，如下所示：<br>
android {<br>
  ...<br>
  defaultConfig {<br>
    ...<br>
    externalNativeBuild {<br>
      cmake {...}<br>
      // or ndkBuild {...}<br>
    \}<br>
    ndk {<br>
      // Specifies the ABI configurations of your native<br>
      // libraries Gradle should build and package with your APK.<br>
      abiFilters 'x86', 'x86_64', 'armeabi', 'armeabi-v7a',<br>
                   'arm64-v8a'<br>
    \}<br>
  \}<br>
  buildTypes {...}<br>
  externalNativeBuild {...}<br>
}<br>
在大多数情况下，您只需要在 ndk {} 块中指定 abiFilters（如上所示），因为它会指示 Gradle 构建和打包原生库的这些版本。不过，如果您希望控制 Gradle 应当构建的配置，并独立于您希望其打包到 APK 中的配置，请在 defaultConfig.externalNativeBuild.cmake {} 块（或 defaultConfig.externalNativeBuild.ndkBuild {} 块中）配置另一个 abiFilters 标志。Gradle 会构建这些 ABI 配置，不过仅会打包您在 defaultConfig.ndk{} 块中指定的配置。<br>
为了进一步降低 APK 的大小，请考虑配置 ABI APK 拆分，而不是创建一个包含原生库所有版本的大型 APK，Gradle 会为您想要支持的每个 ABI 创建单独的 APK，并且仅打包每个 ABI 需要的文件。如果您配置 ABI 拆分，但没有像上面的代码示例一样指定 abiFilters 标志，Gradle 会构建原生库的所有受支持 ABI 版本，不过仅会打包您在 ABI 拆分配置中指定的版本。为了避免构建您不想要的原生库版本，请为 abiFilters 标志和 ABI 拆分配置提供相同的 ABI 列表。<br>


