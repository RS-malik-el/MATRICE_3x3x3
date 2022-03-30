/*
	DATE    : 31/03/2022
	AUTHEUR : RACHEL SYSTEME
	GITHUB  : https://github.com/RS-malik-el
	YOUTUBE : https://www.youtube.com/channel/UCf4jGfp-BFp6GLd6eTptVMg?sub_confirmation=1

	Ce fichier, coder pour arduino, contient les fonctions ou méthodes vous permettant
	de contrôler l'allumage de vos leds dans une matrice cubique à leds de taille 3x3x3 
*/

#include "Matrix_3x3x3.h"

#define DELAY_LIMIT() 	if (_delay > 1000)\
	 						_delay = 1000;\
						if (_delay < 100  )\
	 						_delay = 100;


Matrix_3x3x3 :: Matrix_3x3x3(){}
Matrix_3x3x3 :: ~Matrix_3x3x3(){}


// Initialisation de la série aléatoire des nombres
void Matrix_3x3x3 :: Init_Random(){
	randomSeed(analogRead(A0));
}


// Définition des pins comme sortie
void Matrix_3x3x3 :: AttachPinRow(uint8_t Pin_1, uint8_t Pin_2, uint8_t Pin_3){
	_Pin_Ligne[0] = Pin_1;
	_Pin_Ligne[1] = Pin_2;
	_Pin_Ligne[2] = Pin_3;

	for (int y = 0; y < 3; ++y)
	{
		pinMode(_Pin_Ligne[y],OUTPUT);
		digitalWrite(_Pin_Ligne[y],HIGH);
	}
}


// Etat initial des colonnes
void Matrix_3x3x3 :: _DefaultColumnState(){
	for (int z = 0; z < 3; ++z)
	{
		for (int x = 0; x < 3; ++x)
		{
			digitalWrite(_Pin_Colonne[z][x],LOW);
		}
	}
}


void Matrix_3x3x3 :: AttachPinColumn(	uint8_t Pin_1, uint8_t Pin_2, uint8_t Pin_3,
										uint8_t Pin_4, uint8_t Pin_5, uint8_t Pin_6,
										uint8_t Pin_7, uint8_t Pin_8, uint8_t Pin_9
										){
	_Pin_Colonne[0][0] = Pin_1;
	_Pin_Colonne[0][1] = Pin_2;
	_Pin_Colonne[0][2] = Pin_3;
	_Pin_Colonne[1][0] = Pin_4;
	_Pin_Colonne[1][1] = Pin_5;
	_Pin_Colonne[1][2] = Pin_6;
	_Pin_Colonne[2][0] = Pin_7;
	_Pin_Colonne[2][1] = Pin_8;
	_Pin_Colonne[2][2] = Pin_9;

	for (int z = 0; z < 3; ++z)
	{
		for (int x = 0; x < 3; ++x)
		{
			pinMode(_Pin_Colonne[z][x],OUTPUT);
		}
	}
	_DefaultColumnState();	
}


void Matrix_3x3x3 :: Play_OneByOne(uint8_t _delay=100){
	DELAY_LIMIT()

	for (int y = 0; y < 3; ++y)
	{
		digitalWrite(_Pin_Ligne[y],LOW);
		for (int z = 0; z < 3; ++z)
		{
			for (int x = 0; x < 3; ++x)
			{
				digitalWrite(_Pin_Colonne[z][x],HIGH);
				delay(_delay);
				digitalWrite(_Pin_Colonne[z][x],LOW);
				delay(_delay);
			}
		}
		digitalWrite(_Pin_Ligne[y],HIGH);
	}
}



void Matrix_3x3x3 :: Play_ThreeByThree(uint8_t _delay=100){
	DELAY_LIMIT()

	for (int y = 0; y < 3; ++y)
	{
		digitalWrite(_Pin_Ligne[y],LOW);
		for (int z = 0; z < 3; ++z)
		{
			for (int x = 0; x < 3; ++x)
			{
				digitalWrite(_Pin_Colonne[z][x],HIGH);
			}

			delay(_delay);

			for (int x = 0; x < 3; ++x)
			{
				digitalWrite(_Pin_Colonne[z][x],LOW);
			}
			
			delay(_delay);	
		}
		digitalWrite(_Pin_Ligne[y],HIGH);
	}
}


void Matrix_3x3x3 :: Play_PlanByPlan(uint8_t _delay=100){
	DELAY_LIMIT()

	for (int z = 0; z < 3; ++z)
	{
		for (int x = 0; x < 3; ++x)
		{
			digitalWrite(_Pin_Colonne[z][x],HIGH);
		}
	}

	for (int y = 0; y < 3; ++y)
	{
		digitalWrite(_Pin_Ligne[y],LOW);
		delay(_delay);
		digitalWrite(_Pin_Ligne[y],HIGH);
		delay(_delay);
	}
	_DefaultColumnState();
	
}

/*
	allumage aléatoire des leds:
	si nb = 1 : on allume led par led 
	si nb = 2 : on allume 2 par 2
	si nb = 3 : on allume 3 par 3
	si nb = 4 : on allume plan par plan
*/
void Matrix_3x3x3 :: Play_Randomly(uint8_t nb = 1, uint8_t _delay=100){
	_nb = nb;
	
	if (_nb < 1 || _nb > 4)
		_nb = 1;

	DELAY_LIMIT()
	
	_Draw();
	_Random_OneByOne(_delay);
	_Random_TwoByTwo(_delay);
	_Random_ThreeByThree(_delay);
	_Random_PlanByPlan(_delay);
}


//	.................PRIVATE....................
// Tirage aléatoire de la position de la led ou des leds à allumer
void Matrix_3x3x3 :: _Draw(){
	if (_nb == 1){
		_Rand_x0 = random(3);
		_Rand_y0 = random(3);
		_Rand_z0 = random(3);
	}

	if (_nb == 2){
		_Rand_x0 = random(3);
		_Rand_x1 = random(3);
		_Rand_z0 = random(3);
		_Rand_z1 = random(3);
		
		do{
			_Rand_y0 = random(3);
			_Rand_y1 = random(3);

			if (_Rand_z0 != _Rand_z1)
				break;
		}while(_Rand_y0 == _Rand_y1);
	}

	if (_nb == 3){
		_Rand_y0 = random(3);
		_Rand_z0 = random(3);
	}

	if (_nb == 4)
		_Rand_y0 = random(3);
}


void Matrix_3x3x3 :: _Random_OneByOne(uint8_t _delay=100){
	if (_nb == 1)
		{
			digitalWrite(_Pin_Ligne[_Rand_y0],LOW);
			digitalWrite(_Pin_Colonne[_Rand_z0][_Rand_x0],HIGH);
			delay(_delay);
			digitalWrite(_Pin_Ligne[_Rand_y0],HIGH);
			digitalWrite(_Pin_Colonne[_Rand_z0][_Rand_x0],LOW);
			delay(_delay);
		}
}


void Matrix_3x3x3 :: _Random_TwoByTwo(uint8_t _delay=100){
	if (_nb == 2)
	{	unsigned long depart = millis();
		while(millis()-depart <= _delay*2){
			digitalWrite(_Pin_Ligne[_Rand_y0],LOW);
			digitalWrite(_Pin_Colonne[_Rand_z0][_Rand_x0],HIGH);
			delayMicroseconds(10);
			digitalWrite(_Pin_Colonne[_Rand_z0][_Rand_x0],LOW);
			digitalWrite(_Pin_Ligne[_Rand_y0],HIGH);
			delayMicroseconds(10);

			digitalWrite(_Pin_Ligne[_Rand_y1],LOW);
			digitalWrite(_Pin_Colonne[_Rand_z1][_Rand_x1],HIGH);
			delayMicroseconds(10);
			digitalWrite(_Pin_Colonne[_Rand_z1][_Rand_x1],LOW);
			digitalWrite(_Pin_Ligne[_Rand_y1],HIGH);
			delayMicroseconds(10);
		}	
	}
}


void Matrix_3x3x3 :: _Random_ThreeByThree(uint8_t _delay=100){
		if (_nb == 3)
		{	
			for (int x = 0; x < 3; ++x)
			{
				digitalWrite(_Pin_Colonne[_Rand_z0][x],HIGH);
			}
		
			digitalWrite(_Pin_Ligne[_Rand_y0],LOW);
			delay(_delay);
			digitalWrite(_Pin_Ligne[_Rand_y0],HIGH);
			_DefaultColumnState();
			delay(_delay);
	}
}


void Matrix_3x3x3 :: _Random_PlanByPlan(uint8_t _delay=100){
	if (_nb == 4)
	{
		for (int z = 0; z < 3; ++z)
		{
			for (int x = 0; x < 3; ++x)
			{
				digitalWrite(_Pin_Colonne[z][x],HIGH);
			}
		}
		digitalWrite(_Pin_Ligne[_Rand_y0],LOW);
		delay(_delay);
		digitalWrite(_Pin_Ligne[_Rand_y0],HIGH);
		_DefaultColumnState();
		delay(_delay);
	}
}