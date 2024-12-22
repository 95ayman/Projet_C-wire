#include "function.h"

pAvl addLoad(pAvl tree, int id, long load) {
    pAvl station;
    int h = 0;

    if (!searchAVL(tree, id, &station)) {
        tree = insertAVL(tree, 0, &h, id);
    } else {
        station->load += load;
    }

    return tree;
}



pAvl buildTree(pAvl tree, int Lv, int Hva, int Hvb, char *strhvb, char *strhva, char *strlv, char *strcomp, char *strindiv, char *strcapa, char *strload) {
    int heightDiff = 0;

    if (Lv) {
        if (strhva && strcmp(strhva, "-") != 0) {
            long capa = atol(strcapa);
            int lvId = atoi(strlv);
            tree = insertAVL(tree, capa, &heightDiff, lvId);
        } else {
            int lvId = atoi(strlv);
            long load = atol(strload);
            tree = addLoad(tree, lvId, load);
        }
    } else if (Hva) {
        if ((strcomp && strcmp(strcomp, "-") != 0) || (strindiv && strcmp(strindiv, "-") != 0)) {
            int hvaId = atoi(strhva);
            long load = atol(strload);
            tree = addLoad(tree, hvaId, load);
        } else if (strlv && strcmp(strlv, "-") != 0) {
            long capa = atol(strcapa);
            int hvaId = atoi(strhva);
            tree = insertAVL(tree, capa, &heightDiff, hvaId);
        } else {
            int hvaId = atoi(strhva);
            long capa = atol(strcapa);
            tree = addLoad(tree, hvaId, capa);
        }
    } else if (Hvb) {
        if ((strcomp && strcmp(strcomp, "-") != 0) || (strindiv && strcmp(strindiv, "-") != 0)) {
            int hvbId = atoi(strhvb);
            long load = atol(strload);
            tree = addLoad(tree, hvbId, load);
        } else if (strhva && strcmp(strhva, "-") != 0) {
            long capa = atol(strcapa);
            int hvbId = atoi(strhvb);
            tree = insertAVL(tree, capa, &heightDiff, hvbId);
        } else {
            int hvbId = atoi(strhvb);
            long capa = atol(strcapa);
            tree = addLoad(tree, hvbId, capa);
        }
    }

    return tree;
}





pAvl Filterdata(pAvl tree, FILE *file, int Lv, int Hva, int Hvb) {
    char *tokens[8];
    char line[500];
    rewind(file);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';

        tokens[0] = strtok(line, ";");
        for (int i = 1; i < 8; ++i) {
            tokens[i] = strtok(NULL, ";");
        }

        tree = buildTree(tree, Lv, Hva, Hvb, tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], tokens[7]);
    }

    return tree;
}

