/**
*@file Coins.cpp
*@brief zawiera definicje metod do obslugi monet, zadeklarowanych w pliku Coins.h
*/
#include "pch.h"
#include "Coins.h"
#include "Collision.hpp"

using namespace sf;

/**
*@brief konstruktor Coins()
*@details ladowanie grafiki z pliku png, ustawianie wartosci poczatkowych
*/
Coins::Coins(float t_X, float t_Y)
{
	coin.loadFromFile("graphics/coin.png");
	coin.setSmooth(true);
	coinSprite.setTexture(coin);
	coinSprite.setPosition(t_X, t_Y);
	coinSound.openFromFile("music/coinSound.ogg");
}

/**
*@brief metoda draw()
*@details przeciazona aby moc narysowac monete
*/
void Coins::draw(RenderTarget &target, RenderStates state) const
{
	target.draw(this->coinSprite, state);
}

/**
*@brief metoda gotIt()
*@details obsluga zebrania monety, zwiekszenie wyniku Jelly
*/
void Coins::gotIt(Jelly *jelly)
{
	if (Collision::PixelPerfectTest((*jelly).characterSprite, coinSprite))
	{
		++(*jelly).coins;
		coinSprite.setPosition(-1000.f, -1000.f);
		coinSound.play();
	}
}

/**
*@brief metoda changePosition()
*@details zmiana pozycji monety
*/
void Coins::changePosition(float t_X, float t_Y)
{
	coinSprite.setPosition(t_X, t_Y);
}
