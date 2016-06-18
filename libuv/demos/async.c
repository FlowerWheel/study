
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "uv.h"
#include "common.h"

void async_cb(uv_async_t *handle) {
    static int times = 0;
    char buf[128];
    sprintf(buf, "async_callback call times: %d\n", ++times);
    echo(buf);
    sleep(1);
    uv_async_send(handle);
}

void prepare_cb(uv_prepare_t *handle){
    static int times = 0;
    char buf[128];
    sprintf(buf, "prepare_callback call times: %d\n", ++times);
    echo(buf);
}

void check_cb(uv_check_t *handle){
    static int times = 0;
    char buf[128];
    sprintf(buf, "check_callback call times: %d\n", ++times);
    echo(buf);
}

void idle_cb(uv_idle_t *handle){
    static int times = 0;
    char buf[128];
    sprintf(buf, "idle_callback call times: %d\n", ++times);
    echo(buf);
}

void timer_cb(uv_timer_t *handle){
    static int times = 0;
    char buf[128];
    sprintf(buf, "timer_callback call times: %d\n", ++times);
    echo(buf);
}

void _timer_cb(uv_timer_t *handle) {
//    CB("timer", (uv_handle_t*)handle);
}

int main(int argc, char **argv){
    echo("async_demo\n\n");

    uv_loop_t *loop = uv_default_loop();


    uv_idle_t idleHandle;

    uv_idle_init(loop, &idleHandle);

    uv_idle_start(&idleHandle, idle_cb);


    uv_prepare_t prepareHandle;

    uv_prepare_init(loop, &prepareHandle);

    uv_prepare_start(&prepareHandle, prepare_cb);


    uv_check_t checkHandle;

    uv_check_init(loop, &checkHandle);

    uv_check_start(&checkHandle, check_cb);


    uv_timer_t timerHandle;

    uv_timer_init(loop, &timerHandle);

    uv_timer_start(&timerHandle, timer_cb, 1000, 1000);


    uv_async_t asyncHandle;

    uv_async_init(loop, &asyncHandle, async_cb);

    /**
     *
     * Note:
     * It’s safe to call this function from any thread. The callback will be called on the loop thread.
     *
     * Warning:
     * libuv will coalesce calls to uv_async_send(), that is, not every call to it will yield an execution of the callback.
     * For example: if uv_async_send() is called 5 times in a row before the callback is called, the callback will only be called once.
     * If uv_async_send() is called again after the callback was called, it will be called again.
     */
    uv_async_send(&asyncHandle);
    uv_async_send(&asyncHandle);
    uv_async_send(&asyncHandle);

    uv_run(loop, UV_RUN_DEFAULT);

    return 0;
}

