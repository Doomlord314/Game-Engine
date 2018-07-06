#include <SFML/Graphics.hpp>
#include "Objects.h"
#include <stdlib.h>
#include <time.h>
int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!");
    ObjectManager O;
    window.setFramerateLimit(60);
    O.push_back(Object(250,20,sf::Color::Red, 100, 20));
    O.push_back(Object(250,480,sf::Color::Red, 100, 20));
    O.push_back(Object(250,250,sf::Color::Green, 20, 20));
    int bsX = 3;
    int bsY = 5;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Player Movement
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            O.Objects[0].move(-10,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            O.Objects[0].move(10,0);
        }
        //Ball Movement
        O.Objects[2].move(bsX,bsY);
        if(O.Objects[2].y < 0 || O.Objects[2].y > 500)
        {
            bsY *= -1;
        }
        if(O.Objects[2].x < 0 || O.Objects[2].x > 500)
        {
            bsX *= -1;
        }
        if(O.isTouch(0,2))
        {
            //bsX *= -1;
            bsY *= -1;
            bsX += (rand()%3) - 2;
           // bsY += 1;
            O.Objects[2].y += 10;
        }
        if(O.isTouch(1,2))
        {
            //bsY += 1;
            bsX += (rand()%3) - 2;
            bsY *= -1;
            O.Objects[2].y -= 10;
        }
        //AI movement
        if(O.Objects[1].x < O.Objects[2].x)
        {
            O.Objects[1].x += 4;
        }
        if(O.Objects[1].x > O.Objects[2].x)
        {
            O.Objects[1].x -= 4;
        }
        window.clear(sf::Color(255,255,255));
        O.draw(window);
        window.display();
    }

    return 0;
}
