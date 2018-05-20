/*
 * menu.cpp
 *
 *  Created on: 28/03/2017
 *      Author: up201503344
 */

#include "menu.h"

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Retrieves a handle for the standard input, standard output, or standard error device
COORD CursorPosition; // Defines the coordinates of a character cell in a console screen buffer used in gotoXY


void menu_principal(Emergencia &em)

{

	int menu_item = 0; //usada para saber qual e o caso do switch que esta a apontar
	int x = 10; //usada para saber a linha que a seta esta apontar
	bool running = true;
	system("CLS");//cleans cmd

	gotoXY(18, 10); cout << "->";

	while (running)
	{
		gotoXY(18, 8); cout << " Rescue Points:";
		gotoXY(20, 10);  cout << " One";
		gotoXY(20,11); cout << " Many";
		gotoXY(20, 12);  cout << " Exit";

		system("pause>nul"); // the >nul bit causes it to print no message

		if (!GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(0x31) && !GetAsyncKeyState(0x32) )// se for clicado uma tecla diferente das setas (cima e baixo) e enter, nao faz nada
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && x != 12) //down button pressed and
		{
			gotoXY(18, x); cout << "  ";//limpa seta
			x++;
			gotoXY(18, x); cout << "->";//seta aponta para a proxima linha do menu
			menu_item++;//faz com que este valor seja coerente com a linha que esta apontar
			continue;

		}
		else if (GetAsyncKeyState(VK_DOWN) && x == 12) // se precionar para baixo na ultima linha do menu, volta a primeira linha do mesmo
		{
			gotoXY(18, x); cout << "  ";//"limpa" a seta
			x = 10;//posicao em x da pos inicial
			gotoXY(18, x); cout << "->"; // mete a seta nessa pos inicial
			menu_item = 0;//atribui o caso 0 do switch para a primeira linha como e suposto
			continue;

		}

		else if (GetAsyncKeyState(VK_UP) && x != 10) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";//seta aponta para a linha anterior
			menu_item--;
			continue;
		}
		else if (GetAsyncKeyState(VK_UP) && x == 10)//se precionar para cima na primeira linha do menu a seta passa a apontar para a ultima linha do mesmo
		{
			gotoXY(18, x); cout << "  ";
			x = 12;//pos em x da pos final do menu (defenido nos couts)
			gotoXY(18, x); cout << "->";//mete seta nessa posicao
			menu_item = 3; // menu_item correspondente a ultima linha do menu
			continue;


		}
		else if (GetAsyncKeyState(0x31))
		{
			gotoXY(18, x); cout << "  ";
			x = 10;
			gotoXY(18, x); cout << "->";
			menu_item = 0;
			continue;
		}
		else if (GetAsyncKeyState(0x32))
		{
			gotoXY(18, x); cout << "  ";
			x = 11;
			gotoXY(18, x); cout << "->";
			menu_item = 1;
			continue;
		}
		else if (GetAsyncKeyState(0x33))
		{
			gotoXY(18, x); cout << "  ";
			x = 12;
			gotoXY(18, x); cout << "->";
			menu_item = 2;
			continue;
		}
		else if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed
			//dependendo da posicao da seta no menu, ao carregar enter vera o valor do menu_item correspondente a essa linha e executa a opcao escolhida

			switch (menu_item) {

			case 0: {
				gotoXY(20,16);
				//capacityMenu(em,1);
				em.readHospitals("../files/hospitals.txt");
				em.readInem("../files/ambulances.txt");
				string rescue_filename ="../files/rescue_one.txt";
				em.readResgate(rescue_filename);
				em.readNodes();
				em.readStreets();
				em.displayGraph();
				algorithmMenu(em,2);
				running = false;
				break;
			}

			case 1:{
				em.readHospitals("../files/hospitals.txt");
				em.readInem("../files/ambulances.txt");
				string rescue_filename ="../files/rescue_many.txt";
				em.readResgate(rescue_filename);
				em.readNodes();
				em.readStreets();
				em.displayGraph();
				algorithmMenu(em,2);
				running = false;
				system("CLS");
				break;
			}
			case 2: {
				gotoXY(20, 17);//para que o proximo cout nao sobreponha o menu
				cout << "Bye!";
				Sleep(3000);
				running = false;//de forma a sair do while
				break;
			}
		 }

		}

	}

	gotoXY(20, 17);// para que a mensagem de fechar o programa "Press any key to continue..." se encontra uma linha apos o cout apresentado ao querer sair do programa
	exit(0);//fecha o programa

}



void capacityMenu(Emergencia &em, int type)
{
	int menu_item = 0; //usada para saber qual e o caso do switch que esta a apontar
	int 	x = 10; //usada para saber a linha que a seta esta apontar
	bool running = true;
	system("CLS");//cleans cmd

	string rescue_filename;

	if(type == 1)
		rescue_filename ="../files/rescue_one.txt";
	else
		rescue_filename ="../files/rescue_many.txt";


	gotoXY(20, 10); cout << "->";

	while (running)
	{
		gotoXY(18, 8); cout << "Capacity : ";
		gotoXY(20, 10);  cout << " Infinite";
		gotoXY(20, 11);  cout << " Limited";
		gotoXY(20,12);  cout << " Return";

		system("pause>nul"); // the >nul bit causes it to print no message

		if (!GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(0x31) && !GetAsyncKeyState(0x32) && !GetAsyncKeyState(0x33) )// se for clicado uma tecla diferente das setas (cima e baixo) e enter, nao faz nada
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && x != 12) //down button pressed and
		{
			gotoXY(18, x); cout << "  ";//limpa seta
			x++;
			gotoXY(18, x); cout << "->";//seta aponta para a proxima linha do menu
			menu_item++;//faz com que este valor seja coerente com a linha que esta apontar
			continue;

		}
		else if (GetAsyncKeyState(VK_DOWN) && x == 12) // se precionar para baixo na ultima linha do menu, volta a primeira linha do mesmo
		{
			gotoXY(18, x); cout << "  ";//"limpa" a seta
			x = 10;//posicao em x da pos inicial
			gotoXY(18, x); cout << "->"; // mete a seta nessa pos inicial
			menu_item = 0;//atribui o caso 0 do switch para a primeira linha como e suposto
			continue;

		}

		else if (GetAsyncKeyState(VK_UP) && x != 10) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";//seta aponta para a linha anterior
			menu_item--;
			continue;
		}
		else if (GetAsyncKeyState(VK_UP) && x == 10)//se precionar para cima na primeira linha do menu a seta passa a apontar para a ultima linha do mesmo
		{
			gotoXY(18, x); cout << "  ";
			x = 12;//pos em x da pos final do menu (defenido nos couts)
			gotoXY(18, x); cout << "->";//mete seta nessa posicao
			menu_item = 2; // menu_item correspondente a ultima linha do menu
			continue;


		}
		else if (GetAsyncKeyState(0x31))
		{
			gotoXY(18, x); cout << "  ";
			x = 10;
			gotoXY(18, x); cout << "->";
			menu_item = 0;
			continue;
		}
		else if (GetAsyncKeyState(0x32))
		{
			gotoXY(18, x); cout << "  ";
			x = 11;
			gotoXY(18, x); cout << "->";
			menu_item = 1;
			continue;
		}
		else if (GetAsyncKeyState(0x33))
		{
			gotoXY(18, x); cout << "  ";
			x = 12;
			gotoXY(18, x); cout << "->";
			menu_item = 2;
			continue;
		}
		else if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed
			//dependendo da posicao da seta no menu, ao carregar enter vera o valor do menu_item correspondente a essa linha e executa a opcao escolhida

			switch (menu_item) {

			case 0: {

				em.readHospitals("../files/hospitals.txt");
				em.readInem("../files/ambulances.txt");
				em.readResgate(rescue_filename);
				em.readNodes();
				em.readStreets();
				em.displayGraph();
				algorithmMenu(em,1);
				running = false;
				system("CLS");
				break;
			}


			case 1: {

				em.readHospitals("../files/hospitals.txt");
				em.readInem("../files/ambulances.txt");
				em.readResgate(rescue_filename);
				em.readNodes();
				em.readStreets();
				em.displayGraph();

				algorithmMenu(em,2);
				running = false;
				system("CLS");
				break;
			}

			case 2: {
				running = false;
				system("CLS");
				break;
			}
			}

		}

	}

	gotoXY(20, 17);// para que a mensagem de fechar o programa "Press any key to continue..." se encontra uma linha apos o cout apresentado ao querer sair do programa
	return;

}

void algorithmMenu(Emergencia &em,int typeFlag)
{
	int menu_item = 0; //usada para saber qual e o caso do switch que esta a apontar
	int 	x = 10; //usada para saber a linha que a seta esta apontar
	bool running = true;
	system("CLS");//cleans cmd

	gotoXY(18, 10); cout << "->";

	while (running)
	{
		gotoXY(18, 8); cout << "Algorithm:";
		gotoXY(20, 10);  cout << " A*";
		gotoXY(20, 11);  cout << " Dijkstra";
		gotoXY(20,12);  cout << " Exit";

		system("pause>nul"); // the >nul bit causes it to print no message

		if (!GetAsyncKeyState(VK_DOWN) && !GetAsyncKeyState(VK_UP) && !GetAsyncKeyState(VK_RETURN) && !GetAsyncKeyState(0x31) && !GetAsyncKeyState(0x32) && !GetAsyncKeyState(0x33) )// se for clicado uma tecla diferente das setas (cima e baixo) e enter, nao faz nada
		{
			continue;
		}

		if (GetAsyncKeyState(VK_DOWN) && x != 12) //down button pressed and
		{
			gotoXY(18, x); cout << "  ";//limpa seta
			x++;
			gotoXY(18, x); cout << "->";//seta aponta para a proxima linha do menu
			menu_item++;//faz com que este valor seja coerente com a linha que esta apontar
			continue;

		}
		else if (GetAsyncKeyState(VK_DOWN) && x == 12) // se precionar para baixo na ultima linha do menu, volta a primeira linha do mesmo
		{
			gotoXY(18, x); cout << "  ";//"limpa" a seta
			x = 10;//posicao em x da pos inicial
			gotoXY(18, x); cout << "->"; // mete a seta nessa pos inicial
			menu_item = 0;//atribui o caso 0 do switch para a primeira linha como e suposto
			continue;

		}

		else if (GetAsyncKeyState(VK_UP) && x != 10) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";//seta aponta para a linha anterior
			menu_item--;
			continue;
		}
		else if (GetAsyncKeyState(VK_UP) && x == 10)//se precionar para cima na primeira linha do menu a seta passa a apontar para a ultima linha do mesmo
		{
			gotoXY(18, x); cout << "  ";
			x = 12;//pos em x da pos final do menu (defenido nos couts)
			gotoXY(18, x); cout << "->";//mete seta nessa posicao
			menu_item = 2; // menu_item correspondente a ultima linha do menu
			continue;


		}
		else if (GetAsyncKeyState(0x31))
		{
			gotoXY(18, x); cout << "  ";
			x = 10;
			gotoXY(18, x); cout << "->";
			menu_item = 0;
			continue;
		}
		else if (GetAsyncKeyState(0x32))
		{
			gotoXY(18, x); cout << "  ";
			x = 11;
			gotoXY(18, x); cout << "->";
			menu_item = 1;
			continue;
		}
		else if (GetAsyncKeyState(0x33))
		{
			gotoXY(18, x); cout << "  ";
			x = 12;
			gotoXY(18, x); cout << "->";
			menu_item = 2;
			continue;
		}
		else if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed
			//dependendo da posicao da seta no menu, ao carregar enter vera o valor do menu_item correspondente a essa linha e executa a opcao escolhida

			switch (menu_item) {

			case 0: {

				int noid;
				gotoXY(20,17);
				em.path(true);
				//em.displaySmallGraph();
				cin.get();
				em.closeGV();
				Emergencia emergencia(true);
				menu_principal(emergencia);
				running = false;
				system("CLS");

				break;
			}
			case 1: {
				int noid;
				gotoXY(20,17);
				em.path(false);
				//em.displaySmallGraph();
				cin.get();
				em.closeGV();
				Emergencia emergencia(true);
				menu_principal(emergencia);
				running = false;
				system("CLS");

				break;
			}

			case 2: {
				gotoXY(20,17);
				running = false;
				system("CLS");
				break;
			}




			}

		}

	}

	gotoXY(20, 17);// para que a mensagem de fechar o programa "Press any key to continue..." se encontra uma linha apos o cout apresentado ao querer sair do programa
	return;
}

// ---------------------- lOCALIZAR CURSOR

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

