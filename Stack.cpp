#include "Common.h"
#include "Stack.h"
#include <stdlib.h>
//l
struct Nodo {
     int valor;
     Nodo* siguiente;
};

struct StackRepr {
    int tam;
    Nodo* tope;
};


Stack emptyS() {

StackRepr* s1= new StackRepr;

        s1-> tam = 0;
        s1-> tope = NULL;

        return s1;
}

int sizeS(Stack s) {
        return s->tam ;
}

void pushS(Stack s, int x) {

Nodo* n1 = new Nodo;

    n1-> valor= x;

    if (sizeS(s) != 0) {
                        n1-> siguiente = s-> tope;
                       }
        s-> tam ++;
        s-> tope= n1;
}

int topS(Stack s) { //Funciona
    return s-> tope-> valor;
}

void popS(Stack s) {

Nodo* n1= s->tope;

    delete s-> tope;
    s-> tam--;
    s-> tope= n1-> siguiente;


}

void destroyS(Stack s) {
        delete s;
}
