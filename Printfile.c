#include "function.h"

void InfixprintAVL(pAvl node, FILE *file) {
    if (node != NULL){
        InfixprintAVL(node->pLeft, file);
        fprintf(file,"%d:%ld:%ld\n", node->id, node->capa, node->load);
        InfixprintAVL(node->pRight, file);
        
    }
}


void PrintToFile(pAvl tree, int Lv, int Hva, int Hvb) {
    FILE *file;
    file = fopen("data.csv", "w+");
    if (file == NULL) {
        exit(12);
    }
    if (Lv) {
        fprintf(file, "LV : Capacity: Consommation\n");
    }
    if (Hva) {
        fprintf(file, "HVA : Capacity: Consommation\n");
    }
    if (Hvb) {
        fprintf(file, "HVB : Capacity: Consommation\n");
    }
    InfixprintAVL(tree, file);
    fclose(file);

}
