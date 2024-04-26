// Q1：为什么要避免在基类的构造函数中调用虚函数？

#include <iostream>

class Animal {
public:
    Animal() {
        std::cout << "Animal constructor called" << std::endl;
        speak();
    }

    virtual ~Animal() {}

    virtual void speak() {
        std::cout << "Some animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    Dog() {
        std::cout << "Dog constructor called" << std::endl;
    }

    virtual void speak() override {
        std::cout << "Bark!" << std::endl;
    }
};

int main() {
    Dog rex;
    return 0;
}

/*
Animal constructor called
Some animal sound
Dog constructor called
*/
