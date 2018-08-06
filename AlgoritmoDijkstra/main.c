#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

//Estrutura Aresta que contem peso, vertice de Origem e Destino
typedef struct {
    int Vori;
    int Vdest;
    int peso;
}Aresta;

//Estrutura ArestaRelaxada que contem aresta e uma variavel para informar se a aresta esta aberta ou fechada
typedef struct {
	Aresta arestaCalc;
	int aberta;
}ArestaRelaxada;

//Função para alocar a matriz dos pesos de acordo com o número de vértices
Aresta** alocaMatrizAresta(int numVertices){
	Aresta **Matriz = (Aresta**) malloc(sizeof(Aresta*)*numVertices);
	int i;
	for(i=0; i < numVertices; i++){
		Matriz[i] = (Aresta*) malloc(sizeof(Aresta)*numVertices);
	}
	return Matriz;
}

//Função que contém as instruções
int instrucoes(){
	printf("%c%c%c",201,205,205);
	int i;
		for(i = 0; i < 44; i++){
			printf("%c",205);
		}
		printf("%c",187);
		puts("");
		printf("%c\t\t  Instrucoes\t\t       %c\n",186,186);
		for ( i = 0; i < 3; i ++){
			printf("%c\t\t\t\t\t       %c\n",186,186);
		}
		printf("%c\t    Algoritmo de Djikstra.\t       %c\n",186,186);
		printf("%c\t\t\t\t\t       %c\n",186,186);
		printf("%c   Na pasta do projeto existe um arquivo      %c\n",186,186);
		printf("%c chamado entrada.txt, esse arquivo e a        %c\n",186,186);
		printf("%c entrada da matriz dos pesos das arestas      %c\n",186,186);
		printf("%c do seu Grafo, preencha-o com os respectivos  %c\n",186,186);
		printf("%c pesos, lembrando de dar o peso de -1 para    %c\n",186,186);
		printf("%c os vertices que nao sao adjacentes e separar %c\n",186,186);
		printf("%c todos os pesos com algum 'ESPAÇO', isso é    %c\n",186,186);
		printf("%c crucial para o funcionamento do programa.    %c\n",186,186);
		printf("%c   A mesma pasta dispoe do arquivo            %c\n",186,186);
		printf("%c exemplo.txt, cujo desmonstra como deve ser   %c\n",186,186);
		printf("%c essa entrada.                                %c\n",186,186);
		printf("%c   Ao ser executado, sera pedido o vertice    %c\n",186,186);
		printf("%c inicial do seu Grafo.                        %c\n",186,186);
		printf("%c   O programa retornara a matriz dos pesos e  %c\n",186,186);
		printf("%c o peso de um caminho de peso minimo ligando  %c\n",186,186);
		printf("%c vertice de origem a cada vertice do Grafo.   %c\n",186,186);
		printf("%c   Os vertices serao denominados 1,2,3...     %c\n",186,186);
		printf("%c para n Vertices.                             %c\n",186,186);
		printf("%c   Para calcular outro caminho no mesmo Grafo %c\n",186,186);
		printf("%c basta retornar ao menu principal e alterar o %c\n",186,186);
		printf("%c vertice de origem.                           %c\n",186,186);
		printf("%c\t\t\t\t\t       %c\n",186,186);
		printf("%c\t\t\t\t\t       %c\n",186,186);
		printf("%c Digite qualquer tecla para voltar ao Menu.   %c\n",186,186);
		printf("%c\t\t\t\t\t       %c\n",186,186);
		printf("%c\t\t\t\t\t       %c\n",186,186);
		printf("%c%c%c",200,205,205);
		for(i = 0; i < 44; i++){
			printf("%c",205);
		}
		printf("%c\n",188);
		system("pause");
		system("cls");
}


void preencheMatriz(Aresta** Grafo, int numVertices){ 
   	int i, j;
   	FILE * file;
   	file = fopen("entrada.txt","r");// Abrindo o arquivo
   	if(file == NULL){//Se não for possivel ler o arquivo retorna essa mensagem fecha o programa
   		puts("Nao foi possivel ler o arquivo entrada.txt.");
   		exit(1);
	}
	for(i = 0; i < numVertices; i++){//Se for possivel, guarda os valores do arquivo em uma matriz
		for(j = 0; j < numVertices; j++){
			fscanf(file,"%d",&(Grafo[i][j].peso));
		}
	}
   	fclose(file);//Fecha o Arquivo
};

//Função para desenhar a matriz dos pesos
void DesenhaGrafo(Aresta** gr, int n){
	puts("");
	puts("\tMATRIZ DOS PESOS DAS ARESTAS");
	puts("");
	int a;
	for(a = 0; a<=n;a++){
		if(a == 0){
			printf("%c_____%c",179,179);
		}
		else{
			printf("_v%02d_%c",gr[0][a-1].Vdest,179);
		}
	}
	int b;
	for(b = 0; b<n;b++){
		puts("");
		for(a = 0; a<=n;a++){
			if(a == 0){
				printf("%c_v%02d_%c",179,gr[b][a].Vori,179);
			}
			else{
				if(gr[b][a-1].peso == (INT_MAX/2)){
					printf("__*__%c",179);
				}
				else{
				printf("__%02d_%c",gr[b][a-1].peso,179);
				}
			}
		}
	}
	puts("");
	puts("");
}

//função que preenche uma matriz padrão com pesos infinitos em todas as arestas
void preencheMatrizPadrao(Aresta** Grafo, int n){
	int i;
	int j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j ++){
			if(j==i){
				Grafo[i][j].peso = 0;
				Grafo[i][j].Vori = i+1;
				Grafo[i][j].Vdest = j+1;
			}
			else{
				Grafo[i][j].peso = INT_MAX/2; // Divide por 2 para não estourar a mémoria quando formos calcular
				Grafo[i][j].Vori = i+1;
				Grafo[i][j].Vdest = j+1;
			}
		}
	}
}
//Função que preenche o vetor com pesos dos caminhos como infinito
void colocaInfinito(ArestaRelaxada* Caminhos, int numVertices){
	int i;
	for(i = 0; i < numVertices; i++){
		Caminhos[i].arestaCalc.peso = INT_MAX/2; // Divide por 2 para não estourar a mémoria quando formos calcular
		Caminhos[i].arestaCalc.Vori = i+1;
		Caminhos[i].aberta = 1;
	}
}

//Função que tranforma os pesos -1 dos vertices não adjacentes em infinito
void ProcessaMatriz(Aresta** Grafo, int numVertices){
	int i, j;
	for(i = 0; i < numVertices; i++){
		for(j = 0; j < numVertices; j++){
			if(Grafo[i][j].peso == (-1)){
				Grafo[i][j].peso = INT_MAX/2;
			}
		}
	}
}

//Função que calcula os caminhos de peso minimo
ArestaRelaxada* calculaCaminhos(Aresta** Grafo, ArestaRelaxada* Caminhos, Aresta v,int pesoAtual, int cont, int numVertices){
	int k;
	
	if(cont == numVertices){//Verifica se todos os vertices já foram relaxados
		return Caminhos;//Se sim, retorna os caminhos
	}
	
	for(k =0; k < numVertices ; k++){//Rotulando a aresta recebida
			if(Caminhos[k].arestaCalc.Vori == v.Vori ){ 
			Caminhos[k].arestaCalc.peso = v.peso;
			Caminhos[k].aberta = 0;
		}
	}
	
	int i;
	for(i = 0; v.Vori != Grafo[i][0].Vori ; i ++){ // iteração para achar a linha correspondentes aos pesos da aresta recebida
	}
	
	int j ;
	for(j = 0; j < numVertices; j++){
		// Verifica se a aresta ainda está aberta e se o peso da aresta adjacente mais o peso do vertice atual é menor do que o caminho antigo
		if(Caminhos[j].aberta == 1 && Caminhos[j].arestaCalc.peso > (Grafo[i][j].peso + pesoAtual)){
			Caminhos[j].arestaCalc.peso = Grafo[i][j].peso + pesoAtual;
		}
	}
	
	int menorVertice = INT_MAX/2;
	int l;
	for(l = 0; l < numVertices ; l++){
		//Verifica dentre os vertices abertos qual tem o menor peso 			
		if(Caminhos[l].aberta == 1 && Caminhos[l].arestaCalc.peso < menorVertice){
			menorVertice = Caminhos[l].arestaCalc.peso;
			v.peso = Caminhos[l].arestaCalc.peso; // Salva o vertice com menor peso atual 
			v.Vori = Grafo[i][l].Vdest;
		}
	}
	
	pesoAtual = v.peso;
	cont++; // Controla o número de vezes que a função foi executada e fechou um vertice
	//Começa recursividade passando o atual
	calculaCaminhos(Grafo,Caminhos,v,pesoAtual,cont,numVertices);
}

//Imprime o resultado
void imprimeCaminhos(ArestaRelaxada* Caminhos, int numVertices, Aresta arestaInicial){
	int i;
	printf("\nCaminhos de peso minino partindo de v%d\n",arestaInicial.Vori);
	for(i = 0; i < numVertices; i++){
		printf("\n\tCaminho minimo para v%02d e: %d",Caminhos[i].arestaCalc.Vori, Caminhos[i].arestaCalc.peso);
	}
	puts("");
}
//Libera o espaço na memória alocado pela matriz
void liberarMatriz(Aresta** Matriz, int numVertices){
	int i;
	for(i=0; i<numVertices; i++){
		free(Matriz[i]);
	}
	free(Matriz);
}
//Função para escolher a aresta inicial
Aresta escolheAresta(int numVertices, Aresta** Grafo){
	int i, arestaInicial = 0;
	while((arestaInicial < 1)||(arestaInicial > numVertices)){
		printf("Escolha um Vertice Inicial entre:"); 
		for(i = 0; i < numVertices; i++){
			printf(" %d",i+1);
		}
		puts("");
		scanf("%d", &arestaInicial);
		for(i = 0; i < numVertices; i++){
			if(Grafo[i][i].Vori == arestaInicial){
				return Grafo[i][i];
			}
		}
		puts("Nao foi possivel escolher a aresta inicial. Tente Novamente!");
		puts("");
	}
}

//Função para contar o número vertices do Grafo;
int contaVertices(){
	FILE *file;
	file = fopen("entrada.txt","r");
	int i,j,k,nVertice = 0;
	for(i = -1; k != (-1); i ++){
		k = fscanf(file,"%d",&j);
	}
	nVertice = sqrt(i);
	fclose(file);	
	return nVertice;
}

//Função Menu
int Menu(){
	while(1){
		system("cls");
		int i;
		int opcao;
		puts("");
		printf("%c%c%c",201,205,205);
		for(i = 0; i < 42; i++){
			printf("%c",205);
		}
		printf("%c",187);
		puts("");
		printf("%c\t Digite a opcao desejada.\t     %c\n",186,186);
		for ( i = 0; i < 3; i ++){
			printf("%c\t\t\t\t\t     %c\n",186,186);
		}
		printf("%c\t 1-> Algoritmo de Djikstra.\t     %c\n",186,186);
		printf("%c\t\t\t\t\t     %c\n",186,186);
		printf("%c\t 2-> Instrucoes.\t\t     %c\n",186,186);
		printf("%c\t\t\t\t\t     %c\n",186,186);
		printf("%c\t 3-> Encerrar.\t\t\t     %c\n",186,186);
		printf("%c\t\t\t\t\t     %c\n",186,186);
		printf("%c%c%c",200,205,205);
		for(i = 0; i < 42; i++){
			printf("%c",205);
		}
		printf("%c\n",188);
		printf("\t Opcao: ",186);
		scanf("%d",&opcao);
		
		if(opcao==1){
			
			system("cls");
			puts("");
			puts("\t 1 - ALGORITMO DE DIJKSTRA.");
			puts("");
			int numVertices = 0;			
			Aresta arestaInicial; // Cria a aresta Inicial
			puts("Digite o numero de vertices:");
			numVertices = contaVertices(); // Chama a função que calcula o numero de vertices.
			Aresta** pGrafo = (Aresta**)alocaMatrizAresta(numVertices); // Chama a função de alocação de mémoria para a matriz dos pesos
			ArestaRelaxada* pCaminhos = malloc(sizeof(ArestaRelaxada)*numVertices); // Chama a função de alocação para os caminhos
			system("cls");
			preencheMatrizPadrao(pGrafo,numVertices); //Chama a função para preencher a matriz padrão dos pesos '0' e Infinito
			preencheMatriz(pGrafo, numVertices); //Chama a função que  preenche a Matriz de acordo com os dados do arquivo entrada.txt
			ProcessaMatriz(pGrafo,numVertices); // Chama a função que transforma os pesos dos vertices não adjacentes em infinito.
			DesenhaGrafo(pGrafo,numVertices); // Chama a função que desenha a Matriz dos
			colocaInfinito(pCaminhos, numVertices); // Chama a função que coloca Infinito nos pesos dos resultados
			arestaInicial = escolheAresta(numVertices, pGrafo); // Chama a função que escolhe a aresta Inicial
			calculaCaminhos(pGrafo,pCaminhos,arestaInicial,0,0,numVertices); // Chama a função que calculas os Caminhos a partir de um vertice
    		imprimeCaminhos(pCaminhos, numVertices, arestaInicial); // Chama a função que imprime o resultado
    		puts("\nDigite Qualquer tecla para voltar ao Menu principal.\n");
    		system("pause");
			liberarMatriz(pGrafo, numVertices); //chama a função libera o espaço alocado na memória pela matriz.
			free(pCaminhos); // Libera o espaço alocado na mémoria pelos caminhos.
    		system("cls");
		}
		if(opcao == 2){
			system("cls");
			instrucoes();
		}
		if(opcao==3){
			exit(0);
		}
	}
}

int main() {
	
	Menu();

}
