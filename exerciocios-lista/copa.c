/*
    Primeira linha: n (1 <= n <= 60000)
    Segunda linhas n números identificadores mi
    Terceira linha: s (1 <= s <= n) quantidades de pessoas que sairam da fila
    Quarta linha: s inteiros, representando si, os identificadores das pessoas que sairam da fila na ordem que sairam
    Imrprimir (n - s), os identificadores das pessoas que restaram
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pessoa Pessoa;
typedef struct fila Fila;

Pessoa* Pessoa_create(int index);
Fila* Fila_create();
void Fila_add_last(Fila* F, int index);
void Fila_remove(Fila* F, int index);
void Fila_print(Fila* F);
void Fila_remove(Fila* F, int index);
bool Fila_is_empty(Fila* F);

struct pessoa {
    int index;
    Pessoa* next;
};

struct fila {
    Pessoa* begin;
    Pessoa* end;
};

Fila* Fila_create() {
    Fila* F = (Fila*)malloc(sizeof(Fila));
    F->begin = (Pessoa*)NULL;

    return F;
}

Pessoa* Pessoa_create(int index) {
    Pessoa* p = (Pessoa*)malloc(sizeof(Pessoa));
    p->index = index;
    p->next = (Pessoa*)NULL;

    return p;
}

bool Fila_is_empty(Fila* F) {
    return (F->begin == NULL && F->end == NULL);
}

void Fila_add_last(Fila* F, int index) {
    Pessoa* q = Pessoa_create(index);
    if (F->begin == NULL) {
        F->begin = q;
    }
    else {
        Pessoa* p = F->begin;
        
        while (p->next != NULL) {
            p = p->next;
        }

        p->next = q;
    }
}

void Fila_print(Fila* F) {
    Pessoa* p = F->begin;
    while (p != NULL) {
        printf("%d ", p->index);
        p = p->next;
    }
}



void Fila_remove(Fila* F, int index){
    if (!Fila_is_empty(F)) {
        if (F->begin->index == index) {
            Pessoa* pos = F->begin;

            if (F->begin == F->end) {
                F->end = (Pessoa*)NULL;
            }
            F->begin = F->begin->next;
            free(pos);
        }
        else {
            Pessoa* pos = F->begin->next;
            Pessoa* prev = F->begin;
            while (pos != NULL && pos->index != index) {
                prev = pos;
                pos = pos->next;
            }

            if (pos != NULL) {
                prev->next = pos->next;
                free(pos);
            }

        }
    }
}

// ====================== MAIN ============================
int main() {
    Fila* fila;
    int qntPessoas;
    int i = 0;
    int index, abandonos;

    scanf("%d", &qntPessoas);

    if (qntPessoas < 1 || qntPessoas > 60000) {
        return 0;
    }

    fila = Fila_create();

    for (i = 0; i < qntPessoas; i++) {
        scanf("%d", &index);
        Fila_add_last(fila, index);
    }       

    scanf("%d", &abandonos);

    for (i = 0; i < abandonos; i++) {
        scanf("%d", &index);
        Fila_remove(fila, index);
    }

    Fila_print(fila);

    return 0;
}