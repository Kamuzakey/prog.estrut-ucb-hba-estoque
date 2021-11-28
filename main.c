/*------------------ BIBLIOTECAS----------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------ SCTRUCTS-------------------------------*/

typedef struct produto{
  int id;
  char nome[100];
  int qtde;
  int valido;
} produto;

typedef struct funcionario{
  int id;
  char nome[100];
  char CPF[11];
  char matricula[6];
  int valido;
} funcionario;

typedef struct venda{
  produto *produto;
  funcionario *funcionario;
  int qtde;
} venda;

/*-----------DECLARAÇÃO DE FUNÇÕES---------------------------*/

void le_valida_char(char valida[], char tipo[]);
void le_valida_qtde(int *valida, int i);
void armazena_produto(produto produto);
void armazena_fun(funcionario funcionario);
void armazena_vendas(venda venda);

/*-------------------FUNÇÕES---------------------------------*/


/* A função irá imprimir o menu inicial, onde o usuário poderá assim escolher e seguir para um outro menu.*/
void imprime_menu_inicial(){
    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t ESTOQUE HBA TELECOM \n");
    printf("--------------------------------------\n");
    printf("1-CONSULTAR ESTOQUE\n");
    printf("2-RETIRAR PRODUTO\n");
    printf("3-CADASTRAR NOVO PRODUTO\n");
    printf("4-NOVA VENDA\n");
    printf("5-ADICIONAR FUNCIONÁRIO\n");
    printf("6-RETIRAR FUNCIONÁRIO\n");
    printf("7-REALIZAR REESTOQUE\n");
    printf("0-SAIR\n");
    printf("--------------------------------------\n");
}

/*A função recebe a quantidade minima e maxima de opções a serem lidas, recebe, valida e retorna a opção desejada pelo usuário.*/ 
int le_opcao(int min, int max) {
    int opcao;

    do {
        printf("SELECIONE UMA OPÇÃO:\n");
        scanf("%d", &opcao);
        getchar();

        if (opcao < min || opcao > max) {
            printf("ERRO: OPÇÃO INVÁLIDA\n");
        }
    } while ((opcao < min || opcao > max));

    return opcao;
}

/* A função tem como objetivo mostrar a lista de produtos no estoque e suas respectivas quantidades, recebe como parametro as informações e imprime na tela de acordo com a formatação definida*/ 
void consulta_estoque(produto produtos[], int *qtde) {
    int i = 0;
    
	system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t CONSULTA DE ESTOQUE \n");
    printf("--------------------------------------\n");

    if (*qtde == 0) {
        printf("Nenhum produto cadastrado no sistema.\n");
    } else {
        printf(" \tPRODUTO\t\t|\t\tQTDE\t \n");

        for (i = 0; i < *qtde;i++) {
            if (produtos[i].valido == 0) {
                printf("\t%s\t\t|\t\t%d\t \n",produtos[i].nome, produtos[i].qtde);
	        }
        }
    }
	
    printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
	getchar();
	imprime_menu_inicial();
}

/*função de edição, recebe como paramêtro os dados de produto e quantiade a serem retirados do estoque, reatualizando assim o estoque. */
void retira_produto(produto produtos[], int *qtde){
	int i, valida = 0;
  char nome[100];

	system("clear||cls");

  printf("--------------------------------------\n");
  printf("\t\t RETIRAR PRODUTO \n");
  printf("--------------------------------------\n");
  printf("INFORME O NOME DO PRODUTO A SER RETIRADO DO ESTOQUE:\n");
    scanf("%[^\n]",nome);
	fflush(stdin);
	getchar();

    for(i = 0; i < *qtde; i++){
        if(strcmp(nome, produtos[i].nome) == 0){
            valida = 1;
            produtos[i].valido = 1;
            printf("%s RETIRADO COM SUCESSO\n",produtos[i].nome);
            break;
        }
    }

    if (valida == 0) {
        printf("PRODUTO NÃO EXISTE NO ESTOQUE.\n");
    }

	printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
	getchar();
	// imprime_menu_inicial();
} 

/* A função cadastra um novo produto e sua respectiva quantidade ao estoque*/ 
void cadastrar_produto(produto produtos[], int *qtde) {
    int opcao;
	system("clear||cls");

    printf("--------------------------------------\n");
    printf("\t\t CADASTRAR NOVO PRODUTO \n");
    printf("--------------------------------------\n");

    printf("INFORME O NOME DO PRODUTO:\n");
	le_valida_char(produtos[*qtde].nome, "NOME");
	
    do {
        printf("INFORME A QUANTIDADE DESSE PRODUTO:\n");
        scanf("%d", &produtos[*qtde].qtde);
	    getchar();
	
        if (produtos[*qtde].qtde < 0) {
            printf("ERRO:PRODUTO INVALIDO\n");
        }
    } while(produtos[*qtde].qtde < 0);
  
    produtos[*qtde].id = *qtde;
    produtos[*qtde].valido = 0;

    armazena_produto(produtos[*qtde]);
    *qtde += 1;

    printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
	getchar();
	imprime_menu_inicial();
}

/*A função recebe do usuário os dados de venda e relaciona com os produtos em estoque, retornando assim se existe o produto em estoque ou não e caso exista conclui a compra*/
void realizar_venda(venda vendas[], int *qtde_vendas, int *qtde_funcionarios) {
    char matricula[6];
    char nomeprod[100];
    int qtdefuncionario = *qtde_funcionarios;
    int qtdeproduto = *qtde_funcionarios;
    int qtdeprod;
    int i, ind, valida = 0;

	system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t NOVA VENDA \n");
    printf("--------------------------------------\n");

    do {
        printf("INFORME A MATRÍCULA DO FUNCIONÁRIO:\n");
        le_valida_char(matricula, "MATRICULA");

        for (i = 0; i < qtdefuncionario; i++) {
		    if (strcmp(vendas[i].funcionario->matricula, matricula) == 0) {
       	        valida = 1;
                break;
            }
        }

        if (valida == 0) {
            printf("ERRO: MATRÍCULA INVÁLIDA.\n");
            getchar();
        }
    } while(valida == 0);

    valida = 0;

    do {
        printf("INFORME O NOME DO PRODUTO:\n");
        le_valida_char(nomeprod, "NOME");

        for (i = 0; i < qtdeproduto ; i++){
            if (strcmp(vendas[i].produto->nome, nomeprod) == 0) {
                valida = 1;
                ind = i;
								
                break;
            }
        }

        if (valida == 0) {
            printf("ERRO: PRODUTO INEXISTENTE\n.");
            getchar();
        }
    } while(valida == 0);

    valida = 0;

    do {
        printf("INFORME A QUANTIDADE DO PRODUTO DESEJADO:\n");
        le_valida_qtde(&qtdeprod, 1);

        if (vendas[ind].produto->qtde > qtdeprod) {
            vendas[ind].produto->qtde -= qtdeprod;
            valida = 1;
            break;
        } else {
            printf("O PRODUTO POSSUI APENAS %d\n\n", vendas[ind].produto->qtde);
        }
    } while(valida == 0);

    printf("\nPRODUTO COMPRADO COM SUCESSO!\n");
    printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
    getchar();
	// imprime_menu_inicial();
}

/* A função recebe e adiciona ao sistema um novo funcionário*/
void adiciona_funcionario(funcionario funcionarios[], int *qtde) {
	int i;
  char matricula[6];
    system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t CADASTRAR NOVO FUNCIONÁRIO \n");
    printf("--------------------------------------\n");

    printf("INFORME O NOME DO FUNCIONÁRIO:\n");
    le_valida_char(funcionarios[*qtde].nome, "NOME");

    printf("INFORME O CPF DESSE FUNCIONARIO:\n");
    le_valida_char(funcionarios[*qtde].CPF, "CPF");

    printf("INFORME A MATRICULA DESSE FUNCIONÁRIO:\n");
		le_valida_char(funcionarios[*qtde].matricula, "MATRICULA");
    
    funcionarios[*qtde].valido = 0;
    funcionarios[*qtde].id = *qtde;

    armazena_fun(funcionarios[*qtde]);	
    *qtde += 1;

    printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
	getchar();
	imprime_menu_inicial();
}

/* A função recebe e retira do sistema um antigo funcionário*/
void retira_funcionario(funcionario funcionarios[], int *qtde) {
    char nome[100];
    int i, valida = 0;

	system("clear||cls");
    printf("--------------------------------------\n");
    printf("\t\t RETIRAR FUNCIONARIO \n");
    printf("--------------------------------------\n");
    printf("INFORME O NOME DO FUNCIONARIO A SER RETIRADO:\n");
    scanf("%[^\n]",nome);

    for (i = 0; i < *qtde; i++) {
        if (strcmp(nome, funcionarios[i].nome) == 0) {
            valida = 1;
            funcionarios[i].valido = 1;
            
            printf("%s RETIRADO COM SUCESSO\n", funcionarios[i].nome);
			getchar();
            break;
		}
    }

    if (valida == 0) {
        printf("FUNCIONARIO NÃO EXISTE.\n");
		getchar();
    }

	printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
	getchar();
	// imprime_menu_inicial();
}

/*A função percorre por todos os produtos cadastrados no estoque recebendo do usuário as respectivas novas quantidades */
void realiza_reestoque(produto produtos[], int *qtde){
    int i, qtdeprod;

	system("clear||cls");

    printf("--------------------------------------\n");
    printf("\t\t REALIZAR REESTOQUE \n");
    printf("--------------------------------------\n");
    printf("INFORME AS NOVAS QUANTIDADES A SEREM ADICIONADAS AO ESTOQUE:\n");

    for(i = 0; i < *qtde; i++){
        if(produtos[i].valido == 0){
            printf("PRODUTO: %s QTDE: ", produtos[i].nome);
            le_valida_qtde(&qtdeprod, 2);

            produtos[i].qtde = produtos[i].qtde + qtdeprod;
            printf("\n");
        }
    }

    printf("--------------------------------------\n");
	printf("\nPRESSIONE ENTER PARA VOLTAR AO MENU\n");
	getchar();
	// imprime_menu_inicial();
}

/* A função recebe uma string e valida se a mesma está vazia ou não.*/
void le_valida_char(char valida[], char tipo[]){
    do{
        scanf("%[^\n]",valida);
        getchar();

        if(strcmp(valida,"") == 0){
            printf("ERRO:%s INVÁLIDO.",tipo);
        }
    }while(strcmp(valida,"") == 0);
}

/*A função recebe um inteiro e checa se ele é valido ou não */
void le_valida_qtde(int *valida, int i){
  if(i == 1){
    do{
      scanf("%d",valida);
      getchar();
      if(*valida <= 0){
        printf("ERRO:QUANTIDADE INVÁLIDA.");
      }
    }while(*valida <= 0);
  }

  if(i == 2){
    do{
      scanf("%d",valida);
      getchar();
      if(*valida < 0){
        printf("ERRO:QUANTIDADE INVÁLIDA.");
      }
    }while(*valida < 0);
  }
}

/* Essa função armazena os dados no arquivo "estoque_prod.txt"*/
void armazena_produto(produto produto) {
	FILE *arq = fopen("estoque_prod.txt", "a+");

	fprintf(arq, "%d | %s | %d | valido = %d\n", produto.id, produto.nome, produto.qtde, produto.valido);

	fclose(arq);
}

/* Essa função armazena os dados no arquivo "funcionario.txt"*/
void armazena_fun(funcionario funcionario) {
	FILE *arq = fopen("funcionario.txt", "a+");
	
	fprintf(arq, "%d | %s | %s | %s | valido = %d\n", funcionario.id, funcionario.nome, funcionario.CPF, funcionario.matricula, funcionario.valido);

	fclose(arq);
}

void armazena_vendas(venda venda) {
	FILE *arq = fopen("venda.txt", "a+");
	
	fprintf(arq, "%d | %d\n", venda.produto->id, venda.funcionario->id);

	fclose(arq);
}
/*A função carrega dados do arquivo "funcionario.txt"*/
void carrega_funcio(funcionario funcionarios[], int *qtde_funcionarios) {
    FILE *arq = fopen("funcionario.txt", "r");

    while (!feof(arq)) {
        fscanf(arq, "%d | %[^ |] | %[^ |] | %[^ |] | valido = %d\n", 
        &funcionarios[*qtde_funcionarios].id, funcionarios[*qtde_funcionarios].nome, funcionarios[*qtde_funcionarios].CPF, funcionarios[*qtde_funcionarios].matricula, 
        &funcionarios[*qtde_funcionarios].valido);

        *qtde_funcionarios += 1;
    }

    fclose(arq);
}
/*A função carrega dados do arquivo "estoque.txt"*/
void carrega_produtos(produto produtos[], int *qtde_produtos) {
    FILE *arq = fopen("estoque_prod.txt", "r");

    while (!feof(arq)) {
        fscanf(arq, "%d | %[^ |] | %d | valido = %d\n", 
        &produtos[*qtde_produtos].id, produtos[*qtde_produtos].nome,
        &produtos[*qtde_produtos].qtde, &produtos[*qtde_produtos].valido);

        *qtde_produtos += 1;
    }

    fclose(arq);
}
/*A função busca e confere se o funcionario existe*/
funcionario *busca_funcio(funcionario funcionarios[], int qtde_funcionarios, int id_funcionario) {
    int i;

    for (i = 0; i < qtde_funcionarios; i++) {
        if (funcionarios[i].id == id_funcionario) {
            return &funcionarios[i];
        }
    }

    return NULL;
}
/*A função busca e confere se o produto existe*/
produto *busca_produto(produto produtos[], int qtde_produtos, int id_produto) {
    int i;

    for (i = 0; i < qtde_produtos; i++) {
        if (produtos[i].id == id_produto) {
            return &produtos[i];
        }
    }

    return NULL;
}
/*A função carrega dados do arquivo "vendas.txt*/
void carrega_vendas(venda vendas[], int *qtde_vendas, funcionario funcionarios[], int qtde_funcionarios, produto produtos[], int qtde_produtos) {
    FILE *arq = fopen("venda.txt", "r");
    int id_produto, id_funcionario;

    while (!feof(arq)) {
        fscanf(arq, "%d | %d\n", &id_produto, &id_funcionario);

        vendas[*qtde_vendas].produto = busca_produto(produtos, qtde_produtos, id_produto);
        vendas[*qtde_vendas].funcionario = busca_funcio(funcionarios, qtde_funcionarios, id_funcionario);

        *qtde_vendas += 1;
    }

    fclose(arq);
}

/*------------------MAIN----------------------------*/

int main() {
	FILE *estoque_prod, *matricula_funcionario;
    int opcao, i;
  
    produto produtos[200];
    int qtde_produtos = 0;

    funcionario funcionarios[200];
    int qtde_funcionarios = 0;

    venda vendas[200];
    int qtde_vendas = 0;

    carrega_funcio(funcionarios, &qtde_funcionarios);
    carrega_produtos(produtos, &qtde_produtos);
    carrega_vendas(vendas, &qtde_vendas, funcionarios, qtde_funcionarios, produtos, qtde_produtos);

    
	do {
	    imprime_menu_inicial();
	    opcao = le_opcao(0, 7);
	
	    switch (opcao){
	    case 1:
            consulta_estoque(produtos, &qtde_produtos);
            break;
	    case 2:
            retira_produto(produtos, &qtde_produtos);
            break;
	    case 3:
	       cadastrar_produto(produtos, &qtde_produtos);
            break;
        case 4:
            realizar_venda(vendas, &qtde_produtos, &qtde_funcionarios);  
            break;  
        case 5:
            adiciona_funcionario(funcionarios, &qtde_funcionarios);
            break;
        case 6:
            retira_funcionario(funcionarios, &qtde_funcionarios);
            break;    
        case 7:
            realiza_reestoque(produtos, &qtde_produtos);
            break;   
        case 0:
	    	printf("Encerrando programa!\n");
            break;   
        default:
        break;
	    }
	} while(opcao != 0);

    estoque_prod = fopen("estoque_prod.txt", "w+");
    matricula_funcionario = fopen("funcionario.txt", "w+");

    // Salva os produtos no estoque_prod.txt
    for (i = 0; i < qtde_produtos; i++)
        armazena_produto(produtos[i]);

    // Salva os funcionarios no funcionario.txt
    for (i = 0; i < qtde_funcionarios; i++)
        armazena_fun(funcionarios[i]);

    // Salva os funcionarios no vendas.txt
    for (i = 0; i < qtde_vendas; i++)
        armazena_vendas(vendas[i]);

    fclose(estoque_prod);
    fclose(matricula_funcionario);
    

    return 0;
} 