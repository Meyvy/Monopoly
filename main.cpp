#include <iostream>
#include <array>
#include <memory>

class A
{
public:
    virtual ~A(){};
    virtual void mmd() = 0;
};

class B : public A
{
public:
    void mmd()
    {
        std::cout << "b" << std::endl;
    }
    ~B()
    {
        std::cout << "b" << std::endl;
    }
};

class C : public A
{
public:
    void mmd()
    {
        std::cout << "c" << std::endl;
    }
    ~C()
    {
        std::cout << "c" << std::endl;
    }
};

int main()
{
    auto c = C();
    auto a = B();
    std::array<std::unique_ptr<A>, 4> test;
    test[0] = std::make_unique<B>();
    test[1] = std::make_unique<C>();
    test[2] = std::make_unique<B>();
    test[3] = std::make_unique<C>();
}