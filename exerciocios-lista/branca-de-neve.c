/*
    Linha 1 - t (numero de casos teste) 1 <= t <= 1000 -> Cada Caso tem que ter (3 + m) linhas
        Linha 1 do caso - Numero n de anões && Numero c de cores de toucas (3 <= n <= 3 * 1000)
        Linha 2 do caso - Deve ter as n toucas, cada um com uma cor respectiva (1 <= c1 <= c <= n)
        Linha 3 do caso - O valor de m (1 <= m <= 1000)
        Próximas m linhas - a e b, sendo que (1 <= a <= b <= n), representam os anões que aparecem de a à b
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct anao Anao;
typedef struct fila Fila;
typedef struct album Album;
typedef struct foto Foto;


Fila* Fila_create();
Anao* Anao_create(int index, int touca);
void Anao_add_last(Fila* F, int index, int touca);
void Fila_print(Fila* F);
Album* Album_create();
Foto* Foto_create(int a, int b, int index);
void Album_add_last(Album* A, int a, int b, int index);
void Album_print(Album* A);
void Album_is_prety(Album* A, Fila* F, int index, int qntToucas, int qntAnao);


struct anao {
    int index;
    int touca;
    Anao* next;
};

struct fila {
    Anao* begin;
};

struct foto {
    int index;
    int a;
    int b;
    Foto* next;
};


struct album {
    Foto* begin;
};


Fila* Fila_create() {
    Fila* F = (Fila*)malloc(sizeof(Fila));

    F->begin = (Anao*)NULL;

    return F;
}

Anao* Anao_create(int index, int touca) {
    Anao* p = (Anao*)malloc(sizeof(Anao));

    p->index = index;
    p->touca = touca;
    p->next = (Anao*)NULL;

    return p;
}


void Anao_add_last(Fila* F, int index, int touca) {
    Anao* q = Anao_create(index, touca);
    if (F->begin == NULL) {
        F->begin = q;
    }
    else {
        Anao* p = F->begin;

        while (p->next != NULL) {
            p = p->next;
        }

        p->next = q;
    }
}

void Fila_print(Fila* F) {
    Anao* p = F->begin;

    while (p!= NULL) {
        printf("%d ", p->touca);
        p = p->next;
    }
}

Album* Album_create() {
    Album* A = (Album*)malloc(sizeof(Album));

    A->begin = (Foto*)NULL;

    return A;    
}

Foto* Foto_create(int a, int b, int index) {
    Foto* f = (Foto*)malloc(sizeof(Foto));

    f->a = a;
    f->b = b;
    f->index = index;
    f->next = (Foto*)NULL;

    return f;    
}

void Album_add_last(Album* A, int a, int b, int index) {
    Foto* f = Foto_create(a, b, index);
    if (A->begin == NULL) {
        A->begin = f;
    }
    else {
        Foto* p = A->begin;

        while (p->next != NULL) {
            p = p->next; 
        }

        p->next = f;
    }
}

void Album_print(Album* A) {
    Foto* p = A->begin;

    while (p != NULL) {
        printf("%d %d\n", p->a, p->b);
        p = p->next;
    }
}

void Album_is_prety(Album* A, Fila* F, int index, int qntToucas, int qntAnao) {
    Foto* f = A->begin;
    Anao* a = F->begin;
    int countBnt = 0;
    int toucaBnt = 0;
    int t = 0;

    while (f != NULL) {
        qntAnao = f->b;
        for (t = 1; t < qntToucas; t++) {
            while (a->index != f->b) {
                if (f->a >= a->index || f->b <= a->index) {
                    if (t == a->touca) {
                        countBnt++;
                    }
                }
                a = a->next;
            }
            
            if (countBnt > qntAnao / 2) {
                toucaBnt = t;
            }
            else {
                toucaBnt = 0;
            }

            countBnt = 0;        
        }
        
        if (toucaBnt == 0) {
            printf("feia\n");
        }
        else {
            printf("bonita %d\n", toucaBnt);
        }
        
        f = f->next;
    }    
}

// ===================== MAIN ==============================

int main() {
    Fila* fila = (Fila*)NULL;
    Album* album = (Album*)NULL;
    int casosTeste, countTeste = 0;
    int qntAnao, qntToucas, qntFotos;
    int touca;
    int a, b;
    int i = 0;
    int res = 0;



    scanf("%d", &casosTeste);
    if (casosTeste < 1 || casosTeste > 1000) {
        return 0;
    }

    scanf("%d %d", &qntAnao, &qntToucas);
    if (qntAnao < 3 || qntAnao > 3000) {
        return 0;
    }

    while (countTeste != casosTeste) {
        fila = Fila_create();
        for (i = 1; i <= qntAnao; i++) {
            scanf("%d", &touca);
            Anao_add_last(fila, i, touca);
        }
        countTeste++;
    }

    scanf("%d", &qntFotos);
    if (qntFotos < 1 || qntFotos > 1000) {
        return 0;
    }
    album = Album_create();

    for (i = 1; i <= qntFotos; i++) {
        scanf("%d %d", &a, &b);
        Album_add_last(album, a, b, i);
    }

    
    Album_is_prety(album, fila, i, qntToucas, qntAnao);
        

    return 0;
}