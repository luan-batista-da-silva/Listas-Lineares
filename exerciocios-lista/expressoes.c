#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct simbolos Simbolos;
typedef struct expressao Expressao;
typedef struct cadeias Cadeias;
typedef struct fila Fila;

Expressao* Expressao_create();
Simbolos* Simbolos_create(char val);
Fila* Fila_create();
Cadeias* Cadeias_create(Expressao* E);
void Expressao_add_last(Expressao* E, char val);
void Fila_add_last(Fila* F, Expressao* E);
void Expressao_print(Expressao* E);
void Expression_verify_is_correct(Fila* F);

struct simbolos {
    char caracter;
    Simbolos* next;
};

struct expressao {
    Simbolos* begin;
    Simbolos* end;
};

struct cadeias {
    Expressao* exp;
    Cadeias* next;
};

struct fila {
    Cadeias* begin;
    Cadeias* end;
};

Expressao* Expressao_create() {
    Expressao* E = (Expressao*)calloc(1, sizeof(Expressao));
    E->begin = NULL;
    E->end = NULL;
    return E;
}

Simbolos* Simbolos_create(char val) {
    Simbolos* p = (Simbolos*)calloc(1, sizeof(Simbolos));
    p->caracter = val;
    p->next = NULL;
    return p;
}

Fila* Fila_create() {
    Fila* F = (Fila*)calloc(1, sizeof(Fila));
    F->begin = NULL;
    F->end = NULL;
    return F;
}

Cadeias* Cadeias_create(Expressao* E) {
    Cadeias* c = (Cadeias*)calloc(1, sizeof(Cadeias));
    c->exp = E;
    c->next = NULL;
    return c;
}

void Expressao_add_last(Expressao* E, char val) {
    Simbolos* p = Simbolos_create(val);

    if (E->begin == NULL && E->end == NULL) {
        E->begin = p;
        E->end = p;
    } else {
        E->end->next = p;
        E->end = p;
    }
}

void Fila_add_last(Fila* F, Expressao* E) {
    Cadeias* c = Cadeias_create(E);

    if (F->begin == NULL && F->end == NULL) {
        F->begin = c;
        F->end = c;
    } else {
        F->end->next = c;
        F->end = c;
    }
}

void Expressao_print(Expressao* E) {
    Simbolos* p = E->begin;

    while (p != NULL) {
        printf("%c", p->caracter);
        p = p->next;
    }
}

void Expression_verify_is_correct(Fila* F) {
    Cadeias* c = F->begin;

    while (c != NULL) {
        Simbolos* p = c->exp->begin;
        int chaves = 0, parenteses = 0, colchete = 0;
        int countAbre = 0, countFecha = 0;
        int expressionCorrect = TRUE;

        while (p != NULL && expressionCorrect) {
            if (p->caracter == '(') {
                countAbre++;
                parenteses++;
            } else if (p->caracter == ')') {
                countFecha++;
                if (countAbre < countFecha) {
                    expressionCorrect = FALSE;
                }
                parenteses--;
            } else if (p->caracter == '[') {
                countAbre++;
                colchete++;
            } else if (p->caracter == ']') {
                countFecha++;
                if (countAbre < countFecha) {
                    expressionCorrect = FALSE;
                }
                colchete--;
            } else if (p->caracter == '{') {
                countAbre++;
                chaves++;
            } else if (p->caracter == '}') {
                countFecha++;
                if (countAbre < countFecha) {
                    expressionCorrect = FALSE;
                }
                chaves--;
            }

            p = p->next;
        }

        if (chaves == 0 && colchete == 0 && parenteses == 0 && expressionCorrect) {
            printf("bem-formada\n");
        } else {
            printf("mal-formada\n");
        }

        c = c->next;
    }
}



int main() {
    Fila* fila = NULL;
    char caracteres[1001];
    int i, tam, cadeias, j;

    scanf("%d%*c", &cadeias);
    if (cadeias < 1 || cadeias > 20) {
        return 0;
    }

    fila = Fila_create();

    for (i = 0; i < cadeias; i++) {
        scanf("%[^\n]%*c", caracteres);
        Expressao* expressao = Expressao_create();
        tam = strlen(caracteres);

        for (j = 0; j < tam; j++) {
            Expressao_add_last(expressao, caracteres[j]);
        }

        Fila_add_last(fila, expressao);
    }

    Expression_verify_is_correct(fila);

    return 0;
}
