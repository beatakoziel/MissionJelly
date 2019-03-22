/**
*@file Jelly.h
*@brief zawiera atrybuty i deklaracje metod sluzacych do obslugi Jelly, zdefiniowanych w pliku Jelly.cpp
*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

/**
*@brief klasa Jelly
*@details zawiera atrybuty oraz metody dotycz¹ce obslugi(poruszania sie) Jelly
*/
class Jelly : public Drawable
{
public:
	Jelly(float t_X, float t_Y, float defHeigh);
	Jelly() = delete;
	~Jelly() = default;

	/**
	 * @brief true - jelly zyje, false - nie zyje
	 **/
	bool jellyIsAlive = true;
	/**
	 * @brief czy jelly jest na wysokosci height 
	 **/
	bool onGround = true;
	/**
	 * @brief czy jelly moze aktualnie podskoczyc
	 **/
	bool canJump = true;
	/**
	 * @brief czy jelly moze isc w lewo
	 **/
	bool canMoveLeft = true;
	/**
	 * @brief czy jelly moze isc w prawo
	 **/
	bool canMoveRight = true;
	/**
	 * @brief "przyspieszenie grwaitacji" - wykorzystywane w metodzie gravity() w Jelly.cpp, ustala z jaka predkoscia jelly ma byc przyciagna
	 **/
	float gravityAcceleration = 50;
	/**
	 * @brief odpowiada na jakiej wysokosci moze obecnie stac jelly
	 **/
	float height;
	/**
	 * @brief standardowa wysokosc, czyli wysokosc podloza mapy, przypisuje sie jej liczbe przekazana w konstruktorze (na mapie z plaza jest to 650)
	 **/
	float defaultHeight;
	/**
	 * @brief zmienna odpowiadajaca za szybkosc jelly- przypisywana w metodzie movement() w Jelly.cpp
	 **/
	float speed;
	/**
	 * @brief zycia jelly, standardowo 3; jesli bedzie ich miala 0 to konczy sie gra
	 **/
	int lifes=3;
	/**
	 * @brief ilosc monet jelly
	 **/
	int coins = 0;
	/**
	 * @brief sprite jelly
	 **/
	Sprite characterSprite;
	/**
	 * @brief pozycja startowa jelly
	 **/
	Vector2f beginningPosition;
	/**
	* @brief zmienna wykorzystywana przy skakaniu, miedzy innymi do splaszczania jelly przed skokiem
	**/
	float time;
	/**
	 * @brief zmienna wykorzystywana przy skakaniu, miedzy innymi do splaszczania jelly przed skokiem
	 **/
	Clock jumpClock;
	/**
	 * @brief wczytuje sie tu dzwiek skoku jelly
	 **/
	Music jumpingS;
	/**
	 * @brief wczytuje sie tu dzwiek uderzenia jelly przez przeciwnika
	 **/
	Music hitS;

	void change_position(float x, float y);
	void gravity();
	void movement();
	Vector2f current_position();

private:
	/**
	 * @brief tekstura jelly
	 **/
	Texture character;

	void draw(RenderTarget& target, RenderStates state) const override;	 
	void jellySounds();
};