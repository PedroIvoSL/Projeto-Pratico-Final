/*
Objetivo: Fazer um programa que facilite na hora de vender passagens áreas
Entrada: Destino, Idade e Quantidade de assentos existentes do avião
Saida: Se a passagens disponíveis para determinado vôo
*/

#include <stdio.h> //Biblioteca que possibilita o uso das fuções "printf" e "scanf"
#include "conio.h" //Biblioteca para colorir o console
#include <stdlib.h> //Biblioteca de propósito geral padrão da linguagem de programação C. Ela possui funções envolvendo alocação de memória, controle de processos, conversões e outras. Ela é compatível com C++ e é chamada cstdlib em C
//#include <locale.h> //Optei em não ultilizar o "locale" pelo motivo do mesmo mudar a tabela ASCII assim atrapalhando em algumas funçoes
#include <string.h> //Biblioteca que faciliata o manuseio de strings

struct tReserva{ //em minha defesa, eu aprendi struct com as aulas do Edson :)
	int codigo;
	int menor5;
	int assento;
	char marca;
};
//Prototipos de função abaixo:
void removerPulaLinha (char[]);
int menuPrincipal (void);
int lerValidarOpc (void);
int lerValidarQntAssentos (char []);
void lerValidarDestino (char[]);
float lerValidarPreco (void);
void inicializarAssentos (char assnt[], int qntAssentos);
void mostrarAssentos (int qntAssentos, char assnt[]);
int lerValidarAssentos (char assentos[], int numAssento, int qntAssentos);
int lerValidarIdade(void);
void reservarAssento(char assentos[], int codAssento);
void mostarSituacao (char assentos[], int qntAssentos);
int validarCodigo (struct tReserva reservas[], int chave, int countCodigo, char assentos[]);
float calcularVendas (int countConfirmado, struct tReserva reservas[], float preco);

int main(void){

    int opcao = 0, qntAssentos, flag, countCodigoReserva = 0, chave, vendasConfirmadas, countConfirmado = 0;
    float preco;
    char destino[50], assentos[200];
    struct tReserva reservas[200];
    struct tReserva reservaAux;
    struct tReserva reservasConfirmadas[200];

    printf("Bem-vindo a plataforma da Salumar linhas aereas!\n");
    printf("\nO melhor site para fazer compras de passagens aereas!");
    printf("\n\nPressione qualquer tecla para continuar...");
    getch();
    system("cls");

	lerValidarDestino(destino);
	qntAssentos = lerValidarQntAssentos(destino);
	inicializarAssentos(assentos, qntAssentos);
	preco = lerValidarPreco();


    printf("\nSucesso!");
    printf("\nPressione qualquer tecla para continuar...");
    getch();
    system("cls");

    do{
    	opcao = menuPrincipal();
    	switch(opcao){
        case 1:
        	system("cls");
            printf("\nVERIFICAR OCUPAÇÃO\n");
            mostrarAssentos(qntAssentos, assentos);
            system("pause");
        break;
        case 2:
        	system("cls");
            printf("\nEFETUAR UMA RESERVA\n\n");
            mostrarAssentos(qntAssentos, assentos);
            do{
				printf("DIGITE O NUMERO DO ASSENTO QUE VOCE QUER: ");
            	scanf("%i", &reservaAux.assento);
            	flag = lerValidarAssentos(assentos, reservaAux.assento, qntAssentos);
            	if(flag == 0){
            		printf("\nNUMERO DE ASSENTO INVALIDO!\n");
				}
		}while(flag == 0);
			reservaAux.menor5 = lerValidarIdade();
			reservarAssento(assentos, reservaAux.assento);
			reservaAux.codigo = countCodigoReserva+1;
			reservas[countCodigoReserva] = reservaAux;
			countCodigoReserva++;
			printf("SEU CODIGO DE RESERVA E: %i\n", countCodigoReserva);
            system("pause");
        break;
        case 3:
			system("cls");
            printf("\nCANCELAR UMA RESERVA\n");
          	printf("Digite seu codigo de reserva que voce deseja cancelar: ");
            scanf("%i", &chave);
            flag = validarCodigo(reservas, chave, countCodigoReserva, assentos);
            if(flag != 0){
            	assentos[reservas[chave-1].assento-1] = 'D';
            	reservas[chave-1].marca = '*';
            	printf("\nRESERVA CANCELADA!\n");
			}
			else
			printf("CHAVE INVALIDA!\n");
            system("pause");
        break;
        case 4:
            system("cls");
            printf("\nCONFIRMAR UMA RESERVA\n");
            printf("Digite seu codigo de reserva: ");
            scanf("%i", &chave);
            flag = validarCodigo(reservas, chave, countCodigoReserva, assentos);
            if(flag != 0){
            	assentos[reservas[chave-1].assento-1] = 'C';
            	reservasConfirmadas[countConfirmado] = reservas[chave-1];
            	countConfirmado++;
            	printf("\nASSENTO CONFIRMADO\n");
			}
			else
				printf("CHAVE INVALIDA!\n");
            system("pause");
        break;
        case 5:
        	system("cls");
            printf("\nMOSTRAR SITUACAO DO VOO\n");
            mostarSituacao (assentos, qntAssentos);
            printf("\n VALOR TOTAL: R$%.2f \n", calcularVendas(countConfirmado, reservasConfirmadas, preco));
            system("pause");
        break;
		};
	}while(opcao != 0);
    return 0;
}
void removerPulaLinha (char str[]){
    str[strlen(str)-1]='\0';
}
int menuPrincipal (void){
	int opc = 0;
	printf("*** MENU ***");
	printf("\n1- VERIFICAR A OCUPACAO DE UM VOO\n");
	printf("2- EFETUAR UMA RESERVA\n");
	printf("3- CANCELAR UMA RESERVA\n");
	printf("4- CONFIRMAR UMA RESERVA\n");
	printf("5- MOSTRAR SITUACAO DO VOO\n");
	printf("0- FINALIZAR SESSAO\n");
	opc = lerValidarOpc ();
	return opc;
}
int lerValidarOpc (){
	int opc;
	do{
		scanf("%i", &opc);
		if (opc < 0 || opc > 5)
			printf("Porfavor, digite um numero de 0 a 5: ");
	}while (opc < 0 || opc > 5);
	return opc;
}
int lerValidarQntAssentos (char destino[]){
	int numAssentos;
	 do{
        printf("Digite a quantidade de assentos no aviao do voo para %s: ", destino);
        scanf("%i", &numAssentos);

        if (numAssentos < 90 || numAssentos > 200){
            printf("Quantidade de assentos invalidos!\nPorfavor digite um quantidade de assentos maior igual a 90 ou menor igual a 200\n\n");
        }

    } while (numAssentos < 90 || numAssentos > 200);
    return numAssentos;
}
void lerValidarDestino (char destino[]){
	    do{
		printf("Digite o destino do seu voo: ");
    	fgets(destino, 50, stdin);
    	removerPulaLinha(destino);

    	if (strcmp(destino, "")==0){
    		printf("Favor digite um destino valido!\n");}

	}while(strcmp(destino, "") == 0);

	return ;
}
float lerValidarPreco (){
	float pco;
	do{
        printf("Digite o preco base da passagem: ");
        scanf("%f", &pco);
        if (pco < 1){
            printf("Favor, digite um preço valido\n");
        }
    }while(pco < 1);

    return pco;
}
void inicializarAssentos (char assnt[], int qntAssentos){
	int i;

	for(i=0; i<qntAssentos; i++){
		assnt[i] = 'D';
	}
}
void mostrarAssentos (int qntAssentos, char assnt[]){
	int i, countLinha = 0;

	for(i=0; i<qntAssentos; i++){
		switch(assnt[i]){

			case 'C':
				textcolor(9);
				printf("%03i%c ", i+1, assnt[i]);
			break;
			case 'D':
				textcolor(10);
				printf("%03i%c ", i+1, assnt[i]);
			break;
			case 'R':
				textcolor(4);
				printf("%03i%c ", i+1, assnt[i]);
			}
		countLinha++;
		if(countLinha == 6){
			printf("\n");
			countLinha = 0;
		}
		if(countLinha == 3)
			printf("   ");

	}
	textcolor(15);
	printf("\n");
}
int lerValidarAssentos (char assentos[], int codAssento, int qntAssentos){
	if(codAssento < 1 || qntAssentos < codAssento){
		return 0;
	}
	if(assentos[codAssento-1]!= 'D'){
		return 0;
	}
	return 1;
}
int lerValidarIdade(){
	char simOuNao;
	do{
		printf("O PASSAGEIRO TEM IDADE INFERIOR A 6 ANOS? [S|N]: ");
		setbuf(stdin, NULL);
		scanf("%c", &simOuNao);
		simOuNao = toupper(simOuNao);
		if(simOuNao != 'S' && simOuNao != 'N'){
			printf("PORFAVOR, DIGITE APENAS S OU N!\n");
		}
	}while(simOuNao != 'S' && simOuNao != 'N');
	if(simOuNao == 'S')
		return 1;
	else
		return 0;
}
void reservarAssento(char assentos[], int codAssento){
	assentos[codAssento-1] = 'R';
}
void mostarSituacao (char assentos[], int qntAssentos){
	int countDisponiveis = 0, countReservados = 0, countConfirmados = 0, i;

	for(i=0; i<qntAssentos; i++){
		if(assentos[i] == 'D'){
			countDisponiveis++;
		}
		else if(assentos[i] == 'R'){
			countReservados++;
		}
		else
			countConfirmados++;
	}
	printf("\nASSENTOS DISPONIVEIS: %i", countDisponiveis);
	printf("\nASSENTOS RESERVADOS: %i", countReservados);
	printf("\nASSENTOS CONFIRMADOS: %i", countConfirmados);

}
int validarCodigo (struct tReserva reservas[], int chave, int countCodigo, char assentos[]){

	if(chave <= 0 || chave > countCodigo){
		return 0;
	}
	if(reservas[chave-1].marca == '*'){
		return 0;
	}
	if (assentos[reservas[chave-1].assento -1] == 'C'){
		return 0;
	}
	return 1;
}
float calcularVendas (int countConfirmado, struct tReserva reservas[], float preco){
	int i;
	float valorTotal = 0;
	for(i = 0; i < countConfirmado; i++){
		if(reservas[i].menor5 == 1)
			valorTotal += preco/2;
		else
			valorTotal += preco;
	}
	return valorTotal;
}