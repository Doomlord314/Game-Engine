#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <sstream>
typedef void (*button_cb)();
std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
void default_text(sf::Text& t, int x, int y, sf::Color c)
{
    t.setCharacterSize(30);
    t.setStyle(sf::Text::Bold);
    t.setColor(c);
    t.setPosition(x,y);
}
sf::Font font;
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
class Text
{
    public:
    int x;
    int y;
    int size;
    sf::Color c;
    sf::Text t;
    std::string text_str;
    Text(int xl, int yl, sf::Color cl, int sizel, std::string text_str):
     t(text_str, font)
    {
        x = xl;
        y = yl;
        c = cl;
        size = sizel;
    }
    void change_text(std::string new_text)
    {
        t.setString(new_text);z
    }
    int move(int xl,int yl)
    {
        x+= xl;
        y+= yl;
    }
    void draw(sf::RenderWindow& window)
    {
        default_text(t,x,y,c);
        window.draw(t);
    }
};
class Button
{
    public:
    int x;
    int y;
    int resx;
    int resy;
    bool mstate = false;
    bool lmstate = false;
    sf::Color c;
    button_cb on_click;
    Button(int xl, int yl, sf::Color cl, int resxl, int resyl, button_cb on_clickl)
    {
        x = xl;
        y = yl;
        c = cl;
        resx = resxl;
        resy = resyl;
        on_click = on_clickl;
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
        lmstate = mstate;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            mstate = true;
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            mstate = false;
        window.draw(r);
    }

};
class ObjectManager
{
    public:
    std::vector<Button> Buttons;
    std::vector<Text> Texts;
    private:
    bool isClicked(int index, sf::RenderWindow& window)
    {
        sf::Vector2i xy = sf::Mouse::getPosition(window);
        int ix = xy.x;
        int iy = xy.y;
        Button o = Buttons[index];
        if(ix > o.x && ix < o.x + o.resx)
            if(iy > o.y && iy < o.y + o.resy)
                return true;
        return false;
    }
    public:
    std::vector<Object> Objects;
    void push_back(Object o)
    {
        Objects.push_back(o);
    }
    void push_back(Button o)
    {
        Buttons.push_back(o);
    }
    void push_back(Text o)
    {
        Texts.push_back(o);
    }
    void Delete(int index,int type = 0)
    {
        switch(type)
        {
            case 0:
                Objects.erase (Objects.begin()+index);
            break;
            case 1:
                Buttons.erase (Buttons.begin()+index);
            break;
            case 2:
                Texts.erase (Texts.begin()+index);
            break;
        }
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
        }for(int i = 0; i < Texts.size(); i++)
        {
            Texts[i].draw(window);
        }
        for(int i = 0; i < Buttons.size(); i++)
        {
            Buttons[i].draw(window);
            if(isClicked(i, window) && Buttons[i].mstate && Buttons[i].lmstate == false)
                Buttons[i].on_click();
        }
    };
};
#endif // OBJECTS_H_INCLUDED
