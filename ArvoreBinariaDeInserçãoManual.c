#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ESQUERDA -1
#define DIREITA +1

typedef struct no
{
    char conteudo;
    struct no *esquerda, *direita, *pai;

} No; //estrutura da arvore binaria

No* setElemento(No *raiz, char valor)
{
    if(raiz == NULL)
    {
        No *novoa = (No*)malloc(sizeof(No)); //aloca a memoria e cria la
        novoa->conteudo = valor;
        novoa->esquerda = NULL;
        novoa->direita = NULL;
        return novoa; //retorna a nova arvore
    }
    else
    {
        if(valor < raiz->conteudo)
        {
            raiz->esquerda = setElemento(raiz->esquerda, valor);//coloca  a esquerda recussivamente, se for null vai criar uma nova la, se n volta pra ca
        }
        else if (valor > raiz->conteudo)
        {
            raiz->direita = setElemento(raiz->direita, valor);//coloca a direita recussivamente, se for null vai criar uma nova la, se n volta pra ca
        }
        return raiz;
    }
} // iNSERÇÃO DE VALORES


void preFixado(No *raiz)
{
    if(raiz != NULL)
    {

        printf("%c ",raiz->conteudo);

        preFixado(raiz->esquerda);//imprime as lindas a esquerda

        preFixado(raiz->direita);//imprime as lindas a direita

    }


}// Encaminhamento pre-ordem

void central(No *raiz) 
{
    if(raiz != NULL)
    {

        central(raiz->esquerda);

        printf("%c ", raiz->conteudo);

        central(raiz->direita);

    }
}// Encaminhamento em ordem


void mostraArvore(No* a, int b) {
    if (a == NULL) {
        imprimeNo('*', b);
        return;
    }
    mostraArvore(a->direita, b+1);
    imprimeNo(a->conteudo, b);
    mostraArvore(a->esquerda, b+1);
}

// A função auxiliar imprimeNo imprime o caracter
// c precedido de 3b espaços e seguido de uma mudança
// de linha.
void imprimeNo(char c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("   ");
    printf("%c\n", c);
}


void posFixado(No *raiz)
{
    if(raiz != NULL)
    {

        posFixado(raiz->esquerda);

        posFixado(raiz->direita);

        printf("%c ", raiz->conteudo);

    }
}// Encaminhamento pos-ordem

int tamanho(No *raiz)
{
    if(raiz == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);//tem pelo menos 1 nó que é o da raiz aí vai verificando os outros recussivamente
    }
}

int buscar(No *raiz, int chave)
{
    if(raiz == NULL)
    {
        return 0;//tem que retorna algo q n vai estar na arvore
    }
    else
    {
        if(raiz->conteudo == chave) //conteudo é igual ao que tu quer achar
        {
            return 1; // ta na arvore
        }
        else
        {
            if(chave < raiz->conteudo)
            {
                return buscar(raiz->esquerda,chave);//verifica a esquerda
            }
            else if(chave > raiz->conteudo)
            {
                return buscar(raiz->direita,chave);//verifica a direita
            }
        }
    }
    return 0;
}

No* remover(No *raiz, char chave)
{
    if(raiz == NULL)
    {
        return NULL;
    }
    else
    {
        if(raiz->conteudo == chave)  //remover aqui
        {
            if( (raiz->esquerda == NULL) && (raiz->direita == NULL))  // nó folha (sem fillhos)
            {
                free(raiz);
                return NULL;
            }else{
                if((raiz->esquerda != NULL) ^ (raiz->direita != NULL)){ //ume filhe
                    No *auxiliar;
                    if(raiz->esquerda != NULL){     //salva e filhe
                        auxiliar = raiz->esquerda;

                    }else{
                        auxiliar = raiz->direita;
                    }
                    free(raiz);
                    return auxiliar;

                }else { //2 filhos
                     No *auxiliar = raiz->esquerda;
                     while(auxiliar->direita != NULL){
                        auxiliar = auxiliar->direita;
                     }
                     raiz->conteudo = auxiliar->conteudo; //troca de lugar trocando os valores, assim deve ser apagado vai la pro final da arvore

                     auxiliar->conteudo = chave;

                     raiz->esquerda = remover(raiz->esquerda, chave);
                     return raiz;

                }

            }


        } else {
            if(chave < raiz->conteudo) {
                raiz->esquerda = remover(raiz->esquerda,chave);

            } else {
                raiz->direita = remover(raiz->direita,chave);
            }
            return raiz;
        }

    }

}

No* aloqueDireita(No* raiz, char dado, int altura){

    if(raiz == NULL){
        No *novoNo = (No*)malloc(sizeof(No));
        novoNo->conteudo = dado;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if(altura == 0) return raiz;
    
    raiz->direita = aloqueDireita(raiz->direita, dado, altura - 1);
    return raiz;
}

No* aloqueEsquerda(No* raiz, char dado, int altura){

    if(raiz == NULL){
        No *novoNo = (No*)malloc(sizeof(No));
        novoNo->conteudo = dado;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if(altura == 0) return raiz;
    
    raiz->esquerda = aloqueEsquerda(raiz->esquerda, dado, altura - 1);
    return raiz;
}

No* funcao(char string[], int caracterAtual, int lado, No* raiz){

    if(string[caracterAtual] == 0) return raiz;

        if( raiz == NULL ) {
            printf("Criou no\n");
            No *novoNo = (No*)malloc(sizeof(No)); //aloca a memoria e cria la
            novoNo->conteudo = string[caracterAtual];
            novoNo->esquerda = NULL;
            novoNo->direita = NULL;
            raiz = novoNo;
            
            if( string[caracterAtual + 1] == '.' ){
                if(lado == DIREITA) {
                    return raiz;
                
                }

            }
        }

        if (lado == ESQUERDA){
            raiz->esquerda = funcao(string, caracterAtual + 1, ESQUERDA, raiz->esquerda);

        } else {
            raiz->direita = funcao(string, caracterAtual + 1, ESQUERDA, raiz->direita);
        }

        if( string[caracterAtual + 1] == '.' && string[caracterAtual + 2] == '.' ){
            raiz->direita = funcao(string, caracterAtual + 3, DIREITA, raiz->direita);
        }
        
        return raiz;
    }

No* insere(char dado, No* pai){
    No *novoa = (No*)malloc(sizeof(No)); //aloca a memoria e cria la
    novoa->conteudo = dado;
    novoa->pai = pai;
    novoa->esquerda = NULL;
    novoa->direita = NULL;
    return novoa;
}

void insercaoDinamica(char string[], No* raiz){
    No* last;
    int tamanho = strlen(string);
    int lado = ESQUERDA;


    for(int i = 0; i < tamanho; i++){

        if(string[i] == '.'){
            if(lado == ESQUERDA){

                lado = DIREITA;
            
            } else {
                raiz = raiz->pai;
                if(raiz->direita != NULL && raiz->pai != NULL) i--;
            }
            
        } else {
            if(i == 0){
                raiz = insere(string[i], raiz);

            } else {
                
                if(lado == ESQUERDA){
                    raiz->esquerda = insere(string[i], raiz);
                    raiz = raiz->esquerda;

                } else {
                    raiz->direita = insere(string[i], raiz);
                    raiz = raiz->direita;

                }
            }
            lado = ESQUERDA;
        }

    }

    printf("\n\n\n");
    printf("Pre-fixado: ");
    preFixado(raiz);
    printf("\nCentral: ");
    central(raiz);
    printf("\nPos-fixado: ");
    posFixado(raiz);
}

int main(){ //ABD..EH...CFI..J..G.K..

    No *raiz = NULL;
    No *atual;

    //Direita --> 1
    //Esquerda --> -1
    int lado = -1;

    int altura = 0;

    //ABD..EH...CFI..J..G.K..
    char dado[50] = "ABD..EH...CFI..J..G.K..";



    insercaoDinamica(dado, raiz);

    printf("\n\nAlgoritmo finalizado");
    
    return 0;
}
