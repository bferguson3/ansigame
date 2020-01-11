#include <iostream>
#include <SFML/Window/Keyboard.hpp> //easy inclusive interface to X11

int main()
{
    while(1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            std::cout << "OK";
        }
    }
    return 0;
}
