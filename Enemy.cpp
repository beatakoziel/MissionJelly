/**
*@file Enemy.cpp
*@brief plik zawiera definicje metod dotyczacych poruszania sie wrogow,
*rozmieszczenia przeszkod oraz kolizji z nimi zwiazanych, zadeklarowanych w pliku Enemy.h
*/

#include <SFML/Graphics.hpp>
#include "pch.h"
#include "Enemy.h"

/**
*@brief konstruktor Enemy()
*@details w zaleznoœci od rodzaju wroga lub przeszkody laduje odpowiednia grafike i ustawia wartosci poczatkowe
*/
Enemy::Enemy(float t_X, float t_Y, String whichEnemy)
{

	if (whichEnemy == "crab")
	{
		character.loadFromFile("graphics/crab.png");
		characterSprite.setOrigin(150, 150);
		characterSprite.setScale(sf::Vector2f(1, 1));
	}
	else if (whichEnemy == "seagull")
	{
		character.loadFromFile("graphics/seagull.png");
		characterSprite.setOrigin(100, 58);
		speed = 6.0f;
		characterSprite.setScale(sf::Vector2f(1, 1));
	}
	else if (whichEnemy == "ball")
	{
		character.loadFromFile("graphics/ball.png");
		characterSprite.setOrigin(100, 0);
		character.setSmooth(true);
	}
	else if (whichEnemy == "2xball")
	{
		character.loadFromFile("graphics/doubleBall.png");
		characterSprite.setOrigin(447.f, 440.f);
		characterSprite.setScale(0.2f, 0.2f);
		character.setSmooth(true);
	}
	else if (whichEnemy == "bucket")
	{
		character.loadFromFile("graphics/bucket.png");
		characterSprite.setOrigin(100.f, 0);
		character.setSmooth(true);
	}
	else if (whichEnemy == "beachScreen")
	{
		character.loadFromFile("graphics/parawan.png");
		characterSprite.setOrigin(300.f, 0.f);
		characterSprite.setScale(0.8f, 0.8f);
	}
	else if (whichEnemy == "umbrella")
	{
		character.loadFromFile("graphics/umbrella.png");
		characterSprite.setOrigin(600.f, 0.f);
	}
	characterSprite.setTexture(character);
	characterSprite.setPosition(t_X, t_Y);
	
	beginning_position.x = t_X;
	beginning_position.y = t_Y;
}

/**
*@brief metoda draw
*@details przeciazona aby moc wyswietlac wroga lub przeszkode
*/
void Enemy::draw(RenderTarget &target, RenderStates state) const
{
	target.draw(this->characterSprite, state);
}

/**
*@brief metoda current_position()
*@details zwraca aktualna pozycje wroga lub przeszkody
*/
Vector2f Enemy::current_position() 
{
	return characterSprite.getPosition();
}

/**
*@brief metoda movement()
*@param *jelly
*@details poruszanie wroga w lewo na pewna odleglosc i powrot do punktu poczatkowego
*/
void Enemy::movement(Jelly *jelly)
{
	if (characterSprite.getPosition().x >= beginning_position.x) //odwraca postaæ w lewo jeœli dotknie punktu pocz¹tkowego 
		characterSprite.setScale(Vector2f(-1, 1)); 

	else if (characterSprite.getPosition().x <= (beginning_position.x -move)) //odwraca postaæ w lewo jeœli dotknie punktu pocz¹tkowego -move (domyslnie 800)
		characterSprite.setScale(Vector2f(1, 1));


	if (characterSprite.getScale().x == -1) //sprawdza, w któr¹ stronê obrócony jest postaæ, jeœli -1 to porusza siê w lewo
		characterSprite.move(-(speed), 0);

	else if (characterSprite.getScale().x == 1)  // jeœli 1 to porusza siê w prawo
		characterSprite.move(speed, 0);

	if (Collision::PixelPerfectTest(characterSprite, jelly->characterSprite)) //jesli 'jelly' dotknie kraba 
	{
		jelly->characterSprite.setPosition(jelly->beginningPosition);
		jelly->lifes--;
		jelly->hitS.play();
	}
}

/**
*@brief metoda collisionBucket()
*@param *jelly
*@details obsluga kolizji Jelly z wiaderkiem
*/
void Enemy::collisionBucket(Jelly *jelly)
{
	if ((jelly->characterSprite.getPosition().x > (characterSprite.getPosition().x - 200)) && (jelly->characterSprite.getPosition().x < (characterSprite.getPosition().x + 200)))
	{
		if (Collision::PixelPerfectTest(characterSprite, jelly->characterSprite)&& jelly->characterSprite.getPosition().y > 485)
		{
				if (jelly->characterSprite.getPosition().x < characterSprite.getPosition().x)
					jelly->canMoveRight = false;

				if (jelly->characterSprite.getPosition().x > characterSprite.getPosition().x)
					jelly->canMoveLeft = false;
		}
		else
		{
			jelly->canMoveLeft = true;
			jelly->canMoveRight = true;
		}

		if (jelly->characterSprite.getPosition().x < (characterSprite.getPosition().x + 120) && jelly->characterSprite.getPosition().x >(characterSprite.getPosition().x - 120))
			jelly->height = 485;
		else
			jelly->height = jelly->defaultHeight;
	}
}

/**
*@brief metoda collisionDoubleBall()
*@param *jelly
*@details obsluga kolizji Jelly z podwojna pilka
*/
void Enemy::collisionDoubleBall(Jelly *jelly)
{
	if ((jelly->characterSprite.getPosition().x > (characterSprite.getPosition().x - 200)) && (jelly->characterSprite.getPosition().x < (characterSprite.getPosition().x + 200))) {
		if (jelly->characterSprite.getGlobalBounds().intersects(characterSprite.getGlobalBounds()))
		{
			if (jelly->characterSprite.getPosition().y > 370)
			{
				if (jelly->characterSprite.getPosition().x < characterSprite.getPosition().x)
					jelly->canMoveRight = false;

				if (jelly->characterSprite.getPosition().x > characterSprite.getPosition().x)
					jelly->canMoveLeft = false;

			}
			else
			{

				if (jelly->characterSprite.getPosition().x < characterSprite.getPosition().x && Keyboard::isKeyPressed(Keyboard::Right))
					jelly->characterSprite.setPosition(jelly->characterSprite.getPosition().x + (jelly->speed / 4.f), jelly->characterSprite.getPosition().y - ((jelly->speed * 0.01f)*(characterSprite.getPosition().x - jelly->characterSprite.getPosition().x)));
				if (jelly->characterSprite.getPosition().x > characterSprite.getPosition().x && Keyboard::isKeyPressed(Keyboard::Left))
					jelly->characterSprite.setPosition(jelly->characterSprite.getPosition().x - (jelly->speed / 3.f), jelly->characterSprite.getPosition().y - ((jelly->speed * 0.01f)*(jelly->characterSprite.getPosition().x - characterSprite.getPosition().x)));

				jelly->height = 200 + sqrt((pow((characterSprite.getPosition().x - jelly->characterSprite.getPosition().x), (double)2.0)) + (pow((characterSprite.getPosition().y - jelly->characterSprite.getPosition().y), (double)2.0)));
				jelly->canMoveLeft = true;
				jelly->canMoveRight = true;

			}
		}
		else
		{
			jelly->canMoveLeft = true;
			jelly->canMoveRight = true;
			jelly->height = jelly->defaultHeight;
		}
	}
}
/**
*@brief metoda collisionSingleBall()
*@param *jelly
*@details obsluga kolizji Jelly z pilka
*/
void Enemy::collisionSingleBall(Jelly *jelly)
{
	if ((jelly->characterSprite.getPosition().x > (characterSprite.getPosition().x - 250)) && (jelly->characterSprite.getPosition().x < (characterSprite.getPosition().x + 250)))
	{
		if (Collision::PixelPerfectTest(characterSprite, jelly->characterSprite))
		{
			if (jelly->characterSprite.getPosition().y > 534.f)
			{
				if (jelly->characterSprite.getPosition().x < characterSprite.getPosition().x)
					jelly->canMoveRight = false;

				if (jelly->characterSprite.getPosition().x > characterSprite.getPosition().x)
					jelly->canMoveLeft = false;
			}
			else
			{
				if (jelly->characterSprite.getPosition().x < characterSprite.getPosition().x && Keyboard::isKeyPressed(Keyboard::Right))
					jelly->characterSprite.setPosition(jelly->characterSprite.getPosition().x + (jelly->speed / 4.f), jelly->characterSprite.getPosition().y - ((jelly->speed * 0.01f)*(characterSprite.getPosition().x - jelly->characterSprite.getPosition().x)));
				if (jelly->characterSprite.getPosition().x > characterSprite.getPosition().x && Keyboard::isKeyPressed(Keyboard::Left))
					jelly->characterSprite.setPosition(jelly->characterSprite.getPosition().x - (jelly->speed / 3.f), jelly->characterSprite.getPosition().y - ((jelly->speed * 0.01f)*(jelly->characterSprite.getPosition().x - characterSprite.getPosition().x)));

				jelly->height = jelly->characterSprite.getPosition().y;
			}
		}
		else
		{
			jelly->canMoveLeft = true;
			jelly->canMoveRight = true;
			jelly->height = jelly->defaultHeight;
		}
	}
}

/**
*@brief metoda collisionBeachScreen()
*@param *jelly
*@details obsluga kolizji Jelly z parawanem
*/
void Enemy::collisionBeachScreen(Jelly *jelly)
{
	if ((jelly->characterSprite.getPosition().x > (characterSprite.getPosition().x - 300)) && (jelly->characterSprite.getPosition().x < (characterSprite.getPosition().x + 300)))
	{		
		
		if ((jelly->characterSprite.getPosition().x > (characterSprite.getPosition().x - 280)) && (jelly->characterSprite.getPosition().x < (characterSprite.getPosition().x + 280)) && jelly->characterSprite.getPosition().y < 446)
		{
			jelly->height = 416;
				characterSprite.setColor(Color(255, 255, 255));
		}
		else
		{
			jelly->height = jelly->defaultHeight;
				characterSprite.setColor(Color(255, 255, 255, 128));
		}
	}
	else
		characterSprite.setColor(Color(255, 255, 255));
}
