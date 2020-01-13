#include "campo.h"
#include <conio.h>

int main() {
	bool logical = 1;
	char direzione;

	campo c(30, 40, 0, 0, false);
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
		c.aggiungiOstacoli();
		c.stampa();
		c.muoviMacchina(_getch());

	}

	return 0;
}