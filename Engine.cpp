/**
*@file Engine.cpp 
*@brief zawiera funkcje „main”. W nim rozpoczyna sie i konczy wykonywanie programu.
*/

#include "pch.h"

#include "Jelly.h"
#include "Menu.h"
#include "Enemy.h"
#include "Sounds.h"
#include "Coins.h"
#include "Hearth.h"

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <windows.h>
#include <sstream>

using namespace std;
using namespace sf;

typedef basic_ostringstream<char> ostringstream;

static inline std::string toString(int x)
{
	ostringstream type;
	type << x;
	return type.str();
}

int main()
{
	Jelly jelly(0.f, 0.f, 650.f); //tworzy galaretke na pozycji (0 ,0), ale przy uruchomieniu gry galaretka  ustawiana jest na odpowiedniej pozycji; trzeci parametr to standardowa wysokosc mapy 
	Jelly *jellyPointer = &jelly;

	//----------------------Tworzenie przeszkód
	Enemy ball1(3120.0f, 524.f, "ball"), ball2(8500.0f, 524.f, "ball");
	Enemy doubleBall1(6300.f, 438.0f, "2xball"), doubleBall2(7000.f, 438.0f, "2xball"),
		doubleBall3(4000.0f, 438.0f,"2xball"), doubleBall4(10200.0f, 438.0f, "2xball"),
		doubleBall5(11050.0f, 438.0f, "2xball");
	Enemy bucket1(500.f, 410.f, "bucket"), bucket2(1700.f, 410.f, "bucket"),
		bucket3(4900.f, 410.f, "bucket"), bucket4(7800.f, 410.f, "bucket");
	Enemy beachScreen1(5600.0f, 340.0f, "beachScreen"), beachScreen2(9800.0f, 340.0f, "beachScreen");
	Enemy umbrella1(9500.0f, 350.0f, "umbrella");


	//----------------------Tworzenie wrogów
	Enemy crab1(1500.f, 590.f, "crab"); 
	Enemy crab2(6790.f, 590.f, "crab");
	Enemy crab3(8600.f, 590.f, "crab");
	Enemy crab4(10580.f, 590.f, "crab");
	Enemy crab5(10850.f, 590.f, "crab");
	Enemy seagull1(7050.f, 280.f, "seagull");
	Enemy seagull2(2800.f, 310.f, "seagull");
	Enemy seagull3(5800.f, 310.f, "seagull");
	Enemy seagull4(10000.f, 310.f, "seagull");
	Enemy seagull5(12100.f, 580.f, "seagull");
	crab2.move=270.0f;
	crab3.move = 550.0f;
	seagull3.move = 1000.0f;
	seagull4.move = 1000.0f;
	seagull5.move = 900.0f;
	crab4.move = 180.0f;
	crab5.move = 180.0f;

	//------------------------Tworzenie monet
	Coins maincoin(50.0f,60.0f);
	Coins coin1(1000.f, 50.f), coin2(2400.0f, 70.f),
		coin3(2400.0f, 150.0f), coin4(3400.0f, 150.0f),
		coin5(3500.0f, 150.0f), coin6(3600.0f, 150.0f),
		coin7(3700.0f, 150.0f), coin8(3800.0f, 150.0f),
		coin9(4400.0f, 150.0f), coin10(4830.0f, 300.0f),
		coin11(4830.0f, 250.0f), coin12(4830.0f, 200.0f),
		coin13(4830.0f, 150.0f), coin14(5400.0f, -70.0f),
		coin15(5480.0f, -70.0f), coin16(5560.0f, -70.0f),
		coin17(5640.0f, -70.0f), coin18(6400.0f, 510.0f),
		coin19(6400.0f, 430.0f), coin20(6400.0f, 350.0f),
		coin21(7750.0f, 300.0f), coin22(7750.0f, 250.0f),
		coin23(7750.0f, 200.0f), coin24(7750.0f, 150.0f),
		coin25(8920.0f, 370.0f), coin26(9000.0f, 370.0f),
		coin27(8450.0f, 100.0f), coin28(9600.0f, -70.0f),
		coin29(9680.0f, -70.0f), coin30(9760.0f, -70.0f),
		coin31(9840.0f, -70.0f), coin32(5540.f, 550.f),
		coin33(5400.f, 550.f), coin34(5680.f, 550.f),
		coin35(5540.f, 460.f), coin36(5400.f, 460.f), 
		coin37(5680.f, 460.f), coin38(9600.f, 550.f),
		coin39(9880.f, 550.f), coin40(9740.f, 550.f),
		coin41(9600.f, 460.f), coin42(9740.f, 460.f),
		coin43(9880.f, 460.f), coin44(6300.f, 550.f),
		coin45(7000.f, 550.f), coin46(4000.0f, 550.f),
		coin47(10200.0f, 550.f), coin48(11050.0f, 550.f);

	Menu menu(1280, 720); //tworzenie obiektu Menu

	//----------------------Tworzenie serduszek, które się wyświetlają jako życia
	Hearth hearth1(60, 60);
	Hearth hearth2(180, 60);
	Hearth hearth3(300, 60);

	HWND okno = GetConsoleWindow();		// ukrywanie okna konsoli
	ShowWindow(okno, SW_HIDE);			 

	Vector2i screenDimensions(1280, 720); // wykorzystywany do tworzenia okna i do podazania tla za bohaterem
	unsigned int screenX = screenDimensions.x / 2; //optymalizacja -
	unsigned int screenY = screenDimensions.y / 2; //- pozniejsze dzielenie jest klopotliwe


	RenderWindow window{ VideoMode(screenDimensions.x,screenDimensions.y), "Mission Jelly" };
	window.setFramerateLimit(60);

	Texture background_texture;
	background_texture.loadFromFile("graphics/background.jpg");
	Sprite backgroundSprite;
	backgroundSprite.setTexture(background_texture);

	backgroundSprite.setScale(1.0f, (float)screenDimensions.y / background_texture.getSize().y);

	Texture background_menu;
	background_menu.loadFromFile("graphics/menu_background.jpg");
	Sprite menuSprite;
	menuSprite.setTexture(background_menu);

	menuSprite.setScale(1.0f, (float)screenDimensions.y / background_menu.getSize().y);

	Texture background_gameover;
	background_gameover.loadFromFile("graphics/gameover.jpg");
	Sprite gameoverSprite;
	gameoverSprite.setTexture(background_gameover);

	gameoverSprite.setScale(1.0f, (float)screenDimensions.y / background_gameover.getSize().y);

	Texture background_intro;
	background_intro.loadFromFile("graphics/introduction.jpg");
	Sprite introSprite;
	introSprite.setTexture(background_intro);

	introSprite.setScale(1.0f, (float)screenDimensions.y / background_intro.getSize().y);

	Texture background_winner;
	background_winner.loadFromFile("graphics/winner.jpg");
	Sprite winnerSprite;
	winnerSprite.setTexture(background_winner);

	winnerSprite.setScale(1.0f, (float)screenDimensions.y / background_winner.getSize().y);

	//----------------------------------------------------------------------------------
	View view; //tworzenie widoku, w celu podazania tla za postacia
	view.reset(FloatRect(0.0f, 0.0f, (float)screenDimensions.x, (float)screenDimensions.y));
	view.setViewport(FloatRect(0, 0, 1.0f, 1.0f));

	Vector2f position((float)screenX, (float)screenY);

	//----------------------Dzwieki

	Sounds musicMenu(0);
	musicMenu.playM();

	Sounds changeSound(1);
	Sounds changeSound2(2);

	Music winnerSound, looserSound;
	winnerSound.openFromFile("music/youWin.ogg");
	looserSound.openFromFile("music/youLose.ogg");

	//----------------------Czcionka i zmienna do wyswietlania wyniku na ekranie

	Font font;

	if (!font.loadFromFile("Alex.ttf"))
		std::cout << "Blad";

	Text howManyCoins;
	howManyCoins.setPosition(60,180);
	howManyCoins.setCharacterSize(70);
	howManyCoins.setFillColor(Color(157, 124, 100));
	howManyCoins.setFont(font);

	//----------------------------------------------------------------------------------

	while(window.isOpen()	)
	{
		menu.draw(window); 
		Event event;
		if (menu.menuVisible==1) {
			while (window.pollEvent(event))
			{
				switch (event.type) {
				case Event::KeyReleased:
					switch (event.key.code)
					{
					case Keyboard::Up:
					{
						changeSound.playM(); 
						menu.Up();
						break;
					}
					case Keyboard::Down:
					{
						changeSound.playM();
						menu.Down();
						break;
					}
					case Keyboard::Enter:
					{
						if (menu.selected == 0)
						{
							musicMenu.pauseM();
							changeSound2.playM(); //cichy dzwiek potwierdzajacy wybor
							jelly.change_position(60.0f, 60.0f);
							menu.menuVisible = -1;
						}
						if (menu.selected == 1)
						{
							changeSound2.playM();
							menu.menuVisible = 0;
						}
						if (menu.selected == 2)
							window.close();
					}
					}
					break;

				case Event::Closed:
				{
					window.close();

				}
				break;
				}
			}
		}
		
		while(window.pollEvent(event))
		{ 
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyReleased && event.key.code == Keyboard::Space)  // Zabezpieczenie przeciwko podwojnym skokom jelly
				jelly.canJump = false;													
		}
		//------------------------------------------------------ chodzenie i zabezpieczenie przed wychodzeniem z mapy
		crab1.movement(jellyPointer);
		crab2.movement(jellyPointer);
		crab3.movement(jellyPointer);
		seagull1.movement(jellyPointer);
		seagull2.movement(jellyPointer);
		seagull3.movement(jellyPointer);
		seagull4.movement(jellyPointer);
		crab4.movement(jellyPointer);
		crab5.movement(jellyPointer);
		seagull5.movement(jellyPointer);


		coin1.gotIt(jellyPointer);
		coin2.gotIt(jellyPointer);
		coin3.gotIt(jellyPointer);
		coin4.gotIt(jellyPointer);
		coin5.gotIt(jellyPointer);
		coin6.gotIt(jellyPointer);
		coin7.gotIt(jellyPointer);
		coin8.gotIt(jellyPointer);
		coin9.gotIt(jellyPointer);
		coin10.gotIt(jellyPointer);
		coin11.gotIt(jellyPointer);
		coin12.gotIt(jellyPointer);
		coin13.gotIt(jellyPointer);
		coin14.gotIt(jellyPointer);
		coin15.gotIt(jellyPointer);
		coin16.gotIt(jellyPointer);
		coin17.gotIt(jellyPointer);
		coin18.gotIt(jellyPointer);
		coin19.gotIt(jellyPointer);
		coin20.gotIt(jellyPointer);
		coin21.gotIt(jellyPointer);
		coin22.gotIt(jellyPointer);
		coin23.gotIt(jellyPointer);
		coin24.gotIt(jellyPointer);
		coin25.gotIt(jellyPointer);
		coin26.gotIt(jellyPointer);
		coin27.gotIt(jellyPointer);
		coin28.gotIt(jellyPointer);
		coin29.gotIt(jellyPointer);
		coin30.gotIt(jellyPointer);
		coin31.gotIt(jellyPointer);
		coin32.gotIt(jellyPointer);
		coin33.gotIt(jellyPointer);
		coin34.gotIt(jellyPointer);
		coin35.gotIt(jellyPointer);
		coin36.gotIt(jellyPointer);
		coin37.gotIt(jellyPointer);
		coin38.gotIt(jellyPointer);
		coin39.gotIt(jellyPointer);
		coin40.gotIt(jellyPointer);
		coin41.gotIt(jellyPointer);
		coin42.gotIt(jellyPointer);
		coin43.gotIt(jellyPointer);
		coin44.gotIt(jellyPointer);
		coin45.gotIt(jellyPointer);
		coin46.gotIt(jellyPointer);
		coin47.gotIt(jellyPointer);
		coin48.gotIt(jellyPointer);
		

		howManyCoins.setString(to_string(jelly.coins));

		bucket1.collisionBucket(jellyPointer);
		bucket2.collisionBucket(jellyPointer);
		bucket3.collisionBucket(jellyPointer);
		bucket4.collisionBucket(jellyPointer);

		ball1.collisionSingleBall(jellyPointer);
		doubleBall1.collisionDoubleBall(jellyPointer);
		doubleBall2.collisionDoubleBall(jellyPointer);
		doubleBall3.collisionDoubleBall(jellyPointer);
		doubleBall4.collisionDoubleBall(jellyPointer);
		doubleBall5.collisionDoubleBall(jellyPointer);

		beachScreen1.collisionBeachScreen(jellyPointer);
		beachScreen2.collisionBeachScreen(jellyPointer);
		jelly.movement();


		if (jelly.current_position().x <= 5) // jezeli jest 5 pikseli od konca
			jelly.change_position(6.0f, jelly.current_position().y); // to wraca go na pozycje 10.0 (x)
		if (jelly.current_position().x >= backgroundSprite.getTextureRect().width-750) // jezeli jest ([szerokosc mapy]width-) 750 pikseli od prawego brzegu mapy
			jelly.change_position((float)backgroundSprite.getTextureRect().width-751, jelly.current_position().y); // to wraca go na pozycje ([szerokosc mapy]width-) 751 przed koncem mapy - koniec poziomu
		//------------------------------------------------------ chodzenie i zabezpieczenie przed wychodzeniem z mapy

		//------------------------------------------------------ // podążanie kamery
		if (jelly.jellyIsAlive)
		{
			position.x = jelly.current_position().x + 250 - screenX;
			position.y = jelly.current_position().y - 350 - screenY;
			if (position.x < 0)
				position.x = 0;
			if (position.x > backgroundSprite.getTextureRect().width - 1290.0f) //nie pokazuje się czarne tło przy dochodzeniu do chorągiewki
				position.x = backgroundSprite.getTextureRect().width - 1290.0f;
			if (position.y < 0)
				position.y = 0;

			view.reset(FloatRect(position.x, position.y, (float)screenDimensions.x, (float)screenDimensions.y));

			hearth1.changePosition(position.x + 60, 60);
			hearth2.changePosition(position.x + 135, 60);
			hearth3.changePosition(position.x + 205, 60);
			howManyCoins.setPosition(position.x +80, 60);
			maincoin.changePosition(position.x-20, 50);

			position.x = (float)screenX;

			window.setView(view);
		}
		//---------------------------------------------WYGRANA
		if (jelly.current_position().x >= backgroundSprite.getTextureRect().width - 960)
		{
			menu.menuVisible = 2;
		}
		//------------------------------------------------------ 
		
		window.clear(); //czyszczenie okna
		if (menu.menuVisible==1) //wyświetlanie tła i menu
		{
			window.draw(menuSprite);
			menu.draw(window);
		}
		else if (menu.menuVisible == -1)
		{
			if (jelly.lifes > 0)
			{
				window.draw(backgroundSprite); //wyświetlanie tła

				window.draw(coin32); //wyswietlanie ukrytych monet (muszą byc rysowane przed rysowaniem parawanu)
				window.draw(coin33); 
				window.draw(coin34); 
				window.draw(coin35); 
				window.draw(coin36); 
				window.draw(coin37); 
				window.draw(coin38); 
				window.draw(coin39);
				window.draw(coin40);
				window.draw(coin41);
				window.draw(coin42);
				window.draw(coin43);


				window.draw(jelly); //wyświetlanie galaretki


				window.draw(beachScreen1); //wyswietlanie parawanów
				window.draw(beachScreen2); 


				window.draw(doubleBall1); //wyświetlanie podwojnych pilek
				window.draw(doubleBall2); 
				window.draw(doubleBall3);
				window.draw(doubleBall4);
				window.draw(doubleBall5);
				window.draw(bucket1); //wyświetlanie wiaderek
				window.draw(bucket2); 
				window.draw(bucket3); 
				window.draw(bucket4); 
				window.draw(ball1);


				window.draw(howManyCoins); //wyświetlanie liczby zebranych monet
				window.draw(maincoin); //wyświetlanie monety przy wyniku
				window.draw(coin1); //wyświetlanie monet
				window.draw(coin2);
				window.draw(coin3);
				window.draw(coin4);
				window.draw(coin5);
				window.draw(coin6);
				window.draw(coin7);
				window.draw(coin8);
				window.draw(coin9);
				window.draw(coin10);
				window.draw(coin11);
				window.draw(coin12);
				window.draw(coin13);
				window.draw(coin14);
				window.draw(coin15);
				window.draw(coin16);
				window.draw(coin17);
				window.draw(coin18);
				window.draw(coin19);
				window.draw(coin20);
				window.draw(coin21);
				window.draw(coin22);
				window.draw(coin23);
				window.draw(coin24);
				window.draw(coin25);
				window.draw(coin26);
				window.draw(coin27);
				window.draw(coin28);
				window.draw(coin29);
				window.draw(coin30);
				window.draw(coin31);

				window.draw(umbrella1);

				window.draw(crab1); //wyświetlanie krabów
				window.draw(crab2);
				window.draw(crab3);
				window.draw(crab4);
				window.draw(crab5);
				window.draw(seagull1); //wyswietlanie mew
				window.draw(seagull2);
				window.draw(seagull3);
				window.draw(seagull4);
				window.draw(seagull5);

				if (jelly.lifes == 1)
					window.draw(hearth1);
				else if (jelly.lifes == 2)
				{
					window.draw(hearth1);
					window.draw(hearth2);
				}
				else if (jelly.lifes == 3)
				{
					window.draw(hearth1);
					window.draw(hearth2);
					window.draw(hearth3);
				}
			}
			else
			{
				jelly.jellyIsAlive = false;
				if (looserSound.getStatus() != Sound::Status::Playing)
					looserSound.play();
				window.draw(gameoverSprite);
				view.reset(FloatRect(0, 0, (float)screenDimensions.x, (float)screenDimensions.y));
				window.setView(view);
				Sleep(200);
				if (Keyboard::isKeyPressed(Keyboard::Enter))
					window.close();
			}
		}
		else if (menu.menuVisible == 0) {
			window.draw(introSprite);
			if (Keyboard::isKeyPressed(Keyboard::BackSpace))
				menu.menuVisible = 1;
		}
		else
		{
			jelly.jellyIsAlive = false;
			if (winnerSound.getStatus() != Sound::Status::Playing)
				winnerSound.play();
			window.draw(winnerSprite);
			howManyCoins.setPosition(1164, 608);
			window.draw(howManyCoins);
			view.reset(FloatRect(0, 0, (float)screenDimensions.x, (float)screenDimensions.y));
			window.setView(view);
			if (Keyboard::isKeyPressed(Keyboard::Enter))
				window.close();
		}
		window.display();
		
	}
 }
