#ifndef APPLE_H_
#define APPLE_H_
#include <iostream>
#include <string>
class Apple
{
public:
    Apple():
      m_weight(200),
          m_color("red"),
          m_clean(false)	
      {
      }
      ~Apple(void)
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
      double getWeight()
      {
          std::cout << "Weight: " << m_weight << std::endl;
          return m_weight;
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