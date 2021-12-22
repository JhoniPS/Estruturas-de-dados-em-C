#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
    char conteudo;
    struct no *esquerda, *direita;
    short altura;

} No; //estrutura da arvore binaria

short maior(short a, short b){
    return (a>b)?a:b;
}

short alturaNo(No *no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

short fatorDeBalanceamento(No *no){
    if(no)
        return(alturaNo(no->esquerda) - alturaNo(no->direita));
    else
        return 0;
}

No* rotacaoEsquerda(No *r){ //roda pra esqurda 
    No *y, *f;

    y = r->direita;
    f = y->esquerda;

    y->esquerda = r;
    r->direita = f;

    r->altura = maior( alturaNo(r->esquerda) , alturaNo(r->direita) ) +1;
    y->altura = maior( alturaNo(y->esquerda) , alturaNo(y->direita) ) +1;

    return y;

}

No* rotacaoDireita(No *r){ //roda pra direita 
    No *y,*f;
    
    y = r->esquerda;
    f = y->direita;

    y->direita = r;
    r->esquerda = f;

    r->altura = maior( alturaNo(r->esquerda) , alturaNo(r->direita) ) +1;
    y->altura = maior( alturaNo(y->esquerda) , alturaNo(y->direita) ) +1;

    return y;

}

No* rotacaoDireitaEsquerda(No *r){
    r->direita = rotacaoDireita(r->direita);
    return rotacaoEsquerda(r);
}

No* rotacaoEsquerdaDireita(No *r){
    r->esquerda = rotacaoEsquerda(r->esquerda);
    return rotacaoDireita(r);

}


No* balancear(No *raiz){
    short fb = fatorDeBalanceamento(raiz);
    
    if( (fb < -1) && (fatorDeBalanceamento(raiz->direita) <= 0) )
        raiz = rotacaoEsquerda(raiz);

    else if( (fb > 1) && (fatorDeBalanceamento(raiz->esquerda)>= 0))
        raiz = rotacaoDireita(raiz);

    else if( (fb > 1) && (fatorDeBalanceamento(raiz->esquerda) < 0))
        raiz = rotacaoEsquerdaDireita(raiz);

    else if( (fb < -1) && (fatorDeBalanceamento(raiz->direita) > 0))
        raiz = rotacaoDireitaEsquerda(raiz);

    return raiz;

}
No* novoNo(char valor){
  No *novoa = (No*)malloc(sizeof(No));//aloca a memoria e cria la
        if(novoa){
        novoa->conteudo = valor;
        novoa->esquerda = NULL;
        novoa->direita = NULL;
        novoa->altura = 0;
        }
        else
          printf("cade a mamata");
        return novoa; //retorna a nova arvor

}


No* setElemento(No *raiz,char valor)
{
    if(raiz == NULL)
    {
        return novoNo(valor); //retorna a nova arvore
    }
    else
    {
        if(valor < raiz->conteudo)
        {
            raiz->esquerda = setElemento(raiz->esquerda,valor);//coloca  a esquerda recussivamente, se for null vai criar uma nova la, se n volta pra ca
        }
        else if (valor > raiz->conteudo)
        {
            raiz->direita = setElemento(raiz->direita,valor);//coloca a direita recussivamente, se for null vai criar uma nova la, se n volta pra ca
        }
       
    }
      raiz->altura = maior( alturaNo(raiz->esquerda), alturaNo(raiz->direita))+1; //calcula a altura

        raiz = balancear(raiz);//balancea ou n

        return raiz;
   
}

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

void posFixado(No *raiz)
{
    if(raiz != NULL)
    {

        posFixado(raiz->esquerda);

        posFixado(raiz->direita);

        printf("%c ", raiz->conteudo);

    }
}// Encaminhamento pos-ord


void imprimir(No *raiz)
{
    if(raiz != NULL)
    {
        imprimir(raiz->esquerda);//imprime as lindas a esquerda
        printf("%c\t",raiz->conteudo);

        imprimir(raiz->direita);//imprime as lindas a direita
    }


}

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

int buscar(No *raiz,char chave)
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

No* remover(No *raiz,char chave)
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
                if((raiz->esquerda != NULL) ^ (raiz->direita != NULL)){ 
                    No *auxiliar;
                    if(raiz->esquerda != NULL){     //salva e filhe
                        auxiliar = raiz->esquerda;

                    }else{
                        auxiliar = raiz->direita;
                    }
                    free(raiz);
                    return auxiliar;

                }else { //2 filhes
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


        }
        else
        {
            if(chave < raiz->conteudo)
            {
                raiz->esquerda = remover(raiz->esquerda,chave);
            }
            else
            {
                raiz->direita = remover(raiz->direita,chave);
            }
            return raiz;
        }

    }
    raiz->altura = maior( alturaNo(raiz->esquerda), alturaNo(raiz->direita))+1; //calcula a altura

     raiz = balancear(raiz);//balancea ou n
     return raiz;

}

int main()
{
    int op;
    char valor;


    No *raiz = NULL;


    do
    {
        printf("\n0 pra sair\n1-inserir\n2-imprimir encaminhamentos\n3-numero de elementos\n4-buscar elemento\n5-remover\n");
        scanf("%d",&op);
        getchar();
        switch(op)
        {
        case 0:
            printf("adeus");
            break;
        case 1:
            printf("insira o valor: ");
            scanf("%c",&valor);
            getchar();
            raiz = setElemento(raiz,valor);
            system("cls");
            break;
        case 2:
            printf("impressao\n");
            //imprimir(raiz);
            printf("\nPre-fixado: ");
            preFixado(raiz);
            printf("\nCentral: ");
            central(raiz);
            printf("\nPos-fixado: ");
            posFixado(raiz);
            break;
        case 3:

            break;
        case 4:
            printf("Digite um numero para buscar: ");
            scanf("%c",&valor);
            getchar();
            printf("%c",buscar(raiz,valor));
            break;
        case 5:
            printf("insira o valor a ser removido: ");
            scanf("%c",&valor);
            getchar();
            raiz = remover(raiz,valor);
            break;


        default:
            printf("oi amor\n");
            break;
        }

    }
    while(op != 0);



    return 0;
}
