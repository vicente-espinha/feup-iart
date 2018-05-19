/*
 * menu.h
 *
 *  Created on: 28/03/2017
 *      Author: up201503344
 */

#ifndef SRC_MENU_H_
#define SRC_MENU_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <cstdio>
#include <algorithm>
#include "Emergencia.h"
#include <string>

#define CLEAN_LINE "                                                                                              ";


/**
 * Funcao que representa o menu principal do programa em que deteta o uso de teclas do teclado de forma a escolher
 * a opcao pretendida
 * @param em objeto da classe Emergencia  que a logica do programa se baseia
 */
void menu_principal(Emergencia &em);
/**
 * Representa um sub menu que sucede o menu principal em que o utilizador pode escolher que tipo de emergencia quer
 * assistencia
 * @param em objeto onde se encontra todas as variaveis responsaveis pela logica do programa
 */
void capacityMenu(Emergencia &em, int type);
/**
 * Sub menu que sucede o menu tipoEmergencia em que o utilizador escolhe o nivel de risco do tipo de emergencia que escolheu anteriormente
 * @param em objeto necessario para o uso da logica por detras do programa
 * @param typeFlag inteiro que representa o tipo de emergencia escolhida no menu tipoEmergencia
 */
void algorithmMenu(Emergencia &em,int typeFlag);
/**
 * Mini menu de escolha de como o utilizador quer escolher a zona de emergencia,atraves do nome da rua, ou atraves do ID do No especifico
 * @param em objeto do tipo emergencia onde se encontra o grafo onde estao guardados os Nos
 * @return o ID do No escolhido
 */

void gotoXY(int x,int y);


#endif /* SRC_MENU_H_ */
