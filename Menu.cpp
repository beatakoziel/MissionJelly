/**
*@file Menu.cpp
*@brief zawiera definicje metod do obslugi menu, zadeklarowanych w pliku Menu.h
*/
#include "pch.h"
#include "Menu.h"
#include <iostream>

/**
*@brief konstruktor Menu()
*@details dodawanie czcionki, ustawianie koloru napisow, pozycji w oknie, wartosci napisu wybranego 
*/
Menu::Menu(float width, float height) 
{
	if (!font.loadFromFile("Alex.ttf"))
		std::cout << "Blad";

	text[0].setFont(font);
	//text[0].setFillColor(Color(141,133,133)); szary
	text[0].setFillColor(Color(157, 124, 100)); //brazowy
	text[0].setString("Play");
	text[0].setPosition(Vector2f(width / 2.6, height / 4));
	text[0].setCharacterSize(100);

	text[1].setFont(font);
	text[1].setFillColor(Color::White);
	text[1].setString("Introduction");
	text[1].setPosition(Vector2f(width / 2.6, height / 2.7));
	text[1].setCharacterSize(100);

	text[2].setFont(font);
	text[2].setFillColor(Color::White);
	text[2].setString("Exit");
	text[2].setPosition(Vector2f(width / 2.6, height / 2));
	text[2].setCharacterSize(100);
	
	selected = 0;
}

/**
*@brief metoda draw()
*@details przeciazona aby moc wyswietlac opcje menu
*/
void Menu::draw(RenderWindow &window) 
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(text[i]); //wypisujemy na ekran napisy
	}
}

/**
*@brief metoda Up()
*@details obsluga przejscia w gore
*/
void Menu::Up()
{
	if (selected - 1 >= 0)
	{
		text[selected].setFillColor(Color::White); //ustawiamy wybrany napis jako aktywny
		selected--;
		text[selected].setFillColor(Color(157, 124, 100)); //ustawiamy poprzedni napis jako "nieaktywny"
	}
}

/**
*@brief metoda Down()
*@details obsluga przejscia w do³
*/
void Menu::Down()
{
	if (selected + 1 < 3)
	{
		text[selected].setFillColor(Color::White); //poprzedni napis jako "nieaktywny"
		selected++;
		text[selected].setFillColor(Color(157, 124, 100)); //ustawiamy wybrany napis jako aktywny
	}
}
