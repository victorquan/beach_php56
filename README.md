# littleBitch

### 一、定位
基于php5.6的一个so扩展，开发一套提供扩展方法、底层拦截器等功能，用于总结个人平时在做一些php技术迁移时，需要检测php运行时的一些因素，如变量属性、函数调用的运行时场景等。
因个人才疏学浅，功能比较简单，望多指教，勿喷。

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



