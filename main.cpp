#include <SFML/Graphics.hpp>
#include <string>

#define WIDTH 1000
#define HEIGHT 500

const int CELL_SIZE = 40;
const int MAP_SIZE = (WIDTH * HEIGHT) / CELL_SIZE;
sf::RectangleShape map[MAP_SIZE];
sf::Font font;
sf::Text cellsActive[MAP_SIZE];

sf::Clock _clock;
sf::Time elapsed;

bool isStarted = false;

void Init();
void Draw(sf::RenderWindow* window);
void CheckClicks(sf::RenderWindow* window);
int NeightboursActive(int index);
int NeightboursDisactive(int index);
void CheckCells();
void CheckKeys(sf::Event& event);
void doClock();

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");

    Init();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            CheckKeys(event);
            CheckClicks(&window);
        }

        doClock();

        window.clear(sf::Color::Black);
        Draw(&window);
        window.display();
    }

    return 0;
}
void Init()
{
    if (!font.loadFromFile("font.otf"))
        return;

    for (int i = 0; i < MAP_SIZE; i++)
    {
        cellsActive[i].setFont(font);
        cellsActive[i].setString('0');
        cellsActive[i].setCharacterSize(CELL_SIZE / 2);
        cellsActive[i].setFillColor(sf::Color::Black);

        map[i].setFillColor(sf::Color::White);
        map[i].setOutlineThickness(1);
        map[i].setOutlineColor(sf::Color::Black);

        map[i].setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    }

    int i = 0;
    for (int h = 0; h < HEIGHT; h += CELL_SIZE)
    {
        for (int w = 0; w < WIDTH; w += CELL_SIZE)
        {
            map[i].setPosition(sf::Vector2f(w, h));
            cellsActive[i].setPosition(sf::Vector2f(w, h));
            i++;
        }
    }
}
void Draw(sf::RenderWindow* window)
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        window->draw(map[i]);
        window->draw(cellsActive[i]);
    }
}
void CheckClicks(sf::RenderWindow* window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            if (map[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                map[i].setFillColor(sf::Color::Black);
            }
        }
    }
}
int NeightboursActive(int index)
{
    int neightbours = 0;

    if (map[index + 1].getFillColor() == sf::Color::Black) neightbours++;
    if (map[index - 1].getFillColor() == sf::Color::Black) neightbours++; 
    if (map[index + (WIDTH / CELL_SIZE)].getFillColor() == sf::Color::Black) neightbours++;
    if (map[index - (WIDTH / CELL_SIZE)].getFillColor() == sf::Color::Black) neightbours++;
    if (map[index + (WIDTH / CELL_SIZE) + 1].getFillColor() == sf::Color::Black) neightbours++;
    if (map[index + (WIDTH / CELL_SIZE) - 1].getFillColor() == sf::Color::Black) neightbours++;
    if (map[index - (WIDTH / CELL_SIZE) + 1].getFillColor() == sf::Color::Black) neightbours++;
    if (map[index - (WIDTH / CELL_SIZE) - 1].getFillColor() == sf::Color::Black) neightbours++;

    return neightbours;
}
int NeightboursDisactive(int index)
{
    int neightbours = 0;

    if (map[index + 1].getFillColor() == sf::Color::White) neightbours++;
    if (map[index - 1].getFillColor() == sf::Color::White) neightbours++;
    if (map[index + (WIDTH / CELL_SIZE)].getFillColor() == sf::Color::White) neightbours++;
    if (map[index - (WIDTH / CELL_SIZE)].getFillColor() == sf::Color::White) neightbours++;
    if (map[index + (WIDTH / CELL_SIZE) + 1].getFillColor() == sf::Color::White) neightbours++;
    if (map[index + (WIDTH / CELL_SIZE) - 1].getFillColor() == sf::Color::White) neightbours++;
    if (map[index - (WIDTH / CELL_SIZE) + 1].getFillColor() == sf::Color::White) neightbours++;
    if (map[index - (WIDTH / CELL_SIZE) - 1].getFillColor() == sf::Color::White) neightbours++;

    return neightbours;
}
void CheckCells()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        if (!(NeightboursActive(i) == 2 || NeightboursActive(i) == 3))
            map[i].setFillColor(sf::Color::White);
        if (NeightboursActive(i) == 3)
            map[i].setFillColor(sf::Color::Black);
    }
}
void CheckText()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        cellsActive[i].setString(std::to_string(NeightboursActive(i)));
    }
}
void CheckKeys(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            isStarted = true;
        }
    }
}
void doClock()
{
    if (isStarted)
    {
        elapsed = _clock.getElapsedTime();
        if (elapsed.asSeconds() >= 1.0f)
        {
            CheckText();
            CheckCells();
            _clock.restart();
        }
    }
}