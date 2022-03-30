/*
	DATE    : 31/03/2022
	AUTHEUR : RACHEL SYSTEME
	GITHUB  : https://github.com/RS-malik-el
	YOUTUBE : https://www.youtube.com/channel/UCf4jGfp-BFp6GLd6eTptVMg?sub_confirmation=1

	Ce fichier, coder pour arduino, contient les fonctions ou méthodes vous permettant
	de contrôler l'allumage de vos leds dans une matrice cubique à leds de taille 3x3x3 
*/

#ifndef MATRIX_3X3X3
#define MATRIX_3X3X3

#include <Arduino.h>
#include <stdint.h>

class Matrix_3x3x3
{
	public:
		Matrix_3x3x3(void);
		~Matrix_3x3x3(void);

		void Init_Random();
		void AttachPinRow(uint8_t Pin_1, uint8_t Pin_2, uint8_t Pin_3);
		void AttachPinColumn(	uint8_t Pin_1, uint8_t Pin_2, uint8_t Pin_3,
								uint8_t Pin_4, uint8_t Pin_5, uint8_t Pin_6,
								uint8_t Pin_7, uint8_t Pin_8, uint8_t Pin_9
								);
		void Play_OneByOne(uint8_t _delay=100);
		void Play_ThreeByThree(uint8_t _delay=100);
		void Play_PlanByPlan(uint8_t _delay=100);
		void Play_Randomly(uint8_t nb = 1, uint8_t _delay=100);

	private:
		byte _Pin_Ligne[3] = {}; // les lignes sont négatives (y)
		byte _Pin_Colonne[3][3] = {}; // les colonnes sont positives (x)(z)
		byte _nb = 1;	// Sélection mode aléatoire valeur possible : 1 2 3 4
		
		/* 
			Variable permettant le choix aléatoire
		   	des leds sur le plan
		*/
		byte _Rand_x0 = 0; 
		byte _Rand_x1 = 0;
		byte _Rand_y0 = 0; 
		byte _Rand_y1 = 0;
		byte _Rand_z0 = 0; 
		byte _Rand_z1 = 0;

		void _DefaultColumnState(void); // Etat par défaut des leds
		void _Draw(); // Tirage aléatoire des leds
		void _Random_OneByOne(uint8_t _delay=100);
		void _Random_TwoByTwo(uint8_t _delay=100);
		void _Random_ThreeByThree(uint8_t _delay=100);
		void _Random_PlanByPlan(uint8_t _delay=100);
};
#endif