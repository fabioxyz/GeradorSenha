#include <stdio.h>
#define WIN32_LEAN_AND_MEAN // Reduz as defini��es ao incluir windows.h
// sem esta define, o resto do codigo dava erro com o include <windows.h> nsei pq
#include <windows.h>         // usar o Sleep(milisegundos); 
#define NESTRELAS 33
#define TMAX 100
#define CMAX 30

void imprimir_estrelas(int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("*");
	}
}

void interface() {
	imprimir_estrelas(NESTRELAS); putchar('\n');
	imprimir_estrelas(NESTRELAS); putchar('\n');
	imprimir_estrelas(1); printf("\t\t\t\t"); imprimir_estrelas(1); putchar('\n');
	imprimir_estrelas(1); printf("\tGERADOR DE SENHAS\t"); imprimir_estrelas(1); putchar('\n');
	imprimir_estrelas(1); printf("\t  By - Fabioxyz\t\t"); imprimir_estrelas(1); putchar('\n');
	imprimir_estrelas(1); printf("\t\t\t\t"); imprimir_estrelas(1); putchar('\n');
	imprimir_estrelas(NESTRELAS); putchar('\n');
	imprimir_estrelas(NESTRELAS); putchar('\n'); putchar('\n');
}

int sgerador(int c, char n, int s, char senhas[]) {
	char* pi;

	switch (n) {
	case 'S':
	case 's': {
		char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		int num_caracteres = sizeof(caracteres) - 1; // -1 para nao contar o \0
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < c; j++) {
				senhas[i * (c + 1) + j] = caracteres[rand() % num_caracteres]; // Gera um caractere aleat�rio
				// o rand usa um numero aleatorio, mas para limitar uso o % num_caracteres
				// ou seja, o resto de um numero aleatorio pelo numero de caracteres sera sempre
				// um numero entre 0 e o num de caracteres(ex: resto de 12424 % 62 = 24)
								// o resto vai estar sempre nesse intervalo(matematica).
			}
			senhas[i * (c + 1) + c] = '\0';  // Adiciona o terminador nulo ao final de cada senha
		}
	} break;
	case 'N':
	case 'n': {
		char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
		int num_caracteres = sizeof(caracteres) - 1; // -1 para nao contar o \0
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < c; j++) {
				senhas[i * (c + 1) + j] = caracteres[rand() % num_caracteres]; 
			}
			senhas[i * (c + 1) + c] = '\0';
		}
	} break;
}
	return 0;
}

int criarTxt(char senhas[], int c, int s, char path[]) {
	FILE* fp = fopen(path, "w");
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return 1;
	}

	for (int i = 0; i < s; i++) {
		fprintf(fp, "Senha %d: %s\n", i + 1, &senhas[i * (c + 1)]);
	}
	fclose(fp);

	return 0;
}

int main() {
	int i, caracteres, nsenhas, resultger, resultTxt;
	char escolha, senhas[TMAX * (CMAX + 1)];
	char path[] = "senhasGeradas.txt";

	interface();

	printf("Quantidade de caracteres desejada(Max:%d) : ", CMAX);
	scanf("%d", &caracteres);
	if (caracteres < 0 || caracteres > CMAX) {
		printf("Numero de caracteres invalido.");
		return 1;
	}
	printf("Numeros na senha?(S/N) : ");
	scanf(" %c", &escolha);
	if (escolha != 'S' && escolha != 's' && escolha != 'N' && escolha != 'n') {
		printf("Resposta invalida.");
		return 1;
	}
	printf("Quantidade de Senhas(Max:%d) : ", TMAX);
	scanf("%d", &nsenhas);
	if (nsenhas < 0 || nsenhas > TMAX) {
		printf("Numero de senhas invalido.");
		return 1;
	}
	printf("Gerando suas senhas...\n");


	srand(time(NULL)); // Inicializa o gerador de n�meros aleat�rios
	resultger = sgerador(caracteres, escolha, nsenhas, senhas);
	Sleep(9000);
	if (resultger == 0) {
		printf("Senhas geradas com sucesso!\n\n");
	}
	else {
		printf("Erro ao gerar senhas.");
		return 1;
	}

	
	printf("Criando arquivo...\n");
	Sleep(6000);
	resultTxt = criarTxt(senhas, caracteres, nsenhas, path);
	if (resultTxt == 0) {
		printf("Arquivo %s criado com sucesso!", path);
	}
	else {
		printf("Erro ao criar arquivo.");
		return 1;
	}

	// Espera intera��o antes de encerrar
	printf("\n\nPressione Enter para sair...");
	getchar(); // Captura o Enter pendente do �ltimo scanf
	getchar(); // Aguarda o usu�rio pressionar Enter

	return 0;
}
