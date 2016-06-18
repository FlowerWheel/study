#include<stdio.h>
#include<uv.h>

void cb(uv_prepare_t *prepare){
    printf("I'm prepare cb function");
}

int main () {
    uv_prepare_t *prepare;

    uv_prepare_init(uv_default_loop(), prepare);

    uv_prepare_start(prepare, cb);

    // uv_prepare_stop();

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}
