#ifndef CRUDCLIENTE_H_INCLUDED
#define CRUDCLIENTE_H_INCLUDED
#include <string.h>
typedef struct Cliente{
		int codigo;
		char nome[50];
		char empresa[50];
		char departamento[50];
		char tel[12];
		char email[50];
}Cliente;

typedef struct No {
	struct Cliente cliente;
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
	No *fim;
	int tam;
}Lista;

void iniciar (Lista *lista){
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->tam =  0;
}

void cadastrar(Lista *lista){
	system ("cls");
	printf ("\n Cadastro de Cliente\n");
	No *novo = (No*)malloc(sizeof(No));

	printf ("\n Digite o id do cliente: ");
	scanf (" %d",&novo->cliente.codigo);
	printf (" Digite o nome do cliente: ");
	scanf (" %[^\n]s",&novo->cliente.nome);
	printf (" Digite a empresa do Cliente: ");
	scanf (" %[^\n]s",&novo->cliente.empresa);
	printf (" Digite o departamento da empresa: ");
	scanf (" %[^\n]s",&novo->cliente.departamento);
	printf (" Digite o telefone do Cliente: ");
	scanf (" %[^\n]s",&novo->cliente.tel);
	printf (" Digite o email do Cliente: ");
	scanf (" %[^\n]s",&novo->cliente.email);

	novo->proximo = NULL;

	if(lista->inicio == NULL){
		lista->inicio = novo;
		lista->fim = novo;
	}else{
		lista->fim->proximo = novo;//encadeamento da lista
		lista->fim = novo; // mudança do fim para o novo elemento
	}
	lista->tam++;
}

void cadastrarBackUp(Lista *lista, int codigo, char* nome, char* empresa, char* setor, char* tel, char* email){
	printf(" entrou no BackUp");
	getchar();
	No *novo = (No*)malloc(sizeof(No));

	novo->cliente.codigo = codigo;
	printf(" Passou codigo");
	getchar();
	strcpy(novo->cliente.nome,nome);
	printf(" Passou nome");
	getchar();
	strcpy(novo->cliente.empresa,empresa);
	printf(" Passou empresa");
	getchar();
	strcpy(novo->cliente.departamento,setor);
	printf(" Passou departamento");
	getchar();
	strcpy(novo->cliente.tel,tel);
	printf(" Passou tel");
	getchar();
	strcpy(novo->cliente.email,email);
	printf(" Passou email");
	getchar();

	novo->proximo = NULL;
	printf(" Passou novo->proximo = null");
	getchar();
	printf("[%d]",lista->inicio);

	if(lista->inicio == NULL){
		printf("\n Entrou IF");
		getchar();
		lista->inicio = novo;
		lista->fim = novo;
	}else{
		printf("\n Entrou ELSE");
		getchar();
		lista->fim->proximo = novo;
		lista->fim = novo;
	}
	printf (" SAIU IF ELSE\n");
	getchar();
	lista->tam++;
}


void imprimir(Lista *lista){
	system ("cls");
	printf ("\n Lista de Clientes [%d]\n",lista->tam);

	No *inicio = lista->inicio;

	while (inicio!=NULL){
		printf ("\n ID\t\t %d",inicio->cliente.codigo);
		printf ("\n Nome\t\t %s",inicio->cliente.nome);
		printf ("\n Empresa\t %s",inicio->cliente.empresa);
		printf ("\n Departamento\t %s",inicio->cliente.departamento);
		printf ("\n Telefone\t %s",inicio->cliente.tel);
		printf ("\n Email\t\t %s",inicio->cliente.email);
		printf ("\n ------------------------------------------");
		inicio = inicio->proximo;
	}
	printf ("\n");
}

void editar (Lista *lista, int id){
	system ("cls");
	printf ("\n Edição de Cliente - ID [%d]\n",id);

	No *inicio = lista->inicio;

	while (inicio->cliente.codigo != id){
		inicio = inicio->proximo;
	}

	printf (" Digite o nome do cliente: ");
	scanf (" %[^\n]s",&inicio->cliente.nome);
	printf (" Digite a empresa do Cliente: ");
	scanf (" %[^\n]s",&inicio->cliente.empresa);
	printf (" Digite o departamento da empresa: ");
	scanf (" %[^\n]s",&inicio->cliente.departamento);
	printf (" Digite o telefone do Cliente: ");
	scanf (" %[^\n]s",&inicio->cliente.tel);
	printf (" Digite o email do Cliente: ");
	scanf (" %[^\n]s",&inicio->cliente.email);
}

void excluir (Lista *lista, int id){
	system ("cls");
	No *anterior, *atual;

	printf ("\n Exclusão de Cliente - ID [%d]\n",id);

	if(lista->inicio == NULL){
		printf ("\n Lista Vazia");
	}else{
		anterior = lista->inicio;
		atual = lista->inicio;
		while(atual != NULL){//encontrei o elemento
			if (atual->cliente.codigo == id){//elemento é o primeiro da lista  id){
				if(atual == lista->inicio){
					lista->inicio = lista->inicio->proximo;
					free(atual);
					lista->tam--;
					break;
				}else{                   //elemento é o ultimo da lista
					if(atual == lista->fim){
						lista->fim = anterior;
					}
					//refazendo encadeamento
					anterior->proximo = atual->proximo;
					free(atual);
					lista->tam--;
					break;
				}
			}else{//caso não encontre a posição, caminhar os ponteiros pela lista até achar o IDvalor
				anterior = atual;
				atual = atual->proximo;
			}
		}
	}
}

void salvar (Lista *lista){
	No *inicio = lista->inicio;

	FILE *file = fopen ("./clientes.json","a");
	FILE *file2 = fopen ("./clientes.txt","a");

	if(!file && !file2){
		printf ("\n Não foi possível salvar as informações por algum motivo =( \n Erro <00x001>\n\n");

	}else{
		while (inicio!=NULL){
			fprintf(file,"   {\n");
			fprintf(file,"      \"id\":");
			fprintf(file,"%d,\n",inicio->cliente.codigo);
			fprintf(file,"      \"Nome\":");
			fprintf(file,"\"%s\",\n",inicio->cliente.nome);
			fprintf(file,"      \"Empresa\":");
			fprintf(file,"\"%s\",\n",inicio->cliente.empresa);
			fprintf(file,"      \"departamento\":");
			fprintf(file,"\"%s\",\n",inicio->cliente.departamento);
			fprintf(file,"      \"Telefone\":");
			fprintf(file,"\"%s\",\n",inicio->cliente.tel);
			fprintf(file,"      \"Email\":");
			fprintf(file,"\"%s\"\n",inicio->cliente.email);
			fprintf(file,"   },\n");
			//-----------------------------------------------
			fprintf(file2,"%d\n",inicio->cliente.codigo);
			fprintf(file2,"%s\n",inicio->cliente.nome);
			fprintf(file2,"%s\n",inicio->cliente.empresa);
			fprintf(file2,"%s\n",inicio->cliente.departamento);
			fprintf(file2,"%s\n",inicio->cliente.tel);
			fprintf(file2,"%s\n",inicio->cliente.email);
			inicio = inicio->proximo;
		}
	}
	fclose(file);
	fclose(file2);
}

void backup(Lista* lista){
	int codigo;
	char nome[50];
	char empresa[50];
	char departamento[50];
	char tel[50];
	char email[50];

	FILE *arquivo;
    arquivo = fopen("./clientes.txt","r");

    if (arquivo){
        do{

            fscanf(arquivo,"%d",&codigo);
            fscanf(arquivo,"%s",&nome);
            fscanf(arquivo,"%s",&empresa);
            fscanf(arquivo,"%s",&departamento);
            fscanf(arquivo,"%s",&tel);
            fscanf(arquivo,"%s",&email);
            printf ("\n %d\n",codigo);
			printf (" %s\n",nome);
			printf (" %s\n",empresa);
			printf (" %s\n",departamento);
			printf (" %s\n",tel);
			printf (" %s\n",email);

			getchar();

			cadastrarBackUp(&lista, codigo,nome,empresa,departamento,tel,email);
        }while(!feof(arquivo));

    }
    fclose(arquivo);
}
#endif
