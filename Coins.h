/**
*@file  Coins.h
*@brief zawiera atrybuty i deklaracje metod do obslugi monet, zdefiniowanych w pliku Coins.cpp
*/
#pragma once
#include <SFML/Graphics.hpp>
#include "Jelly.h"

using namespace sf;

/**
*@brief klasa Coins
*@details zawiera atrybuty i metody dotyczace obslugi monet
*/
class Coins: public Drawable
{
public:
	Coins() = delete;
	Coins(float t_X, float t_Y);
	~Coins() = default;

	/**
	 * @brief sprite monety
	 **/
	Sprite coinSprite;

	void gotIt(Jelly *jelly);
	void changePosition(float t_X, float t_Y);

private:
	/**
	 * @brief textura monety
	 **/
	Texture coin;
	/**
	 * @brief dzwiek podnoszenia monety
	 **/
	Music coinSound;

	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
};

