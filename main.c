#include "arbolesADT.h"
#include "manejoArch.h"

#ifdef VAN
#define MAX_COLS 16
#define COL_HOOD 13
#define COL_STREET 12
#define COL_TREENAME 7
#define COL_DIAM 16
#endif

#ifdef BUE
#define MAX_COLS 12 
#define COL_HOOD  3
#define COL_STREET 5
#define COL_TREENAME 8
#define COL_DIAM 12
#endif



int main (int args, const char * argv[]) {
   
    #if !defined BUE && !defined VAN
        return ERROR_DEF;
    #endif

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

    error = leerArboles(treesFile,adt,MAX_COLS,COL_HOOD,COL_STREET,COL_TREENAME,COL_DIAM);
    if (error)
        return error;


    error=resolverQuerys(adt);
    if (error)
      return error;

    freeADT(adt);
    return 0;
}
