#include "arbolesADT.h"
#include "manejoArch.h"

#define MAX_COLS_VA 16

#define COL_HOOD_VA 13
#define COL_STREET_VA 12
#define COL_TREENAME_VA 7
#define COL_DIAM_VA 16


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

    error = leerArboles(treesFile,adt,MAX_COLS_VA,COL_HOOD_VA,COL_STREET_VA,COL_TREENAME_VA,COL_DIAM_VA);
    if (error)
        return error;

    error=resolverQuerys(adt);
    if (error)
      return error;
    
    freeADT(adt);
    return 0;

}

