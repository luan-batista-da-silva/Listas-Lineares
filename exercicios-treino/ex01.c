#include <stdio.h>
#include <stdlib.h>

typedef struct _sNode SNode;
typedef struct _linkedList LinkedList;

SNode* SNode_create(int val);

LinkedList* LinkedList_create();
void LinkedList_add_first(LinkedList* L, int val);
void LinkedList_add_last(LinkedList* L, int val);
void LinkedList_print(const LinkedList* L);


struct _sNode
{
    int val;
    SNode* next;
};

struct _linkedList
{
    SNode* begin;
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
}

void LinkedList_add_first(LinkedList* L, int val) {
    SNode* p = SNode_create(val);
    p->next = L->begin;
    L->begin = p;
}

void LinkedList_print(const LinkedList* L) {
    SNode* p = L->begin;

    printf("L -> ");
    while (p != NULL) {
        printf("%d -> ", p->val);
        p = p->next;
    }
    printf("NULL");
}

void LinkedList_add_last(LinkedList* L, int val) {
    SNode* q = SNode_create(val);
    if (L->begin == NULL) {
        L->begin = q;
    }
    else {
        SNode* p = L->begin;
        
        // Navegando até o último Nó
        while (p->next != NULL) {
            p = p->next;
        }
        // Aqui o ponteiro p, aponta para o nó final da lista
        p->next = q;
    }
}

int main() {
    LinkedList* L = LinkedList_create();

/*
    LinkedList_add_first(L, 5);
        LinkedList_print(L);
        puts("");
    LinkedList_add_first(L, 4);
        LinkedList_print(L);
        puts("");
    LinkedList_add_first(L, 2);
        LinkedList_print(L);
        puts("");
    LinkedList_add_first(L, 10);
        LinkedList_print(L);
*/

    LinkedList_add_last(L, 10); 
    LinkedList_add_last(L, 2);
    LinkedList_add_last(L, 4);
    LinkedList_add_last(L, 5);
    LinkedList_add_last(L, 7);
    LinkedList_print(L);

    return 0;
}




