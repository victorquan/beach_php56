<?php
die("This is a stub file for IDEs, don't use it directly!");

class Animal{
    /**
     * 年龄
     * @var int
     */
    private $age = 0;

    /**
     * 名字
     * @var string
     */
    private $name = "";


    public function __construct(){
    }

    public function __destruct(){
    }

    /**
     * @return string
     */
    public function getAge(){
        return $this->name;
    }

    /**
     * @param $age
     */
    public function setAge($age){
        $this->age = $age;
    }

    /**
     * @return string
     */
    public function getName(){
        return $this->name;
    }

    /**
     * @param $name
     */
    public function setName($name){
        $this->name = $name;
    }


}