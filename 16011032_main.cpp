#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"

using namespace std;

void sagaDondur(short n, int resim);
void solaDondur(short n, int resim);

int main(void) {
	int M, N, Q, i, j, k;
	bool type;
	int efile, islem;
	char resimadi[100], sonek[10];
	do {
		printf("Islem yapilacak resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &resimadi);
		system("CLS");
		efile = readImageHeader(resimadi, N, M, Q, type);
	} while (efile > 1);
	printf("%s\n", resimadi);
	int** resim = resimOku(resimadi);

	short *resimdizi;
	resimdizi = (short*) malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++) 
		for (j = 0; j < M; j++) 
			resimdizi[i*N + j] = (short) resim[i][j];

	int resimadres = (int) resimdizi;

	do {
		system("CLS");
		printf("\t     ISLEMLER\n");
		printf("------------------------------------\n");
		printf("1)  Resmi saga dondur\n");
		printf("2)  Resmi sola dondur\n");
		printf("0)  Cikis\n\n");
		printf("\"%s\" yolundaki resim icin yapilacak islemi seciniz\n-> ", resimadi);
		scanf("%d", &islem);
	} while (islem > 2 || islem < 0);

	switch (islem) {
		case 0:
			exit(0);
		case 1:
			sagaDondur(N, resimadres);
			strcpy(sonek, "_sag.pgm");
			break;
		case 2:
			solaDondur(N , resimadres);
			strcpy(sonek, "_sol.pgm");
			break;
		default:
			strcpy(sonek, "_orj.pgm");
			break;
	}

	for (k = 0; k < N * M; k++) {
		j = k % N;
		i = k / N;
		resim[i][j] = (int)resimdizi[k];
	}
	
	string::size_type pos = string(resimadi).find_last_of(".");
	resimadi[pos] = '\0';
	strcat(resimadi, sonek);
	resimYaz(resimadi, resim, N, M, Q);
	printf("\nIslem basariyla tamamlandi :)\n\"%s\" yolunda resim olusturuldu.\n\n", resimadi);
	system("PAUSE");
	return 0;
}

void sagaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	printf(" \n \n    -----  16011032    Faruk ARSLAN  -----\n\n");
	__asm {
		MOV EBX, resim

		XOR EAX, EAX
		XOR EDX, EDX
		XOR ESI, ESI   //ESI=x EDI=y
		XOR ECX, ECX
		XOR EDI, EDI
		MOV CX, n

lopdis: PUSH CX
		MOV EDI, ESI

		MOV CX, n
		SUB CX, SI

lopic:	MOV EAX, ESI

		PUSH ESI
		XOR ESI, ESI
		MOV SI, n
		MUL ESI
		POP ESI

		ADD EAX, EDI
		SHL EAX, 1
		PUSH ESI
		MOV ESI, EAX
		POP EDX
		PUSH WORD PTR[EBX + ESI]

		MOV ESI, EDX
		MOV EDX, EAX

		MOV EAX, EDI
		PUSH EDX
		PUSH EDI
		XOR EDI, EDI
		MOV DI, n
		MUL EDI
		POP EDI
		POP EDX
		ADD EAX, ESI
		SHL EAX, 1

		PUSH EDI
		MOV EDI, EAX
		MOV AX, WORD PTR[EBX + EDI]

		PUSH ESI
		MOV ESI, EDX
		MOV WORD PTR[ESI + EBX], AX
		POP ESI


		MOV EDX, EDI
		POP EDI


		POP AX
		PUSH ESI
		MOV ESI, EDX
		MOV WORD PTR[ESI + EBX], AX
		POP ESI

		INC EDI
		LOOP lopic
		POP CX
		INC ESI
		LOOP lopdis


; -----------------ilk iç içe döngü bitti , ikindi iç içe döngü baþlýyor -------------------------------

		MOV EBX, resim

		XOR EAX, EAX
		XOR EDX, EDX
		XOR ESI, ESI   //ESI=i EDI=j
		XOR ECX, ECX
		XOR EDI, EDI
		MOV CX, n

lopdis2:PUSH CX
		XOR EDI, EDI

		MOV CX, n
		SHR CX, 1

lopic2: MOV EAX, ESI

		PUSH ESI
		XOR ESI, ESI
		MOV SI, n
		MUL ESI
		POP ESI

		ADD EAX, EDI
		SHL EAX, 1

		PUSH EDI
		MOV EDI, EAX
		POP EDX
		PUSH WORD PTR[EDI + EBX]
		MOV EDI, EDX

		MOV EDX, EAX


		XOR EAX,EAX
		MOV EAX,ESI
											
		PUSH EDX
		PUSH ESI
		XOR ESI, ESI
		MOV SI, n
		MUL ESI
		POP ESI
		POP EDX

		PUSH ESI
		XOR ESI,ESI
		MOV SI,n
		ADD EAX,ESI
		POP ESI
		SUB EAX,EDI
		DEC EAX

											
		SHL EAX, 1


		PUSH ESI
		MOV ESI, EAX
		MOV AX, WORD PTR[EBX + ESI]

		PUSH EDI
		MOV EDI, EDX
		MOV WORD PTR[EBX + EDI], AX
		POP EDI

		MOV EDX, ESI
		POP ESI

		POP AX
		PUSH ESI
		MOV ESI, EDX
		MOV WORD PTR[ESI + EBX], AX
		POP ESI

		INC EDI

		LOOP lopic2
		POP CX
		INC ESI
		LOOP lopdis2
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

void solaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	printf(" \n \n    -----  16011032    Faruk ARSLAN  -----\n\n");
	__asm {
		MOV EBX, resim
		
		XOR EAX, EAX
		XOR EDX, EDX
		XOR ESI, ESI   //ESI=x EDI=y
		XOR ECX, ECX
		XOR EDI, EDI
		MOV CX, n

lopdis: PUSH CX
		MOV EDI, ESI

		MOV CX, n
		SUB CX, SI

lopic:	MOV EAX, EDI

		PUSH ESI
		XOR ESI, ESI
		MOV SI, n
		MUL ESI
		POP ESI

		ADD EAX, ESI
		SHL EAX, 1
		PUSH EDI
		MOV EDI, EAX
		POP EDX
		PUSH WORD PTR[EBX + EDI]
		
		MOV EDI, EDX
		MOV EDX,EAX

		MOV EAX, ESI
		PUSH EDX
		PUSH ESI
		XOR ESI, ESI
		MOV SI, n
		MUL ESI
		POP ESI
		POP EDX
		ADD EAX, EDI
		SHL EAX, 1
		
		PUSH ESI
		MOV ESI, EAX
		MOV AX, WORD PTR[EBX + ESI]

		PUSH EDI
		MOV EDI, EDX
		MOV WORD PTR[EDI + EBX], AX
		POP EDI
		
		
		MOV EDX,ESI
		POP ESI
		

		POP AX
		PUSH EDI
		MOV EDI, EDX
		MOV WORD PTR[EDI + EBX], AX
		POP EDI

		INC EDI
		LOOP lopic
		POP CX
		INC ESI
		LOOP lopdis


		;----------------------ilk iç içe döngü bitti ikinci iç içe döngü baþlýyor-----------------
		
		MOV EBX, resim

		XOR EAX, EAX
		XOR EDX, EDX
		XOR ESI, ESI   //ESI=i EDI=j
		XOR ECX, ECX
		XOR EDI, EDI
		MOV CX, n

lopdis2: PUSH CX
		XOR EDI,EDI

		MOV CX, n
		SHR CX,1
		
lopic2:	MOV EAX, EDI
		
		PUSH ESI
		XOR ESI,ESI
		MOV SI,n
		MUL ESI
		POP ESI
		
		ADD EAX,ESI
		SHL EAX,1

		PUSH ESI
		MOV ESI,EAX
		POP EDX
		PUSH WORD PTR[ESI + EBX]
		MOV ESI,EDX
		
		MOV EDX,EAX


		XOR EAX,EAX
		MOV AX,n
		SUB EAX,EDI
		DEC EAX
	
		PUSH EDX
		PUSH ESI
		XOR ESI,ESI
		MOV SI,n
		MUL ESI
		POP ESI
		POP EDX

		ADD EAX,ESI
		SHL EAX,1

		
		PUSH EDI
		MOV EDI,EAX
		MOV AX,WORD PTR[EBX + EDI]

		PUSH ESI
		MOV ESI,EDX
		MOV WORD PTR[EBX + ESI],AX
		POP ESI

		MOV EDX,EDI
		POP EDI

		POP AX
		PUSH EDI
		MOV EDI,EDX
		MOV WORD PTR[EDI + EBX],AX
		POP EDI

		INC EDI
		
		LOOP lopic2
		POP CX
		INC ESI
		LOOP lopdis2

	}
	
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}
