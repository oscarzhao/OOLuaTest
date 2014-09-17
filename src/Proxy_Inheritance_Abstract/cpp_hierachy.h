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
    virtual const std::string& getClassName() const = 0;
    virtual void funcVoidNoParam() = 0;
    virtual void funcVoidThreeIntParams(int, int, int) = 0;

    //void doSomething()
    //{
    //    std::cout << "[AbstractBase: " << __FUNCTION__ << "] I do not know nothing" << std::endl;
    //}

    //void doSomethingConst() const
    //{
    //    std::cout << "[AbstractBase: " << __FUNCTION__ << "] I'm a const member functions" << std::endl;
    //}
};

class RetDerived: public AbstractBase
{
public:
    static std::string name;
public:
    RetDerived();
    virtual AbstractBasePtr copy() const;

    virtual void funcVoidNoParam();
    virtual void funcVoidThreeIntParams(int a, int b, int c);

    virtual const std::string& getClassName() const;
};

class Derived: public AbstractBase
{
public:
    static std::string name;
public:
    Derived():m_bool(true), m_int(0), m_double(0.0), m_string(""){}
    virtual AbstractBasePtr copy() const;

    virtual const std::string& getClassName() const;

    virtual void funcVoidNoParam();

    virtual void funcVoidThreeIntParams(int a, int b, int c);

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

    RetDerivedPtr getRetDerived();

private:
    RetDerivedPtr m_ptrRetDerived;
};

#endif