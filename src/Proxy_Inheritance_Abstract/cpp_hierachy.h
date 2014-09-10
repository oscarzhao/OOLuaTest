#ifndef CPP_HIERACHY_H_
#define CPP_HIERACHY_H_

/**
 *	抽象类作为基类
 *  boost::shared_ptr 作为 返回值
 */
#include <iostream>
#include <string>
#include "oolua_dsl.h"

class AbstractBase;
class RetDerived;
typedef boost::shared_ptr< AbstractBase > AbstractBasePtr;
typedef boost::shared_ptr< RetDerived > RetDerivedPtr;

class AbstractBase
{
public:
    virtual ~AbstractBase(){ std::cout << "AbstractBase destructed" << std::endl; };
    virtual boost::shared_ptr< AbstractBase > copy() const = 0;
    virtual void funcVoidNoParam() = 0;
    virtual void funcVoidThreeIntParams(int, int, int) = 0;

    void doSomething()
    {
        std::cout << "[AbstractBase: " << __FUNCTION__ << "] I do not know nothing" << std::endl;
    }

    void doSomethingConst() const
    {
        std::cout << "[AbstractBase: " << __FUNCTION__ << "] I'm a const member functions" << std::endl;
    }
};

class RetDerived: public AbstractBase
{
public:
    RetDerived(){ std::cout << "RetDerived constructed" << std::endl; };
    virtual AbstractBasePtr copy() const
    {
        RetDerivedPtr ret(new RetDerived(*this));
        return ret;
    }

    virtual void funcVoidNoParam()
    {
        std::cout << "RetDerived: This is virtual function \"" << __FUNCTION__ << "\", with none params\n";
    }

    virtual void funcVoidThreeIntParams(int a, int b, int c)
    {
        std::cout << "RetDerived: This is virtual function \"" << __FUNCTION__ << "\", with three int params: " << a << ", " << b << ", " << c << std::endl;
    }
};

class Derived: public AbstractBase
{
public:
    Derived():m_bool(true), m_int(0), m_double(0.0), m_string(""){}
    virtual AbstractBasePtr copy() const
    {
        boost::shared_ptr< Derived > ret(new Derived(*this));
        return ret;
    }

    virtual void funcVoidNoParam()
    {
        std::cout << "Derived: This is virtual function \"" << __FUNCTION__ << "\", with none params\n";
    }

    virtual void funcVoidThreeIntParams(int a, int b, int c)
    {
        std::cout << "Derived: This is virtual function \"" << __FUNCTION__ << "\", with three int params: " << a << ", " << b << ", " << c << std::endl;
    }

private:
    bool m_bool;
    int m_int;
    double m_double;
    std::string m_string;
    
};

class MyClass
{
public:
    MyClass(): m_ptrRetDerived(new RetDerived){};
    virtual ~MyClass(){};

    RetDerivedPtr getRetDerived()
    {
        return m_ptrRetDerived;
    }

private:
    RetDerivedPtr m_ptrRetDerived;
};

#endif