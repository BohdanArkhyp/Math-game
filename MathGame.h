#pragma once

#ifndef _MATH_GAME_
#define _MATH_GAME_

#include <SFML/Graphics.hpp>

class Example
{
	int num1, num2;
	char sign;
	int answer;

	sf::Font font;
	sf::Text example;
public:
	void Init();
	void Generate();
	int GetAnswer();
	void Draw(sf::RenderWindow& window);
	void SetColor(sf::Color color);
};

class Number
{
	sf::Text number;
	sf::Font font;
public:
	void Init();
	sf::Text& Get();
};

bool isNumPressed(sf::Event& event);
int whichNumPressed(sf::Event& event);
void checkKeys(sf::Event& event, sf::Text& number, Example& example);

#endif