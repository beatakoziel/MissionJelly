/**
*@file Enemy.h
*@brief plik zawiera atrybuty i deklaracje metod dotyczacych poruszania sie wrogow,
*rozmieszczenia przeszkod oraz kolizji z nimi zwiazanych, zdefiniowanych w pliku Enemy.cpp
*/

#pragma once
#include "SFML/Graphics.hpp"
#include "Jelly.h"
#include "Collision.hpp"

using namespace sf;

/**
*@brief klasa Enemy
*@details zawiera atrybuty oraz metody dotyczace poruszania siê wrogow, rozmieszczenia przeszkod oraz kolizji z nimi zwiazanych
*/
class Enemy :public Drawable
{
public:
	Enemy(float t_X, float t_Y, String whichEnemy);
	Enemy() = delete;
	~Enemy() = default;

	/**
	 * @brief sprite przeciwnika lub przeszkody 
	 **/
	Sprite characterSprite;
	/**
	 * @brief obecna pozycja przeciwnika lub przeszkody
	 **/
	Vector2f current_position();
	/**
	 * @brief odleglosc jaka ma chodzic przeciwnik, domyslnie 800
	 **/
	float move = 800.0f;

	void movement(Jelly *jelly);
	void collisionBucket(Jelly *jelly);
	void collisionBeachScreen(Jelly *jelly);
	void collisionSingleBall(Jelly *jelly);
	void collisionDoubleBall(Jelly *jelly);

private:
	Texture character; //uzywane do tworzenia zarowno przeciwnikow jak i przeszkod
	/**
	 * @brief pozycja poczatkowa przeciwnika lub przeszkody
	 **/
	Vector2f beginning_position;
	/**
	 * @brief szybkosc poruszania sie przeciwnika, domyslnie 4
	 **/
	float speed = 4.0f;

	void draw(RenderTarget& target, RenderStates state) const override;
};