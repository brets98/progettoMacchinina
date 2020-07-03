#pragma once


class macchina
{
	protected:
	
	//Coordinate Macchina
		int riga;
		int colonna;

	public:

		macchina(int r, int c);
		void scriviM();
		void muoviM(char direzione);
		void spostaNemica();
		void distruggiNemica();


};

