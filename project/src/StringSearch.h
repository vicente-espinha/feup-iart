/*
 * StringSearch.h
 *
 *  Created on: 05/05/2017
 *      Author: Rui Quaresma
 */

#ifndef SRC_STRINGSEARCH_H_
#define SRC_STRINGSEARCH_H_


#include <stdio.h>
#include <fstream>

#include <vector>
#include <sstream>
#include <iostream>
#include <string>
#include "Veiculo.h"
#include "No.h"

void prefixFunction(string pattern, int pi[]);

bool KMP(string pattern, string target);

int editDistance(string pattern, string text);


#endif /* SRC_STRINGSEARCH_H_ */
