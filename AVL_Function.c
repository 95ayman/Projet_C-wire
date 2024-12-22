#include "function.h"



int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max3(int a, int b, int c) {
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}


int min3(int a, int b, int c) {
    return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
}

pAvl createNode(){
    pAvl pNew = malloc(sizeof(Avl));
    if (pNew==NULL){
        exit(1);
           }
    pNew->eq = 0;
    pNew->capa = 0;
    pNew->id = 0;
    pNew->load = 0;
    pNew->pLeft = NULL;
    pNew->pRight = NULL;
    return pNew;
}

pAvl createAVL(long  c, int id){
    pAvl pNew = createNode();
    
    pNew->id = id;
    pNew->capa = c;
    return pNew;
}



pAvl rotateRight(pAvl node) {
    pAvl pivot = node->pLeft;
    int eq_node = node->eq, eq_pivot = pivot->eq;
    

    node->pLeft = pivot->pRight;
    pivot->pRight = node;

    node->eq = eq_node - min(eq_pivot, 0) + 1;
    pivot->eq = max3(eq_node + 2, eq_node + eq_pivot + 2, eq_pivot + 1);

    return pivot;

}


pAvl rotateLeft(pAvl node) {
    pAvl pivot = node->pRight;
    int eq_node = node->eq, eq_pivot = pivot->eq;
   

    node->pRight = pivot->pLeft;
    pivot->pLeft = node;

    node->eq = eq_node - max(eq_pivot, 0) - 1;
    pivot->eq = min3(eq_node - 2, eq_node + eq_pivot - 2, eq_pivot - 1);

    return pivot;

}



pAvl doubleRotateLeft(pAvl node){
    node->pRight = rotateRight(node->pRight);
    return rotateLeft(node);
}

pAvl doubleRotateRight(pAvl node){
    node->pLeft = rotateLeft(node->pLeft);
    return rotateRight(node);
}

pAvl balanceAVL(pAvl node){
    if(node->eq >= 2){
        if(node->pRight->eq >= 0){
            return rotateLeft(node);
        }else{
            return doubleRotateLeft(node);
        }
    }else if(node->eq <= -2){
        if(node->pLeft->eq <= 0){
            return rotateRight(node);
        }else{
            return doubleRotateRight(node);
        }
    }
    return node;
}
int searchAVL(pAvl node, int id, pAvl *a) {
    if (node == NULL) { 
        *a = node;
        return 0;
    }
    if (node->id == id) { 
        *a = node;
        return 1;
    }
    if (id < node->id) {
        return searchAVL(node->pLeft, id, a);
    } else {
        return searchAVL(node->pRight, id, a);
    }
}


pAvl insertAVL(pAvl node, long capa, int *h, int id){
    if(node==NULL){ 
        *h = 1;
        return createAVL(capa, id);
    }else if(id < node->id){
        node->pLeft = insertAVL(node->pLeft, capa, h, id);
        *h = -*h;
    }else if(id > node->id){
        node->pRight = insertAVL(node->pRight, capa, h, id);
    }else{
        node->capa = capa; 
        *h = 0;
        return node;
    }

    if(*h != 0){
        node->eq += *h;
        node=balanceAVL(node);
        if(node->eq == 0){
            *h = 0;
        }else{
            *h = 1;
        }
    }
    return node;
}

/* void Free(pAvl node){
    if(node != NULL){
        Free(node->pLeft);
        Free(node->pRight);
        Free(node);
    }
}

*/
