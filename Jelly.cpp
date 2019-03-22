/**
*@file Jelly.cpp
*@brief zawiera definicje metod do obslugi glownej postaci, zadeklarowanych w pliku Jelly.h
*/
#include <SFML/Graphics.hpp>
#include "pch.h"
#include "Jelly.h"
#include "Collision.hpp"

using namespace sf;

/**
*@brief konstruktor Jelly()
*@details ustawianie wartosci poczatkowych atrybutow oraz ladowanie grafiki z pliku png 
*/
Jelly::Jelly(float t_X, float t_Y, float defHeigh)
{
	character.loadFromFile("graphics/jelly.png");
	characterSprite.setTexture(character);
	characterSprite.setPosition(t_X, t_Y);
	character.setSmooth(true);
	defaultHeight = defHeigh;
	height = defHeigh;
	characterSprite.setOrigin(65.5f, 44.5f); //srodek Jelly
	jellySounds();
	beginningPosition.x = t_X;
	beginningPosition.y = t_Y;

}
/**
*@brief metoda jellySounds()
*@details ladowanie z plikow dzwiekow wydawanych przez Jelly
*/
void Jelly::jellySounds()
{
	jumpingS.openFromFile("music/jumpSound.ogg");
	hitS.openFromFile("music/hitSound.ogg");
	//movingS.setLoop(true);
}

/**
*@brief metoda draw
*@details przeciazona aby moc wyswietlac Jelly
*/
void Jelly::draw(RenderTarget& target, RenderStates state) const
{
	target.draw(this->characterSprite, state);
}

/**
*@brief metoda current_position()
*@details zwraca aktualna pozycje Jelly
*/
Vector2f Jelly::current_position()
{
	return characterSprite.getPosition();
}

/**
*@brief metoda change_position()
*@details zmienia pozycje Jelly
*/
void Jelly::change_position(float x, float y)
{
	characterSprite.setPosition(x, y);
}

/**
*@brief metoda gravity()
*@details przyciaga Jelly do wysokosci height(podloze) z odpowiednia prêdkoscia
*/
void Jelly::gravity()
{
	if (characterSprite.getPosition().y < height)
		characterSprite.move(0.f, gravityAcceleration * 5 * time*time);
	else
		characterSprite.setPosition(characterSprite.getPosition().x, height);
}

/**
*@brief metoda movement()
*@details poruszanie Jelly w lewo, w prawo, skok oraz przyspieszenie 
*/
void Jelly::movement()
{
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		if (!onGround)
			speed = 14.f;
		else
			speed = 10.f;//10
	}
	else
		speed = 4.f;  //szybkosc naszej jelly 

	if (Keyboard::isKeyPressed(Keyboard::Right) && canMoveRight)
	{
		if (characterSprite.getScale().x == -1)
			characterSprite.setScale(Vector2f(1, 1));
		characterSprite.move(speed, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Left) && canMoveLeft)
	{
		if (characterSprite.getScale().x == 1)
			characterSprite.setScale(Vector2f(-1, 1));
		characterSprite.move(-(speed), 0.f);
	}

	//---------------------------------------------------------------+ skakanie

	if (characterSprite.getPosition().y >= height) //jesli jest na wysokosci podloza to onGround jest prawda, a jesli nie to nie
	{
		onGround = true;
		canJump = true;
		hitS.stop();
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			jumpClock.restart();
			characterSprite.setScale(Vector2f(characterSprite.getScale().x, 1));
		}
		gravityAcceleration = 50;
	}
	else
		onGround = false;

	time = jumpClock.getElapsedTime().asSeconds();

	if (time < 0.4f && Keyboard::isKeyPressed(Keyboard::Space) && canJump)
	{

		if (time < 0.1f)
		{
			characterSprite.setScale(Vector2f(characterSprite.getScale().x, 0.5f));
			if(jumpingS.getStatus()!= Sound::Status::Playing)
				jumpingS.play();
		}
		else
		{
			characterSprite.setScale(Vector2f(characterSprite.getScale().x, 1));
			if (canJump)
			{
				characterSprite.move(0, -gravityAcceleration);
				gravityAcceleration *= 0.9f;
			}
		}
	}
	else
	{
		gravity();
		jumpingS.stop();
	}

	if (characterSprite.getPosition().x < 300)
	{
		height = defaultHeight;
		canMoveRight = true;
		canMoveLeft = true;
	}
}

