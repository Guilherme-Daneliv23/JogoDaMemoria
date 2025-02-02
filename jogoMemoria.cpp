#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define RESET "\033[0m"
#define BLACK "\033[1;30m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define PURPLE "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define ORANGE "\033[38;5;214m"

const char* colors[] = {
    "\033[1;31m",    // Vermelho
    "\033[1;32m",    // Verde
    "\033[1;33m",    // Amarelo
    "\033[1;34m",    // Azul
    "\033[1;35m",    // Roxo
    "\033[1;36m",    // Cyan
    "\033[1;37m",    // Branco
};

char** createCards(int);
int* setVetControl(int);
char** setCards(int);
char** setTab(int);
void printTab(char**, int);
void parcialTurn(char**, char**, int, int);
void verifyTurn(char**, char**, int, int, int, int, int*);
void scream(char**, int*, int*, int, int);
void headerArt();
void menu(int*);
void control(int);

int main()  {
	int op, tam = 0, valid_input;
    char buffer[256];
    setlocale(LC_ALL, "Portuguese");
    
    menu(&tam);
    
    while(op = 1)	{
    	control(tam);
    	while(1)	{
	    	printf("\n\n\nO que deseja fazer?\n");
	    	printf("1 - Jogar novamente\n");
	    	printf("2 - Voltar para o menu\n");
	    	printf("3 - Encerrar\n");
	    	printf("Digite sua escolha: ");
	    	valid_input = scanf("%d", &op);
	    	
	    	if (valid_input == 1 && op >= 1 && op <= 3) {
            	break;
	        } else {
	            fgets(buffer, sizeof(buffer), stdin);
	            printf("Valor inválido. Por favor, insira um número entre 1 e 5:\n");
	            system("pause");
	            system("cls");
	        }
		}
    	
    	
    	switch(op)	{
    		case 1: op = op;
    		        break;
    		case 2: system("cls");
    		        menu(&tam);
    		        op = op;
    		        break;
    		case 3: exit(0);
		}
	}
   
}

char** createCards(int N) {
    char** mat;
    int i, j;
    mat = (char**)malloc(N * sizeof(char*));
    if(mat == NULL) {
        printf("Erro de alocação!");
        return NULL;
    }
    
    for(i = 0; i < N; i++)  {
        mat[i] = (char*)malloc(N * sizeof(char));
        if(mat[i] == NULL)  {
            printf("Erro de alocação!");
            return NULL;
        }
    }

    return mat;
}

int* setVetControl(int tam)	{
	int* VetControl = (int*)malloc((tam * tam) * sizeof(int));
	int k, n, number, exist = 0;
	for(k = 0; k < (tam * tam); k++)	{
		VetControl[k] = 0;
	}
	
	srand(time(NULL));		
	for(k = 0; k < (tam * tam); k++)	{
		while(VetControl[k] == 0)	{	
			number = (rand() % ((tam * tam) / 2)) + 1;
			
			for(n = 0; n < (tam * tam); n++)	{
				if(VetControl[n] == number)	{
					exist++;
				}
			}
			
			if(exist < 2)	{
				VetControl[k] = number;
		    } else {
		    	exist = 0;
			}
		}
	}
	
	return VetControl;
}

char** setCards(int tam)	{
	char** Cards;
	int* VetControl;	
	int i, j, k = 0;
	Cards = createCards(tam);
	VetControl = setVetControl(tam);	
	
	for(i = 0; i < tam; i++)	{
		for(j = 0; j < tam; j++)	{
			Cards[i][j] = VetControl[k] + '0';
			k++;		
		}
	}
	
	return Cards;
}



char** setTab(int tam)	{
	char** Tab;
	int i, j;
	Tab = createCards(tam);
	
	for(i = 0; i < tam; i++)	{
		for(j = 0; j < tam; j++)	{
			Tab[i][j] = '*';
		}
	}
	
	return Tab;	
}

void printTab(char** Tab, int tam)	{
	int i, j, transformado;
	int align = (35 - (tam * 2)) / 2;
	
	system("cls");
	headerArt();
	for(i = 0; i < tam; i++)	{
    	printf("%*d| ", align, i);
		for(j = 0; j < tam; j++)	{
			if(Tab[i][j] != '*')	{
				transformado = Tab[i][j] - '0';
				printf("%s%c \033[0m", colors[transformado % 7], Tab[i][j]);
			} else {
				printf("%c ", Tab[i][j]);
			}
			
		}
		printf("\n");
	}
	
	printf("  %*s", align, "");
	for(i = 0; i < tam - 1; i++)	{
		printf("__");
	}
	printf("_\n");
	printf("  %*s", align, "");
	for(i = 0; i < tam; i++)	{
		printf("%d ", i);
	}
	printf("\n");
	printf("\n");
}

void parcialTurn(char** Tab, char** Cards, int linha, int coluna)	{
	Tab[linha][coluna] = Cards[linha][coluna]; 
}

void verifyTurn(char** Tab, char** Cards, int L1, int L2, int C1, int C2, int* hit)	{
	if((Tab[L1][C1] == Tab[L2][C2]))	{
		(*hit)++;	
	} else	{
		Tab[L1][C1] = '*';
		Tab[L2][C2] = '*';	
	}
}

void scream(char** TAB, int* L, int* C, int turn, int tam)	{
	int avaliable = 0;
	while(avaliable != 1)	{
		printf("Digite o par linha, coluna da carta %d: ", turn);
		scanf("%d %d", L, C);

		if(*L <= tam - 1 && *C <= tam - 1 && TAB[*L][*C] == '*')	{		
			avaliable = 1;
		} else if(*L <= tam - 1 && *C <= tam - 1)	{
			printf("Essa posição de jogada é inválida, ela já está revelada!\n");
			system("pause");
			printTab(TAB, tam);
		} else {
			printf("As coordenadas digitadas estão fora das dimensões do tabuleiro\n");
			system("pause");
			printTab(TAB, tam);
		}
	}
}

void headerArt()	{
	printf(PURPLE"===================================\n"RESET);
    printf("|                                 |\n");
    printf(CYAN"|         MEMORY CHALLENGE        |\n"RESET);
    printf("|                                 |\n");
    printf(PURPLE"===================================\n\n\n"RESET);
}

void menu(int* tam)	{
	char buffer[256];
	int valid_input, choose;
	
	while (1) {
		headerArt();
        printf("Escolha a dificuldade do seu Jogo: \n\n");
	    printf(GREEN"1 - 4 X 4\n"RESET);
	    printf(ORANGE"2 - 6 X 6\n"RESET);
	    printf(RED"3 - 10 X 10\n"RESET);
	    printf(PURPLE"4 - 12 X 12\n"RESET);
	    printf(BLUE"5 - Fechar o programa\n"RESET);
	    printf("Digite sua escolha: ");
		valid_input = scanf("%d", &choose);
        
        
        if (valid_input == 1 && choose >= 1 && choose <= 5) {
            break;
        } else {
            fgets(buffer, sizeof(buffer), stdin);
            printf("Valor inválido. Por favor, insira um número entre 1 e 5:\n");
            system("pause");
            system("cls");
        }
    }
    
    switch(choose) {
    	case 1: *tam = 4;
    			break;
    	case 2: *tam = 6;
    			break;
    	case 3: *tam = 10;
    			break;
    	case 4: *tam = 12;
    			break;
    	case 5: exit(0);
    			break;
		default: printf("Valor inválido");
				 system("cls");
				 menu(tam);
				 break;
	}
    	
    system("cls");
}

void  control(int tam)	{
	char** TAB;
	char** CARDS;	
    int i, j, linha, coluna, win = 0, L1, L2, C1, C2, hit = 0, turn = 0, op = 1, trys = 0; 

    system("cls");
    
    TAB = setTab(tam);
    CARDS = setCards(tam);
      
	while(win == 0)	{
		trys++;
    	printTab(TAB, tam);
 		turn = 1;
		scream(TAB, &L1, &C1, turn, tam);
		parcialTurn(TAB, CARDS, L1, C1);		
		printTab(TAB, tam);
		
		turn = 2;
		scream(TAB, &L2, &C2, turn, tam);
		parcialTurn(TAB, CARDS, L2, C2);
		printTab(TAB, tam);
		
		sleep(3);	
		verifyTurn(TAB, CARDS, L1, L2, C1, C2, &hit);
		printTab(TAB, tam);
		
		if(hit == (tam * tam) / 2)	{
			win = 1;
		}				
	}
	
	printf("Parabéns! Você ganhou!\n"); 	
	printf("O número de tentativas foi: %d", trys);
    
	free(TAB);
 	free(CARDS);
}
