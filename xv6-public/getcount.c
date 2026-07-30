#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[]) {
    char *call = argv[1];
    
    /*If r is passed as second argument, reset the counter of that system call and exit with out printing */
    if (argc > 2 && (strcmp(argv[2], "r")) == 0) { 
        resetcount(call);
        exit();
    }

    /* when program is called "> getcounts <call-name> <r>" calls the correct counter and resets when needed */
    if ((strcmp(argv[1], "read")) == 0) {
        printf(1, "read count: %d\n", getreadcount());
    }
    if ((strcmp(argv[1], "write")) == 0) {
        printf(1, "write count: %d\n", getwritecount());
    }
    if ((strcmp(argv[1], "open")) == 0) {
        printf(1, "open count: %d\n", getopencount());
    }
    if ((strcmp(argv[1], "close")) == 0) {
        printf(1, "close count: %d\n", getclosecount());
    }
    if ((strcmp(argv[1], "mkdir")) == 0) {
        printf(1, "mkdir count: %d\n", getmkdircount());
    }
    
    exit();
}