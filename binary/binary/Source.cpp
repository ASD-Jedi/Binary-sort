#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <time.h>

#define sd sizeof(int)

void main()
{
	setlocale(LC_ALL, "RUSSIAN");
	int mass[30];
	//fpos_t
	srand(time(0));
	for (int i = 0; i < 30; i++)
		mass[i] = rand() % 100;

	FILE *strm;
	if (!(strm = fopen("data.bin", "wb+"))){
		puts("ошибка открытия файла");
	}
	rewind(strm);
	for (int i = 0; i < 30; i++){
		int f = mass[i];
		fwrite(&f, sd, 1, strm);
	}
	rewind(strm);

	for (int i = 30; i > 0; i--){
		for (int j = 0; j < i; j++){
			int now, next;
			fread(&now, sd, 1, strm);
			fread(&next, sd, 1, strm);
			fpos_t local;
			local = ftell(strm);
			if (now > next){
				fseek(strm, -8, 1);
				fwrite(&next, sd, 1, strm);
				fwrite(&now, sd, 1, strm);
			}
			fseek(strm, -4, 1);
		}
		rewind(strm);
	}
	rewind(strm);
	for (int i = 0; i < 30; i++){
		int t;
		fread(&t, sd, 1, strm);
		printf("%3d", t);
	}
	printf("\n");

	fclose(strm);
	system("PAUSE");
}