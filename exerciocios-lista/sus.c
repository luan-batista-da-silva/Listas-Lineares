#include <stdio.h>
#include <stdlib.h>

typedef struct paciente Paciente;
typedef struct fila Fila;
typedef struct horaAtual Hora;


Paciente* Paciente_create(int horas, int min, int tempCrit);
Fila* Fila_create();
Hora* Hora_createHoraAtual();
void Fila_add_last(Fila* f, int horas, int min, int tempCrit);
int Paciente_verificaCritico(Hora* h, Fila* f);
void Fila_print(Fila* f);

struct paciente {
    int horas;
    int min;
    int tempCrit;
    Paciente* prox;
};

struct fila {
    Paciente* begin;
    Paciente* end;
};

struct horaAtual {
    int hora;
    int min;
};


Fila* Fila_create() {
    Fila* F = (Fila*)malloc(sizeof(Fila));
    F->begin = (Paciente*)NULL;
    F->end = (Paciente*)NULL;

    return F;
}

Paciente* Paciente_create(int horas, int min, int tempCrit) {
    Paciente* p = (Paciente*)malloc(sizeof(Paciente));

    p->horas = horas;
    p->min = min;
    p->tempCrit = tempCrit;
    p->prox = (Paciente*)NULL;

    return p;
}

Hora* Hora_createHoraAtual() {
    Hora* h = (Hora*)malloc(sizeof(Hora));
    h->hora = 7;
    h->min = 0;

    return h;
}

void Fila_add_last(Fila* f, int horas, int min, int tempCrit) {
    Paciente* p = Paciente_create(horas, min, tempCrit);
    if (f->begin == NULL && f->end == NULL) {
        f->begin = p;
        f->end = p;
    }
    else {
        f->end->prox = p;
        f->end = p;
    }
}

int Paciente_verificaCritico(Hora* h, Fila* f) {
    Paciente* p = f->begin;
    int c = 0;
    int tempPassou;

    if (p != NULL) {
        while (p != NULL) {
            tempPassou = (h->hora - p->horas) * 60 + (h->min - p->min);

            if (tempPassou > p->tempCrit) {
                c++;
            }

            h->min += 30;
            if (h->min == 60) {
                h->hora++;
                h->min = 0;
            }
            
            p = p->prox;
        }
    }

    return c;
}

void Fila_print(Fila* f) {
    Paciente* p = f->begin;
    while (p != NULL) {
        printf("%d %d %d\n", p->horas, p->min, p->tempCrit);
        p = p->prox;
    }
}


int main() {
    Fila* filaSus = (Fila*)NULL;
    Hora* horaAtual = (Hora*)NULL;
    int qntPaciente;
    int horas, min, tempCrit;
    int i = 0;
    int countCritico = 0;

    scanf("%d", &qntPaciente);

    if (qntPaciente < 1 || qntPaciente > 50) {
        return 0;
    }

    horaAtual = Hora_createHoraAtual();
    filaSus = Fila_create();

    for (i = 0; i < qntPaciente; i++) {
        scanf("%d %d %d", &horas, &min, &tempCrit);
        if (horas < 7 || horas > 19) {
            puts("Nao atendemos esse horario!");            return 0;
        }
        if (min < 0 || min >= 60) {
            puts("Nao e possivel ter esse horario!");
            return 0;
        }
        if (tempCrit < 0 || tempCrit > 720) {
            puts("Nao podemos atender esse paciente!");
            return 0;
        }
        Fila_add_last(filaSus, horas, min, tempCrit);
    }


    countCritico = Paciente_verificaCritico(horaAtual, filaSus);

    printf("%d", countCritico);

    return 0;
}