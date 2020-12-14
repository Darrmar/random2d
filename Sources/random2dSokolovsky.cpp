#include "random2dSokolovsky.h"
#include "math.h"

using namespace std;

int random2d::road::checkM(unsigned int cm){
	unsigned int ck = 2; // число которым мы будет проверять выполнения условий числа nm
	for (ck = 2; ck < cm;) { // число nk это степень натурального числа 
		ck = ck * 2; //2 в степень
	}
	if (ck == cm) {
		return 0;
	}
	else {
		return 1;
	}
}

int random2d::road::checkA(unsigned int caa, unsigned int cmm){
	if ((caa - 1) % 2 == 0 && caa < cmm && caa != 0) { //все делители числа м = 2 
		return 0;
	}
	else {
		return 1;
	}
}

int random2d::road::checkC(unsigned int acc, unsigned int amm){

	if (acc % 2 == 0) { //m - 2 в степени. Достаточно узнать, делиться ли число с на 2 без остатка
		return 1;
	}
	else if (acc < amm && acc != 0){
		return 0;
	}
}

int random2d::road::checkX(unsigned int cxx, unsigned int cxm) {

	if (cxx < cxm && cxx != 0) { //для Х особо нет условий, он должен быть меньше М
		return 0;
	}
	else {
		return 1;
	}
}

unsigned int random2d::road::formulaCheck(unsigned int fm, unsigned int fx, unsigned int fa, unsigned int fc, unsigned int fnCount){

	nextNumber = (fa * fx + fc) % fm;
	for (int i = 0; i < fnCount; i++) {
		nextNumber = (fa * nextNumber + fc) % fm;//считаем следующие число
		massF[pnum] = nextNumber; //записываем в массив
		pnum++;
	}
	return 0;
}
