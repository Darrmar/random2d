#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include "random2dSokolovsky.h"

using namespace std;
using namespace random2d;

unsigned int vMonteKarlo(unsigned int mkn, unsigned int mkr) {
	//из за необходимости каждый раз генерировать рандомные числа, нужно делать эту функцию тут
	unsigned int x1, x2, x3, mkCount, vd, mkV, mkx;
	vd = 0; //расстояние от центра 
	int usl = mkr - vd; //растояние от центра <= радиусу сферы
	mkCount = 0; // счётчик выполнения условия
	while (usl >= 0) {
		//генерируем 3 случайных числа
		x1 = rand() % (mkr + 1);
		x2 = rand() % (mkr + 1);
		x3 = rand() % (mkr + 1);
		vd = sqrt(x1 * x1 + x2 * x2 + x3 * x3); //Считаем расстояние от центра
		mkCount++;
		usl = mkr - vd; //Обновляем условие
	}
	mkCount = mkCount - 1; //количество правельных выполнений
	mkx = (3 * mkCount)/mkn; //просто степень
	mkV = pow(mkr, mkx); //готовый объём
	return mkV;
}


int main(){

	setlocale(LC_ALL, "ru_RU.UTF-8");

	srand(time(NULL));

	unsigned int nm, nx, na, nc, nCount, nn, nr; 
	//nm - модуль(натуральное число), относительно которого вычисляется остаток от деления (m>=2; m=2^k, где k - натуральное число)
	//nx - начальное значение (0<=X<m)
	//na - множитель (0<=a<m)
	//nc - приращение (0<=c<m)
	//nCount - количество псевдослучайных чисел

	nCount = 10;

	string mode1, mode2;

	road roadRenamed{};

	cout << "Введите режим: console, file " << endl;
	cin >> mode1;

	if (mode1 == "console") {
		cout << "Кто введёт цифры:  self, auto ? " << endl;
		cin >> mode2;
		if (mode2 == "self") {
			cout << "Введите необходимые данные:" << endl << "Введите значение для M - модуля, где M > 2: ";
			cin >> nm;
			if (roadRenamed.checkM(nm) == 0) {
				cout << "Введите приращение C, где (0<=C<m): "; 
				cin >> nc;
				if (roadRenamed.checkC(nc, nm) == 0) {
					cout << "Введите начальное значение для X, где  (0<=X<m): ";
					cin >> nx;
					if (roadRenamed.checkX(nx, nm) == 0) {
						cout << "Введите множитель A, где (0<=A<m): ";
						cin >> na;
						if (roadRenamed.checkA(na, nm) == 0) {
							roadRenamed.formulaCheck(nm, nx, na, nc, nCount);
							for (roadRenamed.pnum = 0; roadRenamed.pnum < nCount; roadRenamed.pnum++) {
								cout << ((float)roadRenamed.massF[roadRenamed.pnum] + 1) / (nm + 1) << endl;
							}
							cout << "Введите количство N измерений для вычесление объема методо Монте-Карло	" << endl;
							cin >> nn;
							nr = rand()%10;
							cout << "Количество измерений - " << nn << endl << "Радиус - " << nr << endl << "Объем сферы - " << vMonteKarlo(nn, nr) << endl;

						}
						else {
							cout << "Введино не корректное число A" << endl;
						}
					}
					else {
						cout << "Введино не корректное число X" << endl;
					}
				}
				else{
					cout << "Введино не корректное число C" << endl;
				}
			}
			else {
				cout << "Введино не корректное число M" << endl;
			}
		}
		else if (mode2 == "auto") {
			nm = 0;
			nc = 0;
			nx = 0;
			na = 0;

			while (roadRenamed.checkM(nm) != 0){
				nm = rand();
			}

			while (roadRenamed.checkC(nc, nm) != 0) {
				nc = rand();
			}

			while (roadRenamed.checkX(nx, nm) != 0) {
				nx = rand();
			}

			while (roadRenamed.checkA(na, nm) != 0) {
				na = rand();
			}

			roadRenamed.formulaCheck(nm, nx, na, nc, nCount);
			for (roadRenamed.pnum = 0; roadRenamed.pnum < nCount; roadRenamed.pnum++) {
				cout << ((float)roadRenamed.massF[roadRenamed.pnum] + 1) / (nm + 1) << endl;
			}

			nn = 1 + rand() % 10;
			nr = rand() % 10;

			cout << "Количество измерений " << nn << endl << "Радиус " << nr << endl << "Объем сферы " << vMonteKarlo(nn, nr) << endl;
		}
	}
	else if (mode1 == "file") {
		ifstream r2dr("random2dSett.txt", ifstream::in);

		if (!r2dr) {
			cout << "Ошибка открытия файла " << endl;
		}
		else {

			r2dr >> nm;
			if (roadRenamed.checkM(nm) == 0) {
				r2dr >> nc;
				if (roadRenamed.checkC(nc, nm) == 0) {
					r2dr >> nx;
					if (roadRenamed.checkX(nx, nm) == 0) {
						r2dr >> na;
						if (roadRenamed.checkA(na, nm) == 0) {
							roadRenamed.formulaCheck(nm, nx, na, nc, nCount);
							for (roadRenamed.pnum = 0; roadRenamed.pnum < nCount; roadRenamed.pnum++) {
								cout << ((float)roadRenamed.massF[roadRenamed.pnum] + 1) / (nm + 1) << endl;
							}
						}
						else {
							cout << "Введино не корректное число A" << endl;
						}
					}
					else {
						cout << "Введино не корректное число X" << endl;
					}
				}
				else {
					cout << "Введино не корректное число C" << endl;
				}
			}
			else {
				cout << "Введино не корректное число M" << endl;
			}
			
		}
	}

	
	system("pause");
	return 0;
}