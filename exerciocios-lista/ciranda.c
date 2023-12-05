#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

// ==============================
//            ciranda.h
// ==============================

typedef struct _circ_node CircNode;
typedef struct _circ_list CircList;
CircNode *CircNode_create(char *nome, int val);
void CircNode_destroy(CircNode **cnode_ref);
CircList *CircList_create();
bool CircList_is_empty(const CircList *L);
void CircList_add_last(CircList *L, char *nome, int val);
void CircList_print(const CircList *L);
void CircList_remove(CircList *L, char *nome);
CircNode *findFirstEliminated(CircList *lk, int val);
CircNode *findRestEliminated(CircList *lk, int val);

// ===============================
//           ciranda.c
// ===============================

typedef struct _circ_node{
    int val;
    char *nome;
    struct _circ_node *prev;
    struct _circ_node *next;
} CircNode;


typedef struct _circ_list{
    CircNode *begin;
    CircNode *end;
    int size;
} CircList;

CircNode *CircNode_create(char *nome, int val){
    CircNode *cnode = (CircNode*) calloc(1, sizeof(CircNode)); 
    cnode->nome = strdup(nome);
    cnode->val = val;
    cnode->prev = cnode;
    cnode->next = cnode;

    return cnode;
}

void CircNode_destroy(CircNode **cnode_ref){
    CircNode *cnode = *cnode_ref;
    free(cnode);
    *cnode_ref = NULL;
}

CircList *CircList_create(){
    CircList *L = (CircList*) calloc(1, sizeof(CircList));
    L->begin = NULL;
    L->end = NULL;
    L->size = 0;

    return L;
}

bool CircList_is_empty(const CircList *L){
    return L->size == 0;
}

void CircList_add_last(CircList *L, char *nome, int val){
    CircNode *p = CircNode_create(nome, val);

    if (CircList_is_empty(L)){
        L->begin = p;
    }
    else{
        L->end->next = p;
        p->prev = L->end;

        // parte circular
        L->begin->prev = p;
        p->next = L->begin;
    }

    L->end = p;
    L->size++;
}

void CircList_print(const CircList *L){
    int i;
    if (CircList_is_empty(L)){
        printf("L -> NULL\n");
        printf("L->end -> NULL\n");
    }
    else{
        CircNode *p = L->begin;
        for (i = 0; i < L->size; i++){
            printf("%s ", p->nome);
            p = p->next;
        }
    }
}

void CircList_remove(CircList *L, char *nome){
    if (!CircList_is_empty(L)){
        CircNode *p = L->begin;
        
        if (strcmp(L->begin->nome, nome) == 0){
            if (L->begin == L->end){
                L->begin = NULL;
                L->end = NULL;
            }
            else{
                L->begin = p->next;
                L->begin->prev = L->end;
                L->end->next = L->begin;
            }

            CircNode_destroy(&p);
            L->size--;
        }
        else{
            p = p->next;

            while (p != L->begin){
                if (strcmp(p->nome, nome) == 0) {
                    if (L->end == p){
                        L->end = p->prev;
                    }
                    
                    p->prev->next = p->next;
                    p->next->prev = p->prev;
                    CircNode_destroy(&p);
                    L->size--;
                    break;
                }
                else{
                    p = p->next;
                }
            }
        }
    }    
}

CircNode *findFirstEliminated(CircList *lk, int val){
    int i;
    CircNode *p;
    if (val % 2 == 1){
        p = lk->begin->next;
        for (i = 0; i < val - 1; i++){
            p = p->next;
        }
    } 
    else{
        p = lk->begin->prev;
        for (i = 0; i < val - 1; i++){
            p = p->prev;
        }
    }

    return p;
}

CircNode *findRestEliminated(CircList *lk, int val){
    int i;
    CircNode *p = lk->begin;

    if (val % 2 == 1){
        for (i = 0; i < val; i++){
            p = p->next;
        }
    } 
    else{
        for (i = 0; i < val; i++){
            p = p->prev;
        }
    }

    return p;
}

// ===================================
//               main.c
// ===================================

int main(){

    CircList *lk = CircList_create();
    int i, entradas;
    scanf("%d", &entradas);
    
    for (i = 0; i < entradas; i++){
        char nome[31];
        int valor;
        scanf("%s", nome);
        getchar();
        scanf("%d", &valor);
        getchar();
        CircList_add_last(lk, nome, valor);
    }

    int chave = lk->begin->val;
    CircNode *primeiroEliminado = findFirstEliminated(lk, chave);
    chave = primeiroEliminado->val;
    CircList_remove(lk, primeiroEliminado->nome);

    for (i = 0; i < entradas - 2; i++){
        CircNode *eliminado = findRestEliminated(lk, chave);
        chave = eliminado->val;
        CircList_remove(lk, eliminado->nome);
    }

    CircList_print(lk);
    
    return 0;
}