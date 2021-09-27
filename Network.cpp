#include "Common.h"
#include "Network.h"
#include "Stack.h"
#include "Map.h"
//l
struct NetworkRepr {

        Map flechas;
        Stack acciones;
};

Network emptyN() {

NetworkRepr* neto= new NetworkRepr;

    neto->acciones =emptyS();
    neto->flechas =emptyM();

    return neto;
}

void addN(Network net, Id id) {

   pushS(net->acciones, id);
   insertM(net->flechas, id, id);
}

bool elemN(Network net, Id id) {

Value v;

    return lookupM(net->flechas, id, v);
}


Id ultimo(Network net, Id id) {

Value v;
Id tmp = id;

    lookupM(net->flechas, tmp, v);

        while (v != tmp) {
                            tmp = v;
                            lookupM(net->flechas, tmp, v);
                        }
        return v;
}

bool connectedN(Network net, Id id1, Id id2) {

    return (ultimo(net, id1) == ultimo(net, id2));

}


void connectN(Network net, Id id1, Id id2) {

Id ultimoId1 = ultimo(net, id1);
Id ultimoId2 = ultimo(net, id2);
                                if (!connectedN(net, ultimoId1, ultimoId2)) {
                                                                            insertM(net->flechas, ultimoId1, ultimoId2);
                                                                            pushS(net->acciones, ultimoId1);
                                                                            }
}


void undoN(Network net) {

int ultiAcc = topS(net->acciones);
Value v;

    lookupM(net->flechas, ultiAcc, v);
    popS(net->acciones);
                        if (v == ultiAcc) {
                                            removeM(net->flechas, ultiAcc);
                                          }
                        else              {
                                            insertM(net->flechas, ultiAcc, ultiAcc);
                                          }

}


void destroyN(Network net) {
    destroyM(net->flechas);
    destroyS(net->acciones);
    delete net;
}
