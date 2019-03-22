/**
*@file Sounds.cpp
*@brief zawiera definicje metod dotyczacych obslugi dzwiekow w grze, zadeklarowanych w pliku Sounds.h
*/
#include "pch.h"
#include "Sounds.h"

using namespace sf;

/**
*@brief konstruktor Sounds
*@param switchEnum
*@details ladowanie pliku dzwiekowego w zaleznosci od przekazanego parametru
*/
Sounds::Sounds(int switchEnum)
{
	switch (switchEnum)
	{
		case menuS:	 //0
		{
			music.openFromFile("music/menuMusic.ogg");
			music.setLoop(true);
			break;
		}
		case changeS:	 //1
		{
			music.openFromFile("music/changeSound.ogg");
			break;
		}
		case change2S:	 //2 
		{
			music.openFromFile("music/changeSound2.ogg");
			break;
		}
	}
}

/**
*@brief metoda playM()
*@details odtwarzanie dzwieku
*/
void Sounds::playM()
{
	music.play();
}

/**
*@brief metoda pauseM()
*@details zatrzymanie dzwieku
*/
void Sounds::pauseM()
{
	music.pause();
}
