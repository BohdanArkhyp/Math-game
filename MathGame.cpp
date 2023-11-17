#include "MathGame.h"

void Example::Init()
{
	font.loadFromFile("font.otf");
	
	example.setFont(font);
	example.setFillColor(sf::Color::Black);
	example.setCharacterSize(50);
	example.setPosition(sf::Vector2f(350, 250));
}
void Example::Generate()
{
	srand(unsigned int(time(nullptr)));

	num1 = 1 + rand() % 5;
	num2 = 1 + rand() % 5;
	int _sign = rand() % 4;

	switch (_sign)
	{
	case 0:
		sign = '+';
		answer = num1 + num2;
		break;
	case 1:
		sign = '-';

		if (num1 < num2)
			std::swap(num1, num2);

		answer = num1 - num2;
		break;
	case 2:
		sign = '*';
		answer = num1 * num2;
		break;
	case 3:
		int _answer = num1;
		num1 = num1 * num2;
		sign = '/';
		answer = _answer;
		break;
	}

	example.setFillColor(sf::Color::Black);
	example.setString(std::to_string(num1) + ' ' + sign + ' ' + std::to_string(num2));
}
int Example::GetAnswer()
{
	return answer;
}
void Example::Draw(sf::RenderWindow& window)
{
	window.draw(example);
}
void Example::SetColor(sf::Color color)
{
	example.setFillColor(color);
}

void Number::Init()
{
	font.loadFromFile("font.otf");

	number.setFont(font);
	number.setFillColor(sf::Color::Black);
	number.setPosition(sf::Vector2f(350, 500));
	number.setCharacterSize(50);
}
sf::Text& Number::Get()
{
	return number;
}

bool isNumPressed(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) return true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) return true;

	return false;
}
int whichNumPressed(sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) return 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) return 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) return 2;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) return 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) return 4;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) return 5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) return 6;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) return 7;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) return 8;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) return 9;

	return -11;
}
void checkKeys(sf::Event& event, sf::Text& number, Example& example)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (isNumPressed(event))
			number.setString(number.getString() + std::to_string(whichNumPressed(event)));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (std::to_string(example.GetAnswer()) == number.getString())
				example.Generate();
			else
				example.SetColor(sf::Color::Red);

			number.setString("");
		}
	}
}