/**
*@file Sounds.h
*@brief zawiera atrybuty i deklaracje metod dotyczacych obslugi dzwiekow w grze, zdefiniowanych w pliku Sounds.cpp
*/
#pragma once
#include <SFML/Audio.hpp>

enum songs { menuS, changeS, change2S};

/**
*@brief klasa Sounds
*@details zawiera atrybuty i metody dotyczace obslugi dzwiekow w grze
*/
class Sounds : public sf::Music
{
public:
	Sounds(int switchEnum);
	Sounds()=delete;
	~Sounds()=default;

	/**
	 * @brief zapisuje sie tu utwor wczytywany z pliku
	 **/
	Music music;

	void playM();
	void pauseM();
};

