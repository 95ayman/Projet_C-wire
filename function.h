#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Avl{
    struct Avl* pLeft;
    struct Avl* pRight;
    int eq;
    long capa;
    int id;
    long load;
}Avl,*pAvl;


int max(int a, int b);
int min(int a, int b);
int max3(int a, int b, int c);
int min3(int a, int b, int c);


pAvl createNode();
pAvl createTree(long  capacity, int id);
pAvl rotateRight(pAvl node);
pAvl rotateLeft(pAvl node);
pAvl doubleLeft(pAvl node);
pAvl doubleRight(pAvl node);
pAvl balanceNode(pAvl node);
int searchAVL(pAvl node, int id, pAvl* searched);
void printAVL(pAvl node);
pAvl buildAvl(pAvl tree, int Lv, int Hva, int Hvb, char *strhvb, char *strhva,char *strlv, char *strcomp, char *strindiv, char *strcapa, char *strload);
pAvl insertAVL(pAvl node,  long capacity, int *h, int id);
void InfixAVL(pAvl node, FILE* file);
void Free(pAvl node);


pAvl addLoad(pAvl tree, int id,  long load);
pAvl processData(pAvl tree, FILE* file,int Lv, int Hva, int Hvb);
void PrintToFile(pAvl tree, int Lv, int Hva, int Hvb);
pAvl Filterdata(pAvl tree, FILE *file, int Lv, int Hva, int Hvb);

#endif 

