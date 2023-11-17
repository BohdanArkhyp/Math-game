#include "MathGame.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Math Game");

    Example example;
    example.Init();
    example.Generate();
    
    Number number;
    number.Init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            checkKeys(event, number.Get(), example);
        }

        window.clear(sf::Color::White);
        example.Draw(window);
        window.draw(number.Get());
        window.display();
    }

    return 0;
}