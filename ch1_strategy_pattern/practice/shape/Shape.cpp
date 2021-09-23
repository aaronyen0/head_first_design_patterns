/* Filename   : Shape.cpp
 * Author     : Xen http://scriptjerks.blogspot.com/
 * Compiler   : gcc 4.7.0/VC++ 2010
 * OS         : Windows 7 64-bit
 * Date       : 2012/06/30
 * Update     : 2013/06/20
 * Description:
 *      An interface(pure virtual function) example. To calculate shapes' area
 * and perimeter. And to evaluate all of the total area summation(you don't 
 * need to know what kind of shapes).
 */

#include <cstdio>
#include <iostream>
#include <vector>
using std::vector;
using std::cout;
using std::endl;

const double PI = 3.1415926;

class IShape
{
public:
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Circle : public IShape
{
public:
    Circle()
        : m_radius(1)
    {
    }
    
    Circle(double radius)
        : m_radius(radius > 0 ? radius : 1)
    {
    }
    
    void SetRadius(double radius)
    {
        if(radius > 0)
            m_radius = radius;
    }
    
    double GetRadius()
    {
        return m_radius;
    }
    
    double Perimeter()
    {
        double p = PI * m_radius;
        return p + p;
    }
    
    double Area()
    {
        return m_radius * m_radius * PI;
    }

private:
    double m_radius;
};

class Rectangle : public IShape
{
public:
    Rectangle()
        : m_length(1), m_width(1)
    {
    }
    
    Rectangle(double length, double width)
        : m_length(length > 0 ? length : 1),
          m_width(width > 0 ? width : 1)
    {
    }
    
    void SetLength(double length)
    {
        if(length > 0)
            m_length = length;
    }
    
    double GetLength()
    {
        return m_length;
    }
    
    void SetWidth(double width)
    {
        if(width > 0)
            m_width = width;
    }
    
    double GetWidth()
    {
        return m_width;
    }
    
    double Perimeter()
    {
        return m_length + m_length + m_width + m_width;
    }
    
    double Area()
    {
        return m_length * m_width;
    }

private:
    double m_length;
    double m_width;
};

double AreaSummation(vector<IShape*> shapes)
{
    double result = 0;

    for(vector<IShape*>::size_type i = 0; i != shapes.size(); ++i)
    {
        result += shapes[i]->Area();
    }

    return result;
}

int main()
{
    vector<IShape*> shapes;
    Circle aCircle[3];
    Rectangle aRect[3];

    aCircle[0] = Circle(0.75);
    aCircle[1] = Circle();
    aCircle[2] = Circle(3.47);
    aRect[0] = Rectangle();
    aRect[1] = Rectangle(3, 4);
    aRect[2] = Rectangle(2.5, 6.25);

    for(int i = 0; i != 3; ++i)
    {
        shapes.push_back(&aCircle[i]);
        cout << "Circle " << i + 1 << ": " << endl
         << "Radius = " << aCircle[i].GetRadius() << endl
         << "Perimeter = " << aCircle[i].Perimeter() << endl
         << "Area = " << aCircle[i].Area() << endl << endl;
    }

    for(int i = 0; i != 3; ++i)
    {
        shapes.push_back(&aRect[i]);
        cout << "Rectangle " << i + 1 << ": " << endl
         << "Length = " << aRect[i].GetLength() << ", Width = " << aRect[i].GetWidth() << endl
         << "Perimeter = " << aRect[i].Perimeter() << endl
         << "Area = " << aRect[i].Area() << endl << endl;
    }

    cout << "Area Summation = " << AreaSummation(shapes) << endl;

    getchar();
}