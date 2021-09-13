# flutter 2.4.3.X 集成文档

<a name="AiyJS"></a>
## 概述


本文是闪验SDK_flutter **v2.4.3.X**版本的接入文档，用于指导SDK的使用方法。<br />

<a name="65lmE"></a>
# 创建应用

<br />应用的创建流程及APPID的获取，请查看「[账号创建](http://flash.253.com/document/details?lid=292&cid=91&pc=28&pn=%25E9%2597%25AA%25E9%25AA%258CSDK)」文档<br />**注意：如果应用有多个包名或签名不同的马甲包，须创建多个对应包名和签名的应用，否则马甲包将报包名或签名校验不通过。**<br />

<a name="h4mXI"></a>
### 安装
在工程 pubspec.yaml 中加入 dependencies

- github 集成
```dart
dependencies:
  shanyan:
    git:
      url: git://github.com/253CL/CLShanYan_Flutter.git
      path: cl_shanyan_baiban
      ref: v2.4.3.3
```
<a name="UlDef"></a>
### 使用


```dart
import 'package:cl_shanyan_baiban/shanyan.dart';
```


<a name="JRH4x"></a>
### 开发环境搭建

<br />权限配置（AndroidManifest.xml文件里面添加权限）<br />
<br />必要权限：<br />

```xml
<uses-permission android:name="android.permission.INTERNET"/>
<uses-permission android:name="android.permission.WRITE_SETTINGS"/>
<uses-permission android:name="android.permission.ACCESS_WIFI_STATE"/>
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE"/>
<uses-permission android:name="android.permission.CHANGE_NETWORK_STATE"/>
<uses-permission android:name="android.permission.CHANGE_WIFI_STATE"/>
<uses-permission android:name="android.permission.GET_TASKS"/>
```

<br />建议的权限：如果选用该权限，需要在预取号步骤前提前动态申请。
```xml
<uses-permission android:name="android.permission.READ_PHONE_STATE"/>
```
**建议开发者申请本权限，本权限只用于移动运营商在双卡情况下，更精准的获取数据流量卡的运营商类型，**<br />**缺少该权限，存在取号失败概率上升的风险。**<br />
<br />配置权限说明

| **权限名称** | 权限说明 | 使用说明 |
| --- | --- | --- |
| INTERNET | 允许应用程序联网 | 用于访问网关和认证服务器 |
| ACCESS_WIFI_STATE | 允许访问WiFi网络状态信息 | 允许程序访问WiFi网络状态信息 |
| ACCESS_NETWORK_STATE | 允许访问网络状态 | 区分移动网络或WiFi网络 |
| CHANGE_NETWORK_STATE | 允许改变网络连接状态 | 设备在WiFi跟数据双开时，强行切换使用数据网络 |
| CHANGE_WIFI_STATE | 允许改变WiFi网络连接状态 | 设备在WiFi跟数据双开时，强行切换使用 |
| READ_PHONE_STATE | 允许读取手机状态 | （可选）获取IMSI用于判断双卡和换卡 |
| WRITE_SETTINGS | 允许读写系统设置项 | 电信SDK在6.0系统以下进行数据切换用到的权限，添加后可增加电信在WiFi+4G下网络环境下的取号成功率。6.0系统以上可去除 |
| GET_TASKS | 允许应用程序访问TASK |  |



在application标签内配置授权登录activity，screenOrientation和theme可以根据项目需求自行修改<br />

```xml
<activity
    android:name="com.chuanglan.shanyan_sdk.view.CmccLoginActivity"
    android:configChanges="keyboardHidden|orientation|screenSize"
    android:launchMode="singleTop"
    android:screenOrientation="behind"
     />

<activity-alias
   android:name="com.cmic.sso.sdk.activity.LoginAuthActivity"
   android:configChanges="keyboardHidden|orientation|screenSize"
   android:launchMode="singleTop"
   android:screenOrientation="behind"
   android:targetActivity="com.chuanglan.shanyan_sdk.view.CmccLoginActivity"
    /> 
<activity
   android:name="com.chuanglan.shanyan_sdk.view.ShanYanOneKeyActivity"
   android:configChanges="keyboardHidden|orientation|screenSize"
   android:launchMode="singleTop"
   android:screenOrientation="behind"
    />
<activity
   android:name="com.chuanglan.shanyan_sdk.view.CTCCPrivacyProtocolActivity"
   android:configChanges="keyboardHidden|orientation|screenSize"
   android:launchMode="singleTop"
   android:screenOrientation="behind"
    /> 
```

<br />配置Android9.0对http协议的支持两种方式：<br />
<br />方式一：<br />

```xml
android:usesCleartextTraffic="true"
```

<br />示例代码：<br />

```xml
<application
    android:name=".view.MyApplication"
    ***
    android:usesCleartextTraffic="true"
    ></application>
```

<br />方式二：<br />
<br />目前只有移动运营商个别接口为http请求，对于全局禁用Http的项目，需要设置Http白名单。以下为运营商http接口域名：cmpassport.com;*.10010.com <br />
<br />(3) 混淆规则：<br />

```java
-dontwarn com.cmic.sso.sdk.**
-dontwarn com.unikuwei.mianmi.account.shield.**
-dontwarn com.sdk.**
-keep class com.cmic.sso.sdk.**{*;}
-keep class com.sdk.** { *;}
-keep class com.unikuwei.mianmi.account.shield.** {*;}
-keep class cn.com.chinatelecom.account.api.**{*;}
```

<br />(4) AndResGuard资源压缩过滤：<br />

```java
"R.anim.umcsdk*",
"R.drawable.umcsdk*",
"R.layout.layout_shanyan*",
"R.id.shanyan_view*",
```

<br />通过上面的几个步骤，工程就配置完成了，接下来就可以在工程中使用闪验SDK进行开发了。
<a name="mglDi"></a>
## 一、免密登录API使用说明
<a name="ANoDq"></a>
### 1.初始化

<br />使用一键登录功能前，必须先进行初始化操作。<br />
<br />调用示例<br />

```dart
ClShanyan.init(appId: "******").then((shanYanResult) {
      setState(() {
           _method = "初始化";
           _code = shanYanResult.code ?? 0;
           _msg = shanYanResult.message ?? "";
           _content = shanYanResult.toJson().toString();
     });
    print(shanYanResult.toJson().toString());
});
```

<br />参数描述

| 参数 | 类型 | 说明 |
| --- | --- | --- |
| appId | String | 闪验平台获取到的appId |


<br />返回为ShanYanResult对象属性如下：

| **字段** | **类型** | **含义** |
| --- | --- | --- |
| code | Int | code为1000:成功；其他：失败 |
| message | String | 描述 |
| innerCode | Int | 内层返回码 |
| innerDesc | String  | 内层事件描述  |
| token | String  | token |



<a name="8Cuhp"></a>
### 2.预取号


- **建议在判断当前用户属于未登录状态时使用，****已登录状态用户请不要调用该方法**
- 建议在执行拉取授权登录页的方法前，提前一段时间调用预取号方法，中间最好有2-3秒的缓冲（因为预取号方法需要1~3s的时间取得临时凭证）
- **请勿频繁的多次调用、请勿与拉起授权登录页同时和之后调用。**
- **避免大量资源下载时调用，例如游戏中加载资源或者更新补丁的时候要顺序执行**




调用示例：<br />

```dart
  ClShanyan.getPrePhoneInfo().then((shanYanResult) {
        setState(() {
        _method = "预取号";
        _code = shanYanResult.code ?? 0;
        _msg = shanYanResult.message ?? "";
        _content = shanYanResult.toJson().toString();
    });
    print(shanYanResult.toJson().toString());
 });
```
返回为ShanYanResult对象属性如下：

| **字段** | **类型** | **含义** |
| --- | --- | --- |
| code | Int | code为1000:成功；其他：失败 |
| message | String | 描述 |
| innerCode | Int | 内层返回码 |
| innerDesc | String  | 内层事件描述  |
| token | String  | token |

<a name="jdF5H"></a>
### 3.获取token

- 调用获取token应同步拉起运营商授权页面。
- **授权页具体规则参考 [官方文档](https://sdk.253.com/document) 上闪验相关部分**
- **授权页须包含一键登录按钮、运营商协议名称（可查看协议链接详情）、脱敏手机号**

<br />调用示例：<br />

```dart
ClShanyan.openLoginAuth().then((shanYanResult) {
    setState(() {
        _method = "获取token";
        _code = shanYanResult.code ?? 0;
        _msg = shanYanResult.message ?? "";
        _content = shanYanResult.toJson().toString();
    });
    print(shanYanResult.toJson().toString());
});
```

<br />返回为ShanYanResult对象属性如下：

| **字段** | **类型** | **含义** |
| --- | --- | --- |
| code | Int | code为1000:成功；其他：失败 |
| message | String | 描述 |
| innerCode | Int | 内层返回码 |
| innerDesc | String  | 内层事件描述  |
| token | String  | token（成功情况下返回）用来后台置换手机号。token一次有效。 |


**
<a name="EOGka"></a>
### 4.置换手机号
当一键登录外层code为1000时，您将获取到返回的参数，请将这些参数传递给后端开发人员，并参考「[服务端](https://flash.253.com/document/details?lid=300&cid=93&pc=28&pn=%25E9%2597%25AA%25E9%25AA%258CSDK)」文档来实现获取手机号码的步骤。<br />


<br />**注意：如果添加布局为自定义控件，监听实现请参考demo示例。**<br />**
<a name="D9qrI"></a>
## 二、本机认证API使用说明

<br />**注：本机认证同免密登录，需要初始化，本机认证、免密登录可共用初始化，两个功能同时使用时，只需调用一次初始化即可。**<br />**
<a name="C1ZCW"></a>
### 1.初始化

<br />**同免密登录初始化**<br />**
<a name="Lqzq4"></a>
### 2.本机号校验

<br />在初始化执行之后调用，本机号校验界面需自行实现，可以在多个需要校验的页面中调用。<br />
<br />调用示例：<br />

```dart
//闪验SDK 本机号校验获取token (Android+iOS)
ClShanyan.localAuthentication().then((shanYanResult) {
    setState(() {
        _method = "本机号校验获取token";
        _code = shanYanResult.code ?? 0;
        _msg = shanYanResult.message ?? "";
        _content = shanYanResult.toJson().toString();
    });
    print(shanYanResult.toJson().toString());
});
```

<br />返回为ShanYanResult对象属性如下：

| **字段** | **类型** | **含义** |
| --- | --- | --- |
| code | Int | code为1000:成功；其他：失败 |
| message | String | 描述 |
| innerCode | Int | 内层返回码 |
| innerDesc | String  | 内层事件描述  |
| token | String  | token（成功情况下返回）用来和后台校验手机号。一次有效。 |

<a name="ApxrD"></a>
### 3.校验手机号

<br />当本机号校验外层code为2000时，您将获取到返回的参数，请将这些参数传递给后端开发人员，并参考「[服务端](http://flash.253.com/document/details?lid=300&cid=93&pc=28&pn=%25E9%2597%25AA%25E9%25AA%258CSDK)」文档来实现校验本机号的步骤
<a name="dCHBW"></a>
## 三、返回码
该返回码为闪验SDK自身的返回码，请注意1003及1023错误内均含有运营商返回码，具体错误在碰到之后查阅「[返回码](http://flash.253.com/document/details?lid=301&cid=93&pc=28&pn=%25E9%2597%25AA%25E9%25AA%258CSDK)」<br />

