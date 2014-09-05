#ifndef APPLE_H_
#define APPLE_H_
#include <iostream>
#include <string>
class Apple
{
public:
    Apple():m_weight(200), m_color("red"), m_clean(false)	
    {
    }
    Apple(double weight, std::string color, bool clean): m_weight(weight),m_color(color), m_clean(clean)
    {
    }
    ~Apple()
    {
    }
    void cleanApple()
    {
      m_clean = true;
      std::cout <<"The  apple is clean now !"<<std::endl;
    }
    double eatApple(double bitten)
    {	
      m_weight -= bitten;
      return m_weight;
    }
    static double anyCFunc (double x)
    {
      x += 1;
      std::cout << x <<	std::endl;
      return x;
    }
    double getWeight() const
    {
      return m_weight;
    }

    std::string getColor() const
    {
        return m_color;
    }
    double cal(double num)
    {
      return num + 0.000001;
    }
private:
    double m_weight;
    std::string m_color;
    bool m_clean;
};
#endif