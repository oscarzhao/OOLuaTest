#ifndef FRUIT_APPLE_H_
#define FRUIT_APPLE_H_

#include <iostream>
#include <string>
#include "oolua_dsl.h"

class Fruit
{
public:
    Fruit():m_weight(0.2),
        m_unit_price(10)
    {
        std::cout << "Fruit constructed successfully" << std::endl;
    }

    virtual ~Fruit()
    {
        std::cout << "Fruit destructed" << std::endl;
    }
    double getWeight()
    {
        std::cout << "[Fruit: " << __FUNCTION__ << "] m_weight: " << m_weight <<  " kg" << std::endl;
        return m_weight;
    }

    double getUnitPrice()
    {
        return m_unit_price;
    }

    double getPrice()
    {
        return m_weight * m_unit_price;
    }

    double eat(double bitten)
    {
        m_weight -= bitten;
        return m_weight;
    }
private:
    double m_weight;
    double m_unit_price;
};

class Apple: public Fruit
{	
public:
    Apple():Fruit(), m_color("red"), m_clean(false)	
    {
        std::cout << "Apple constructed successfully!" <<std::endl;
    }

    virtual ~Apple()
    {
        std::cout << "Apple destructed." <<std::endl;
    }

    void cleanApple()
    {
        m_clean = true;
        std::cout <<"The apple is clean now !"<<std::endl;
    }

    static double anyCFunc (double x)
    {
        x += 1;
        std::cout << x <<	std::endl;
        return x;
    }


private:
    std::string m_color;
    bool m_clean;
};

#endif