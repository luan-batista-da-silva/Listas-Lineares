#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _sNode SNode;
typedef struct _linkedList LinkedList;

SNode* SNode_create(int val);

LinkedList* LinkedList_create();
void LinkedList_add_first(LinkedList* L, int val);
void LinkedList_add_last(LinkedList* L, int val);
void LinkedList_print(const LinkedList* L);
bool LinkedList_is_empty(const LinkedList* L);
void LinkedList_remove(LinkedList* L, int val);
void LinkedList_destroy(LinkedList** L_ref);


struct _sNode
{
    int val;
    SNode* next;
};

struct _linkedList
{
    SNode* begin;
    SNode* end;
};

SNode* SNode_create(int val) {
    SNode* snode = (SNode*)malloc(sizeof(SNode));
    snode->val = val;
    snode->next = (SNode*)NULL;

    return snode;
}

LinkedList* LinkedList_create() {
    LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
    L->begin = (SNode*)NULL;
    L->end = (SNode*)NULL;
}

// void LinkedList_add_first(LinkedList* L, int val) {
//     SNode* p = SNode_create(val);
//     p->next = L->begin;
//     L->begin = p;
// }

void LinkedList_add_first(LinkedList* L, int val) {
    SNode* p = SNode_create(val);
    p->next = L->begin;
    
    if (LinkedList_is_empty(L)) {
        L->end = p;
    }

    L->begin = p;
}

void LinkedList_print(const LinkedList* L) {
    SNode* p = L->begin;

    printf("L -> ");
    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    puts("NULL");

    if (L->end == NULL) {
        printf("L->end = NULL\n");
    }
    else {
        printf("L->end = %d\n", L->end->val);
    }
}

void LinkedList_add_last(LinkedList* L, int val) {
    SNode* q = SNode_create(val);
    if (LinkedList_is_empty(L)) {
        L->begin = q;
        L->end = q;
    }
    else {
        SNode* p = L->begin;
        
        // Navegando até o último Nó
        while (p->next != NULL) {
            p = p->next;
        }
        // Aqui o ponteiro p, aponta para o nó final da lista
        p->next = q;
        L->end = q;
    }
}

bool LinkedList_is_empty(const LinkedList* L) {
    return (L->begin == NULL && L->end == NULL);
}

void LinkedList_remove(LinkedList* L, int val) {
    if (!LinkedList_is_empty(L)) {
        SNode* prev = (SNode*)NULL;
        SNode* pos = L->begin;
        
        while (pos != NULL && pos->val != val) {
            prev = pos;
            pos = pos->next;
        }

        if (pos != NULL) {
            if (L->end == pos) {
                L->end = prev;
            }
            if (L->begin == pos) {
                L->begin = pos->next;
            }
            else {
                prev->next = pos->next;
            }
            free(pos);
        }
    }

/*
    if (!LinkedList_is_empty(L)) {
        // Caso 1 - Removendo no Início da lista
        if (L->begin->val == val) {
            SNode* pos = L->begin;

            if (L->begin == L->end) {
                L->end = (SNode*)NULL;
            }

            L->begin = L->begin->next;
            free(pos);
        }
        // Caso 2 - Removendo no meio da lista
        else {
            SNode* pos = L->begin->next;
            SNode* prev = L->begin;
            while (pos != NULL && pos->val != val) {
                prev = pos;
                pos = pos->next;
            }

            if (pos != NULL) {
                prev->next = pos->next;
                // Caso 3 - Removendo e corrigindo a remoção no final da lista
                if (pos->next == NULL) {
                    L->end = prev;
                }
                free(pos);
            } 
        }
    }
*/
    
}

void LinkedList_destroy(LinkedList** L_ref) {
    puts("Chamando Destroy");
    LinkedList* L = *L_ref;

    SNode* p = L->begin;
    SNode* aux = (SNode*)NULL;

    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }

    free(L);
    *L_ref = (LinkedList*)NULL;
}

int main() {
    LinkedList* L = LinkedList_create();


    LinkedList_add_last(L, 10);
        LinkedList_print(L);
        puts("");
    LinkedList_add_last(L, 2);
        LinkedList_print(L);
        puts("");
    LinkedList_add_last(L, 4);
        LinkedList_print(L);
        puts("");
    LinkedList_add_last(L, 5);
        LinkedList_print(L);
        puts("");
    LinkedList_add_last(L, 7);
        LinkedList_print(L);
    LinkedList_remove(L, 7);
        LinkedList_print(L);

    LinkedList_destroy(&L);


    // LinkedList_add_last(L, 10); 
    // LinkedList_add_last(L, 2);
    // LinkedList_add_last(L, 4);
    // LinkedList_add_last(L, 5);
    // LinkedList_add_last(L, 7);
    // LinkedList_print(L);



    return 0;
}




