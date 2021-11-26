#include <stdio.h>
#include <stdlib.h>

struct t1
{
    int v1;
    int v2;
};

typedef struct t1 T1;

void imprime5(T1* p2){
    printf("Valores   p2: %d %d %d %d\n", p2[0].v1, p2[0].v2, p2[1].v1, p2[1].v2);
    printf("Valores   p2: %d %d %d %d\n", p2->v1, p2->v2, (p2+1)->v1, (p2+1)->v2);
    printf("Endereco  p2: %d %d %d %d\n", &p2[0].v1, &p2[0].v2, &p2[1].v1, &p2[1].v2);
    p2->v2 = 20;
}

void imprime4(T1* p2){
    printf("Valores   p2: %d %d %d %d\n", p2[0].v1, p2[0].v2, p2[1].v1, p2[1].v2);
    printf("Valores   p2: %d %d %d %d\n", p2->v1, p2->v2, (p2+1)->v1, (p2+1)->v2);
    printf("Endereco  p2: %d %d %d %d\n", &p2[0].v1, &p2[0].v2, &p2[1].v1, &p2[1].v2);
    imprime5(p2);
    p2[1].v2 = 222;

}

void imprime3(int* p){
    printf("Valores  p2: %d %d %d %d\n", p, p+1, p+2, p+3);
    printf("Endereco p2: %d %d %d %d\n", p, *p, *(p+1), *(p+2));
    printf("Endereco p2: %d %d %d   \n", p[0], p[1], p[2]);
    *(p+2) = 20;
}

void imprime(int* p){
    printf("Valores  p2: %d %d %d %d\n", p, p+1, p+2, p+3);
    printf("Endereco p2: %d %d %d %d\n", p, *p, *(p+1), *(p+2));
    printf("Endereco p2: %d %d %d   \n", p[0], p[1], p[2]);
    imprime3(p);

}

int main(){
    // int t[] = {5, 7 ,9};
    // printf("Valores  t: %d %d %d \n", t[0], t[1], t[2]);
    // printf("Endereco t: %d %d %d \n", &t[0], &t[1], &t[2]);
    // int* p = t;
    // p[1] = 6;
    // *(p+2) = 8;
    // printf("Valores  p: %d %d %d %d\n", p, p+1, p+2, p+3, p+4);
    // printf("Endereco p: %d %d %d %d\n", p, *p, *(p+1), *(p+2), *(p+3));
    
    
    // int* p2 = malloc(sizeof(int) * 3);
    // p2[0] = 10;
    // *(p2+1) = 11;
    // *(p2+2) = 12;
    // printf("Valores  p2: %d %d %d %d\n", p2, p2+1, p2+2, p2+3);
    // printf("Endereco p2: %d %d %d %d\n", p2, *p2, *(p2+1), *(p2+2));
    // printf("Endereco p2: %d %d %d   \n", p2[0], p2[1], p2[2]);
    // imprime(p2);

    // printf("Valores  p2: %d %d %d %d\n", p2, p2+1, p2+2, p2+3);
    // printf("Endereco p2: %d %d %d %d\n", p2, *p2, *(p2+1), *(p2+2));
    // printf("Endereco p2: %d %d %d   \n", p2[0], p2[1], p2[2]);

    T1* p2 = malloc(sizeof(T1) * 2);
    p2[0].v1 = 10;
    p2[0].v2 = 100;
    p2[1].v1 = 11;
    p2[1].v2 = 111;
    printf("Valores   p2: %d %d %d %d\n", p2[0].v1, p2[0].v2, p2[1].v1, p2[1].v2);
    printf("Valores   p2: %d %d %d %d\n", p2->v1, p2->v2, (p2+1)->v1, (p2+1)->v2);
    printf("Endereco  p2: %d %d %d %d\n", &p2[0].v1, &p2[0].v2, &p2[1].v1, &p2[1].v2);
    imprime4(p2);

    printf("Valores   p2: %d %d %d %d\n", p2[0].v1, p2[0].v2, p2[1].v1, p2[1].v2);
    printf("Valores   p2: %d %d %d %d\n", p2->v1, p2->v2, (p2+1)->v1, (p2+1)->v2);
    printf("Endereco  p2: %d %d %d %d\n", &p2[0].v1, &p2[0].v2, &p2[1].v1, &p2[1].v2);

    //printf("Valores  p2: %d \n", (p2+1)->v2);
    // printf("Valores  p2: %d %d %d %d\n", p2, p2+1, p2+2, p2+3);
    // printf("Endereco p2: %d %d %d %d\n", p2, *p2, *(p2+1), *(p2+2));
    // printf("Endereco p2: %d %d %d   \n", p2[0], p2[1], p2[2]);
    // imprime(p2);

    // printf("Valores  p2: %d %d %d %d\n", p2, p2+1, p2+2, p2+3);
    // printf("Endereco p2: %d %d %d %d\n", p2, *p2, *(p2+1), *(p2+2));
    // printf("Endereco p2: %d %d %d   \n", p2[0], p2[1], p2[2]);
}

/*
*p é equivalente a vet[0];
vet[índice] é equivalente a *(p+índice);
vet é equivalente a &vet[0];
&vet[índice] é equivalente a (vet + índice);
*/