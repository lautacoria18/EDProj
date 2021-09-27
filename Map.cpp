#include "Common.h"
#include "Map.h"
//l
typedef int Priority;

Priority randomPriority() {
        return rand();
}

struct Node {
    Key clave;
    Value valor;
    Priority prioridad;
    Node* hijoIzq;
    Node* hijoDer;
    };


struct MapRepr {
    Node* raiz;
    int tam;
};

Map emptyM() { //0(1)

MapRepr* map1 = new MapRepr;

    map1-> raiz = NULL;
    map1-> tam = 0;

    return map1;
}

int sizeM(Map m) { // 0(1)

    return m->tam;

}


bool lookupN(Node* n, Key k, Value& v) {

bool res = false;

    if (n==NULL) {
                  return false;
                 }

    else {
                if  (n->clave == k) {
                                    v= n->valor;
                                    return true;
                                    }

                if (k < n->clave)  {
                                   res = res || lookupN(n->hijoIzq, k, v);
                                   }

                if (k > n->clave)  {
                                   res = res || lookupN(n->hijoDer, k, v);
                                   }
        }

        return res;
}

bool lookupM(Map m, Key k, Value& v) {

              return lookupN(m->raiz, k, v);
}


void intercambiarEntreNodos(Node* a, Node* b){
Node* tmp = new Node;

        tmp->valor= a->valor;
        tmp->clave= a->clave;
        tmp->prioridad= a->prioridad;

        a->valor= b->valor;
        a->clave= b->clave;
        a->prioridad= b->prioridad;

        b->valor= tmp->valor;
        b->clave= tmp->clave;
        b->prioridad= tmp->prioridad;

}

void swapHijoIzq(Node* n){

Node* hijo=n->hijoIzq;
Node* n1= hijo -> hijoIzq;
Node* n2= hijo -> hijoDer;
Node* n3= n->hijoDer;

        if ((n->prioridad) < (n->hijoIzq->prioridad)){
                                                    intercambiarEntreNodos(n, hijo);

                                                    n->hijoIzq = n1;
                                                    n->hijoDer = hijo;

                                                    hijo-> hijoIzq=n2;
                                                    hijo-> hijoDer=n3;
                                                    }
}

void swapHijoDer(Node* n){

Node* hijo= n->hijoDer;
Node* n1= n->hijoIzq;
Node* n2= hijo->hijoIzq;
Node* n3= hijo->hijoDer;

    if((n->prioridad) < (n->hijoDer->prioridad)){
                                                intercambiarEntreNodos(n,hijo);

                                                n->hijoIzq=hijo;
                                                n->hijoDer=n3;

                                                hijo->hijoIzq=n1;
                                                hijo->hijoDer=n2;
                                                }
}

Node* crearNodo (Node* n, Key k, Value v) {

Node* nuevoNodo= new Node;

        nuevoNodo->clave=k;
        nuevoNodo->valor=v;
        nuevoNodo->prioridad=randomPriority();
        nuevoNodo->hijoIzq=NULL;
        nuevoNodo->hijoDer=NULL;

}

Node* insertN(Node* n, Key k, Value v){

    if(n == NULL){
                    return crearNodo(n, k , v);
                 }
            else
                    if (n->clave > k){
                                        n->hijoIzq=insertN(n->hijoIzq,k,v);
                                        swapHijoIzq(n);
                                     }
                    else {
                                n->hijoDer=insertN(n->hijoDer, k,v);;
                                        swapHijoDer(n);
                         }
    return n;
}

Node* modificarN(Node* n, Key k, Value v) {

    if (n->clave==k){
                    n->valor=v;
                    }

    else {

            if (n->clave > k){
                              n->hijoIzq=modificarN(n->hijoIzq,k,v);
                             }
            else             {
                              n->hijoDer=modificarN(n->hijoDer, k,v);
                             }
        }
    return n;
}

void insertM(Map m, Key k, Value v) {

Value x;

    if (!lookupM(m, k, x)){
                            m->raiz=insertN(m->raiz,k,v);
                            m->tam++;
                          }
    else                  {
                            m->raiz=modificarN(m->raiz, k, v);
                          }
}


Node* borrarElMasChico(Node* n,Key &k,Value &v){

    if (n->hijoIzq==NULL) {
                            Node*tmp =n->hijoDer;
                            k=n->clave;
                            v=n->valor;
                            delete n;
                            return tmp;
                         }

                    else  {
                                n->hijoIzq=borrarElMasChico(n->hijoIzq,k,v);
                                return n;
                          }
}




Node* cambiarDatos(Node* n){

    if((n->hijoDer)==NULL){
                            Node* nodoModificado= n->hijoIzq;
                            delete n;
                            return nodoModificado;
                          }

    else                  {
                            Key k;
                            Value v;
                            n->hijoDer=borrarElMasChico(n->hijoDer,k,v);
                            n->clave=k;
                            n->valor=v;

                          }
                return n;
}

Node* removeN(Node* n, Key k){

    if (n==NULL){
                    return n;
                }
        else
            if (k > n->clave){
                                n->hijoDer=removeN(n->hijoDer,k);
                             }
        else
            if (k < n->clave){
                                n->hijoIzq=removeN(n->hijoIzq,k);
                             }
            else             {
                                n=cambiarDatos(n);
                                return n;
                             }
}


void removeM(Map m, Key k) {

Value v;

    if (m!=NULL) {
                    if (lookupM(m, k, v))   {
                                            m->raiz=removeN(m->raiz, k);
                                            m->tam--;
                                            }
                 }
}


void destroyM(Map m) {

    while (m->raiz != NULL){
                            removeM(m, m->raiz->clave);
                           }
        delete m;
}


