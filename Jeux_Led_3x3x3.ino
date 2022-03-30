/*
	DATE    : 31/03/2022
	AUTHEUR : RACHEL SYSTEME
	GITHUB  : https://github.com/RS-malik-el
	YOUTUBE : https://www.youtube.com/channel/UCf4jGfp-BFp6GLd6eTptVMg?sub_confirmation=1

	Ce programme permet de contrôler l'allumage 
	d'une matrice cubique des leds de taille 3x3x3
	sous arduino arduino ou carte compatible avec l'IDE arduino
*/

#include "Matrix_3x3x3.h"

// Déclaration de l'objet Matrix_3x3x3
Matrix_3x3x3 Cube;

unsigned long _delay = 5000;
unsigned long depart = millis();

void setup(){
	Cube.Init_Random();
	Cube.AttachPinRow(2,3,4);
	Cube.AttachPinColumn(5,6,7,8,9,10,11,12,13);
}

void loop(){
	if ((millis()-depart) < _delay)
		Cube.Play_OneByOne();

	else if ((millis()-depart) < (_delay*2))
		Cube.Play_ThreeByThree();

	else if ((millis()-depart) < (_delay*3))
		Cube.Play_PlanByPlan(100);

	else if ((millis()-depart) < (_delay*4))
		Cube.Play_Randomly(1,100);

	else if ((millis()-depart) < (_delay*5))
		Cube.Play_Randomly(2,100);

	else if ((millis()-depart) < (_delay*6))
		Cube.Play_Randomly(3,100);

	else if ((millis()-depart) < (_delay*7))
		Cube.Play_Randomly(4,100);
	else
		depart = millis();
}