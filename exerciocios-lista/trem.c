#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct linhaFerro LinhaFerro;
typedef struct vagao Vagao;

Vagao* Vagao_create(int index);
LinhaFerro* LinhaFerro_create();
void LinhaFerro_add_last(LinhaFerro* L, int index);
bool LinhaFerro_is_empty(const LinhaFerro* L);
void LinhaFerro_print(const LinhaFerro* L);


struct vagao {
    int index;
    Vagao* next;  
};

struct linhaFerro {
    Vagao* begin;
    Vagao* end;
};

bool LinhaFerro_is_empty(const LinhaFerro* L) {
    return (L->begin == NULL && L->end == NULL);
}

// Criar a Lista da Linha de Ferro
LinhaFerro* LinhaFerro_create() {
    LinhaFerro* L = (LinhaFerro*)malloc(sizeof(LinhaFerro));

    L->begin = (Vagao*)NULL;
    L->end = (Vagao*)NULL;

    return L;
}


Vagao* Vagao_create(int index) {
    Vagao* p = (Vagao*)malloc(sizeof(Vagao));

    p->index = index;
    p->next = (Vagao*)NULL;

    return p;
}

void Vagao_add_last(LinhaFerro* L, int index) {
    Vagao* q = Vagao_create(index);
    if (L->begin == NULL) {
        L->begin = q;
    }
    else {
        Vagao* p = L->begin;
        while (p->next != NULL) {
            p = p->next;
        }

        p->next = q;
    }
}


void LinhaFerro_print(const LinhaFerro* L) {
    Vagao* p = L->begin;

    while (p != NULL) {
        printf("%d ", p->index);
        p = p->next;
    }
}

int main () {
    LinhaFerro* L = (LinhaFerro*)NULL;
    int numVagoes, index;
    int i = 0;

    scanf("%d", &numVagoes);

    if (numVagoes < 1 || numVagoes > 1000) {
        return 0;
    }

    for (i = 0; i < numVagoes; i++) {
        scanf("%d", &index);
        Vagao_add_last(L, index);
    }

    LinhaFerro_print(L);





    return 0;
}