#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct parenteses Parenteses;
typedef struct expressao Expresion;

Expresion* Expresion_create();
Parenteses* Parenteses_create(char val);
void Expresion_add_last(Expresion* E, char val);
void Expresion_print(Expresion* E);
int Expression_verify_is_corect(Expresion* E);



struct parenteses {
    char caracter;
    Parenteses* next;
};

struct expressao {
    Parenteses* begin;
    Parenteses* end;
};

Expresion* Expresion_create() {
    Expresion* E = (Expresion*)calloc(1, sizeof(Expresion));

    E->begin = (Parenteses*)NULL;
    E->end = (Parenteses*)NULL;

    return E;
}

Parenteses* Parenteses_create(char val) {
    Parenteses* p = (Parenteses*)calloc(1, sizeof(Parenteses));

    p->caracter = val;
    p->next = (Parenteses*)NULL;

    return p;
}

void Expresion_add_last(Expresion* E, char val) {
    Parenteses* p = Parenteses_create(val);

    if (E->begin == NULL && E->end == NULL) {
        E->begin = p;
        E->end = p;
    }
    else {
        E->end->next = p;
        E->end = p;
    }
}

void Expresion_print(Expresion* E) {
    Parenteses* p = E->begin;

    while (p != NULL)
    {
        printf("%c", p->caracter);
        p = p->next;
    }
}

int Expression_verify_is_corect(Expresion* E) {
    Parenteses* p = E->begin;
    int countAbre = 0;
    int countFecha = 0;

    while (p != NULL) {
        if (p->caracter == '(') {
            countAbre++;
        }
        else if (p->caracter == ')') {
            countFecha++;
            if (countAbre < countFecha) {
                return FALSE;
            }
        }

        p = p->next;
    }

    if (countAbre >= countFecha) {
        return TRUE;
    }
    else {
        return FALSE;
    }
    
}

int main()
{
    Expresion* expressao = (Expresion*)NULL;
    Parenteses* caracter = (Parenteses*)NULL;
    char caracteres[1001];
    int i, tam;

    scanf("%[^\n]", caracteres);
    expressao = Expresion_create();

    tam = strlen(caracteres) + 1;

    for (i = 0; i < tam; i++) {
        Expresion_add_last(expressao, caracteres[i]);
    }

    if (Expression_verify_is_corect(expressao) == TRUE) {
        printf("correta\n");
    }
    else {
        printf("incorreta\n");
    }

    return 0;
}