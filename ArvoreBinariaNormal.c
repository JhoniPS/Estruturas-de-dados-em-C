#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
    int conteudo;
    struct no *esquerda, *direita;

} No; //estrutura da arvore binaria

No* setElemento(No *raiz, int valor)
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

        printf("%d ",raiz->conteudo);

        preFixado(raiz->esquerda);//imprime as lindas a esquerda

        preFixado(raiz->direita);//imprime as lindas a direita

    }


}// Encaminhamento pre-ordem

void central(No *raiz) 
{
    if(raiz != NULL)
    {

        central(raiz->esquerda);

        printf("%d ", raiz->conteudo);

        central(raiz->direita);

    }
}// Encaminhamento em ordem

void posFixado(No *raiz)
{
    if(raiz != NULL)
    {

        posFixado(raiz->esquerda);

        posFixado(raiz->direita);

        printf("%d ", raiz->conteudo);

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

No* remover(No *raiz, int chave)
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

}

int main()
{
    int op; int valor;

    No *raiz = NULL;

    do
    {
        printf("\n0 pra sair\n1 - Inserir\n2 - Imprimir Caminhamentos\n3 - Numero de elementos\n4 - Buscar elemento\n5 - Remover\n");
        scanf("%d",&op);
        getchar();
        switch(op)
        {
        case 0:
            printf("adeus");
            break;
        case 1:
            printf("insira o valor: ");
            scanf("%d",&valor);
            getchar();
            raiz = setElemento(raiz,valor);
            system("cls");
            break;
        case 2:
            printf("Pre-fixado: ");
            preFixado(raiz);
            printf("\nCentral: ");
            central(raiz);
            printf("\nPos-fixado: ");
            posFixado(raiz);
            break;
        case 3:
            printf("Quantidade de elementos: %d", tamanho(raiz));
            break;
        case 4:
            printf("Digite um numero para buscar: ");
            scanf("%d",&valor);
            getchar();
            printf("%d",buscar(raiz,valor));
            break;
        case 5:
            printf("insira o valor a ser removido: ");
            scanf("%d",&valor);
            getchar();
            raiz = remover(raiz,valor);
            break;
        default:
            printf("Opcao invalida\n");
            break;
        }

    }
    while(op != 0);

    return 0;
}
