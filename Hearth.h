/**
*@file Hearth.h
*@brief zawiera atrybuty i deklaracje metod do wyswietlania i zmiany pozycji serc(zyc),zdefiniowanych w pliku Hearth.cpp
*/
#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

/**
*@brief klasa Hearth
*@details zawiera atrybuty i metody do wyswietlania i zmiany pozycji serca
*/
class Hearth:public Drawable
{
public:
	Hearth(float t_X, float t_Y);
	Hearth() = delete;
	~Hearth() = default;

	/**
	 * @brief sprite serduszka
	 **/
	Sprite characterSprite;

	void changePosition(float t_X, float t_Y);

private:
	/**
	 * @brief textura serduszka
	 **/
	Texture character;

	void draw(RenderTarget& target, RenderStates state) const override;	 //nadpisywanie 'draw' w celu umozliwienia rysowania w 'Mario.cpp'
};
