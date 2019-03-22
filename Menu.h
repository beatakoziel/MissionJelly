/**
*@file Menu.h
*@brief plik zawiera atrybuty i deklaracje metod dotyczacych poruszania sie po menu, zdefiniowanych w pliku Menu.cpp
*/
#include "SFML/Graphics.hpp"

using namespace sf;

/**
*@brief klasa Menu
*@details zawiera atrybuty oraz metody dotyczace poruszania sie po menu
*/
class Menu
{
public:
	Menu(float width, float height);
	~Menu()=default;

	/**
	 * @brief jesli 1 to pojawia sie menu, jesli -1 to pojawia sie reszta, jesli 0 to pojawia sie introduction
	 **/
	int menuVisible = 1;
	/**
	 * @brief ktora opcja z menu zostala wybrana
	 **/
	int selected;

	void draw(RenderWindow &window);
	void Up();
	void Down();

private:
	/**
	 * @brief czcionka
	 **/
	Font font;
	/**
	 * @brief tablica, do ktorej zapisuje sie 3 napisy z menu
	 **/
	Text text[3];
};