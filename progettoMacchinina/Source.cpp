#include "campo.h"
#include <conio.h>

int main() {
	bool logical = 1;
	char direzione;

	campo c(30, 40, 0);
	c.sigla();
	system("pause");
	system("cls");
	c.regolamento();
	system("pause");
	system("cls");
	c.stampa();
	system("pause");
	while (logical == 1)
	{

		system("cls");
		c.aggiungiO();
		c.stampa();

		//controllo del movimento della macchina 
		switch (_getch())
		{
		case('a'):
		case('A'):
			c.muoviSinistra();
			break;
		case('d'):
		case('D'):
			c.muoviDestra();
			break;
		default:
			break;
		}


	}




	return 0;
}