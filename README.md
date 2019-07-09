# littleBitch

### 一、定位
基于php5.6的一个so扩展，开发一套底层拦截器，用于需要检测php运行时的一些因素，如变量属性、函数调用的运行时场景等，纯个人使用的工具。

### 二、使用方法
执行一下命令：
```bash
git clone https://github.com/victorquan/littleBitch.git
cd littleBitch

# root权限执行
phpize
./configure
make
make install
# make test

# 修改php.ini文件，增加以下几行配置
[bitch_php56]
extension=bitch_php56.so
bitch_php56.global_value=123456
bitch_php56.global_string=testString

killall php-fpm
```



