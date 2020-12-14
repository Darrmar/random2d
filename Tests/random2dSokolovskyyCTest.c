#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>
#include <math.h>
#include "random2dSokolovskyyC.h"

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

int main(void)
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    unsigned int nm, nx, na, nc, nCount, nn, nr;
	//nm - модуль(натуральное число), относительно которого вычисляется остаток от деления (m>=2; m=2^k, где k - натуральное число)
	//nx - начальное значение (0<=X<m)
	//na - множитель (0<=a<m)
	//nc - приращение (0<=c<m)
	//nCount - количество псевдослучайных чисел

    nCount = 10;

    char mode1[10];
    char mode2[5];
    printf("Введите режим: console, file\n");
    gets(mode1);

    if(strcmp(mode1,"console")==0){
        printf("Кто введёт цифры:  self, auto ?\n");
        gets(mode2);
		if (strcmp(mode2,"self") == 0) {
		    printf("Введите необходимые данные:\n");
            printf("Введите значение для M - модуля, где M > 2:\n");
			scanf("%u",&nm);
			if (checkM(nm) == 0){
                printf("Введите приращение C, где (0<=C<m): \n");
                scanf("%u", &nc);
                if(checkC(nc, nm) == 0){
                    printf("Введите начальное значение для X, где  (0<=X<m): \n");
                    scanf("%u", &nx);
                    if (checkX(nx, nm) == 0){
                        printf("Введите множитель A, где (0<=A<m): \n");
                        scanf("%u", &na);
                        if (checkA(na, nm) == 0){
                            formulaCheck(nm, nx, na, nc, nCount);
							for (pnum = 0; pnum < nCount; pnum++) {
                                float help = ((float)massF[pnum] + 1) / (nm + 1);
                                printf("%f",help);
                                printf("\n");
							}
                            printf("Введите количство N измерений для вычесление объема методо Монте-Карло\n");
                            scanf("%u", &nn);
                            nr = rand()%10;
                            printf("Количество измерений - ");
                            printf("%u", nn);
                            printf("\nРадиус - ");
                            printf("%u", nr);
                            printf("\nОбъем сферы - ");
                            printf("%u", vMonteKarlo(nn, nr));
                        }else{
                           printf("Введино не корректное число A\n");
                        }
                    }else {
                        printf("Введино не корректное число X\n");
                    }
                }else {
                    printf("Введино не корректное число C\n");
                }
			} else {
                printf("Введино не корректное число M\n");
			}
		}
		else if (strcmp(mode2,"auto") == 0) {
			nm = 0;
			nc = 0;
			nx = 0;
			na = 0;
			while (checkM(nm) != 0){
				nm = rand();
			}

			while (checkC(nc, nm) != 0) {
				nc = rand();
			}

			while (checkX(nx, nm) != 0) {
				nx = rand();
			}

			while (checkA(na, nm) != 0) {
				na = rand();
			}

			formulaCheck(nm, nx, na, nc, nCount);
			for (pnum = 0; pnum < nCount; pnum++) {
                float help = ((float)massF[pnum] + 1) / (nm + 1);
                printf("%f",help);
                printf("\n");
            }
            nn = rand()%10;
            nr = rand()%10;
            printf("Количество измерений - ");
            printf("%u", nn);
            printf("\nРадиус - ");
            printf("%u", nr);
            printf("\nОбъем сферы - ");
            printf("%u", vMonteKarlo(nn, nr));
		}
    }else if (strcmp(mode1,"file")==0){
        FILE *r2dfile;
        r2dfile = fopen ("random2dSett.txt", "r");
        if (r2dfile != NULL){
            fscanf(r2dfile,"%u", &nm);
			if (checkM(nm) == 0){
                fscanf(r2dfile,"%u", &nc);
                if(checkC(nc, nm) == 0){
                    fscanf(r2dfile,"%u", &nx);
                    if (checkX(nx, nm) == 0){
                        fscanf(r2dfile,"%u", &na);
                        if (checkA(na, nm) == 0){
                            formulaCheck(nm, nx, na, nc, nCount);
							for (pnum = 0; pnum < nCount; pnum++) {
                                float help = ((float)massF[pnum] + 1) / (nm + 1);
                                printf("%f",help);
                                printf("\n");
							}
                        }else{
                           printf("Введино не корректное число A\n");
                        }
                    }else {
                        printf("Введино не корректное число X\n");
                    }
                }else {
                    printf("Введино не корректное число C\n");
                }
			} else {
                printf("Введино не корректное число M\n");
			}

        }else{
            printf("Ошибка открытия файла\n");
            return 1;
        }
    }
    return 0;
}
