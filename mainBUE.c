#include "arbolesADT.h"
#include "manejoArch.h"

#define MAX_COLS_BA 12 

#define COL_HOOD_BA 3
#define COL_STREET_BA 5
#define COL_TREENAME_BA 8
#define COL_DIAM_BA 12


int main (int args, const char * argv[]) {

    int error = chequearArgs(args);
    if (error)
        return error;

    FILE * hoodsFile;
    FILE * treesFile;
    error = abrirArchivos(&treesFile,&hoodsFile,argv);
    if (error)
        return error;

    arbolesADT adt = nuevaData();

    error = leerBarrios(hoodsFile,adt);
    if (error)
        return error;

    error = leerArboles(treesFile,adt,MAX_COLS_BA,COL_HOOD_BA,COL_STREET_BA,COL_TREENAME_BA,COL_DIAM_BA);
    if (error)
        return error;


    error=resolverQuerys(adt);
    if (error)
      return error;

    freeADT(adt);
    return 0;
}
