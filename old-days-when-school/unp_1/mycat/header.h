#include "myunp.h"


int my_open(const char *pathname, int mode);

ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);

ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sendfd);
