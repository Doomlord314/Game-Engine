#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED
#include <SFML/Graphics.hpp>

class Object
{
    public:
    int x;
    int y;
    int resx;
    int resy;
    sf::Color c;
    Object(int xl, int yl, sf::Color cl, int resxl, int resyl)
    {
        x = xl;
        y = yl;
        c = cl;
        resx = resxl;
        resy = resyl;
    }
    int move(int xl,int yl)
    {
        x+= xl;
        y+= yl;
    }
    void draw(sf::RenderWindow& window)
    {
        sf::RectangleShape r(sf::Vector2f(resx, resy));
        r.setPosition(x,y);
        r.setFillColor(c);
        window.draw(r);
    }
};

class ObjectManager
{
    public:
    std::vector<Object> Objects;
    void push_back(Object o)
    {
        Objects.push_back(o);
    }
    void Delete(int index)
    {

    }
    bool isTouch(int index1, int index2)
    {
        Object i1 = Objects[index1];
        Object i2 = Objects[index2];
        if( (i2.x >= i1.x && i2.x <= (i1.x + i1.resx)) ||
          ((i2.x + i2.resx) >= i1.x && (i2.x + i2.resx) <= (i1.x + i1.resx)) ){
            if( (i2.y >= i1.y && i2.y <= (i1.y + i1.resy)) ||
                ((i2.y + i2.resy) >= i1.y && (i2.y + i2.resy) <= (i1.y + i1.resy)) ){
                return true;
            }
        }
        return false;
    }
    void draw(sf::RenderWindow& window)
    {
        for(int i = 0; i < Objects.size(); i++)
        {
            Objects[i].draw(window);
        }
    };
};
#endif // OBJECTS_H_INCLUDED
