/**
*@file Hearth.cpp
*@brief zawiera definicje metod do wyswietlania i zmiany pozycji serc(zyc), zadeklarowanych w pliku Hearth.h
*/
#include <SFML/Graphics.hpp>
#include "pch.h"
#include "Hearth.h"

/**
*@brief konstruktor Hearth()
*@details ladowanie grafiki z pliku .png oraz ustawianie wartosci poczatkowych 
*/
Hearth::Hearth(float t_X, float t_Y)
{
	character.loadFromFile("graphics/hearth.png");
	characterSprite.setTexture(character);
	characterSprite.setPosition(t_X, t_Y);
	characterSprite.setOrigin(60.0f, 60.05f); //srodek coin
}

/**
*@brief metoda draw()
*@details przeciazona metoda, aby moc wyswietlic serce(zycie)
*/
void Hearth::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->characterSprite, state);
}

/**
*@brief metoda changePosition()
*@details zmiana pozycji serca
*/
void Hearth::changePosition(float t_X, float t_Y)
{
	characterSprite.setPosition(t_X, t_Y);
}