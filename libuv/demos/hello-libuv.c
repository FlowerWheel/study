
#include<uv.h>
#include<stdio.h>

int main (int argc, char **argv) {

    uv_loop_t *loop = uv_default_loop();

    //uv_loop_init(loop);

    printf("hello libuv\n");

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}


