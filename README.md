# Beach

### 一、定位
基于php5.6的一个so扩展，开发一套提供扩展方法、底层拦截器等功能，用于总结个人平时在做一些php技术迁移时，需要检测php运行时的一些因素，如变量属性、函数调用的运行时场景等。
因个人才疏学浅，功能比较简单，望多指教，勿喷。

### 二、使用方法
执行一下命令：
```bash
git clone https://github.com/victorquan/beach.git
cd beach

# root权限执行
phpize
./configure
make
make install
# make test

# 修改php.ini文件，增加以下几行配置
[beach_php56]
extension=beach_php56.so
beach_php56.global_interceptor_enable=On
#beach_php56.global_value=123456
#beach_php56.global_string=testString

killall php-fpm
```


### 三、Animal类的使用
在php代码里面，可以直接使用Animal类：
```php
$labrador = new \Animal();
$labrador->setName("拉拉");
$labrador->setAge(3);
echo "{$labrador->getName()}今年{$labrador->getAge()}周岁了！\n";
```

