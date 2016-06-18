#include "common.h"

#define CB (name, uv_handle_t *h) {                                 \
    do {                                                            \
    static int times = 0;                                           \
    char buf[128];                                                  \
    sprintf(buf, "%s_callback call times: %d\n", name, ++times);    \
    echo(buf);                                                      \
    } while(0)                                                      \
}

void echo(char *string){
    write(STDOUT_FILENO, string, strlen(string));
}


