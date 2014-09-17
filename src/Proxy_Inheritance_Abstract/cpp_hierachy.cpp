#include "cpp_hierachy.h"

std::string RetDerived::name;

RetDerived::RetDerived()
{ 
    std::cout << "RetDerived constructed" << std::endl; 
}

AbstractBasePtr RetDerived::copy() const
{
    RetDerivedPtr ret(new RetDerived(*this));
    return ret;
}

void RetDerived::funcVoidNoParam()
{
    std::cout << "RetDerived: This is virtual function \"" << __FUNCTION__ << "\", with none params\n";
}

void RetDerived::funcVoidThreeIntParams(int a, int b, int c)
{
    std::cout << "RetDerived: This is virtual function \"" << __FUNCTION__ << "\", with three int params: " << a << ", " << b << ", " << c << std::endl;
}

const std::string& RetDerived::getClassName() const
{
    return RetDerived::name;
}


std::string Derived::name;

AbstractBasePtr Derived::copy() const
{
    boost::shared_ptr< Derived > ret(new Derived(*this));
    return ret;
}

const std::string& Derived::getClassName() const
{
    return Derived::name;
}

void Derived::funcVoidNoParam()
{
    std::cout << "Derived: This is virtual function \"" << __FUNCTION__ << "\", with none params\n";
}

void Derived::funcVoidThreeIntParams(int a, int b, int c)
{
    std::cout << "Derived: This is virtual function \"" << __FUNCTION__ << "\", with three int params: " << a << ", " << b << ", " << c << std::endl;
}

RetDerivedPtr MyClass::getRetDerived()
{
    return m_ptrRetDerived;
}