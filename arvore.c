#include <stdio.h>
#include <stdlib.h>

typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
} Arvore;

Arvore *cria_arv_vazia();
Arvore *arv_constroi(int c, Arvore *e, Arvore *d);
int verifica_arv_vazia(Arvore *a);
Arvore *arv_libera(Arvore *a);
int arv_pertence(Arvore *a, int c);
void arv_imprime(Arvore *a);
int conta_nos(Arvore *a);
char max_arvore(Arvore *a);
int altura_arvore(Arvore *a);
int nos_folha_arvore(Arvore *a);
int eh_espelho(Arvore *arv_a, Arvore *arv_b);
int arv_bin_check(Arvore *a);
Arvore *cria_espelho(Arvore *arv_a);

Arvore *cria_arv_vazia()
{
    return NULL;
}

Arvore *arv_constroi(int c, Arvore *e, Arvore *d)
{
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    a->info = c;
    a->esq = e;
    a->dir = d;
    return a;
}

int verifica_arv_vazia(Arvore *a)
{
    return (a == NULL);
}

Arvore *arv_libera(Arvore *a)
{
    if (!verifica_arv_vazia(a))
    {
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

void arv_imprime(Arvore *a)
{
    if (a == NULL)
    {
        printf(" <> ");
        return;
    }
    printf(" < %d", a->info);
    arv_imprime(a->esq);
    arv_imprime(a->dir);
    printf(" > ");
}

int arv_pertence(Arvore *a, int c)
{
    if (a == NULL)
        return 0;
    if (a->info == c)
        return 1;
    if (arv_pertence(a->esq, c))
        return 1;
    if (arv_pertence(a->dir, c))
        return 1;
}

int conta_nos(Arvore *a)
{
    if (a == NULL)
        return 0;
    int dir, izq;
    dir = conta_nos(a->dir);
    izq = conta_nos(a->esq);
    return (dir + izq + 1);
}

char max_arvore(Arvore *a)
{
    if (a == NULL)
        return 0;
    int ini = a->info;
    int esq, dir;
    esq = max_arvore(a->esq);
    dir = max_arvore(a->dir);

    if ((ini > esq) && (ini > dir))
        return ini;
    if ((esq > ini) && (esq > dir))
        return esq;
    if ((dir > ini) && (dir > ini))
        return dir;
}
int altura_arvore(Arvore *a)
{
    if (a == NULL)
        return 0;
    int esq = altura_arvore(a->esq);
    int dir = altura_arvore(a->dir);
    if (esq > dir)
        return (esq + 1);
    else
        return (dir + 1);
}

int nos_folha_arvore(Arvore *a)
{
    if (a == NULL)
        return 0;
    if (a->dir == NULL && a->esq == NULL)
        return 1;
    int esq = nos_folha_arvore(a->esq);
    int dir = nos_folha_arvore(a->dir);
    return (esq + dir);
}

int eh_espelho(Arvore *arv_a, Arvore *arv_b)
{
    if (!arv_a && !arv_b)
        return 1;
    int dir = eh_espelho(arv_a->dir, arv_b->esq);
    int esq = eh_espelho(arv_a->esq, arv_b->dir);

    if (dir && esq && (arv_a->info == arv_b->info))
        return 1;
    else
        return 0;
}

Arvore *cria_espelho(Arvore *arv_a)
{
    if (arv_a == NULL)
        return NULL;
    Arvore *a = (Arvore *)malloc(sizeof(Arvore));
    a->info = arv_a->info;
    a->dir = cria_espelho(arv_a->esq);
    a->esq = cria_espelho(arv_a->dir);
    return a;
}

int arv_bin_check(Arvore *a)
{
     if (!a) return 1;
    int dir = arv_bin_check(a->dir);
    int esq = arv_bin_check(a->esq);
    if(a->dir){
        if(!(a->info < a->dir->info)) return 0;
    }
    if(a->esq){
        if (!(a->info > a->esq->info)) return 0;
    }
    if(esq && dir) return 1;
    else return 0;
}

int main(int argc, char *argv[])
{
    Arvore *a, *a1, *a2, *a3, *a4, *a5, *ae;
    int p, f, b, c;
    a1 = arv_constroi(6, cria_arv_vazia(), cria_arv_vazia());
    a2 = arv_constroi(4, cria_arv_vazia(), a1);
    a3 = arv_constroi(11, cria_arv_vazia(), cria_arv_vazia());
    a4 = arv_constroi(16, cria_arv_vazia(), cria_arv_vazia());
    a5 = arv_constroi(14, a3, a4);
    a = arv_constroi(10, a2, a5);
    // imprime o arvore
    arv_imprime(a);
    printf("\n Digita um inteiro: ");
    scanf("%d", &c);
    // retorna se um elemnto esta o no no arvore
    p = arv_pertence(a, c);
    if (p == 1)
        printf("|-> %d pertence ao arvore\n", c);
    else
        printf("|-> %d Nao pertence ao arvore\n", c);
    // conta os nos do arvore
    p = conta_nos(a);
    printf("|-> %d nos em total\n", p);
    // retorna o maximo valor do arvore
    c = max_arvore(a);
    printf("|-> O maximo valor no arvore e %d\n", c);
    // altura do arvore
    p = altura_arvore(a);
    printf("|-> A altura do arvore e : %d\n", p);
    // nos que sao folha
    f = nos_folha_arvore(a);
    printf("|-> A quantidade de nos folha no arvore e : %d\n", f);
    // cria um arvore espelho
    ae = cria_espelho(a);
    printf("|-> Espelho: ");
    arv_imprime(ae);
    // verifica se o arvore e espelho
    p = eh_espelho(a, ae);
    if (p == 1)
        printf("\n|-> Sao arvores espelhados");
    else
        printf("\n|-> Nao sao arvores espelhados");

    //verifica se o arvore e de busca binaria
    b = arv_bin_check(a);
    if (b == 1)
        printf("\n|-> E uma arvore binaria");
    else
        printf("\n|-> Nao e uma arvore binaria");
    // verifica no arvore espelho        
    b = arv_bin_check(ae);
    if (b == 1)
        printf("\n|-> E uma arvore binaria");
    else
        printf("\n|-> Nao e uma arvore binaria");

    printf("\n");
    return 0;
}
