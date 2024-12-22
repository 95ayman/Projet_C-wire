#include "function.h"



int main(int argc, char *argv[]){
    int Lv = 0; 
    int Hva = 0;
    int Hvb = 0;
    char *filename = "tmp/tmp.dat";
    
    pAvl tree = NULL;

    if (strcmp("lv", argv[1])==0){
        Lv = 1;
    }else if (strcmp("hva", argv[1])==0){
        Hva = 1;
    }else if (strcmp("hvb", argv[1])==0){
        Hvb = 1;
    }
    else{
        exit(1);
    }

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
    exit(1);
    }
    tree = Filterdata(tree, file, Lv, Hva, Hvb);
    PrintToFile(tree, Lv, Hva, Hvb);

    return 0;
}
