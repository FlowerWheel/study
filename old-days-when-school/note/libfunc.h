/*
 * SYSTEM LIMIT
 */
#include <unistd.h>
long sysconf(int name);
long fpathconf(int fd,  int name);
long pathconf(char *path,  int name);


/*
 * ERROR HANDLE
 */
#include <errno.h>
const char *sys_errlist[];
int sys_nerr;
int errno;

#include <string.h>
char *strerror(int errnum);
int   strerror_r(int errnum,  char *buf,  size_t buflen);/* XSI-compliant */
char *strerror_r(int errnum,  char *buf,  size_t buflen);/* GNU-specific */

#include <stdio.h>
void perror(const char *s);


/*
 * SYSIO
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int open(const char *pathname,  int flags);
int open(const char *pathname,  int flags,  mode_t mode);
int creat(const char *pathname,  mode_t mode);

#include <unistd.h>
int close(int fd);

#include <sys/types.h>
#include <unistd.h>
off_t lseek(int fd,  off_t offset,  int whence);

#include <unistd.h>
ssize_t read(int fildes,  void *buf,  size_t nbyte);
ssize_t pread(int fildes,  void *buf,  size_t nbyte,  off_t offset);/*Elementory do*/

#include <unistd.h>
ssize_t write(int fildes,  const void *buf,  size_t nbyte);
ssize_t pwrite(int fildes,  const void *buf,  size_t nbyte,	off_t offset);/*Elementory do*/

#include <unistd.h>
int dup(int fildes);
int dup2(int fildes,  int fildes2);

#include <unistd.h>
void sync(void);
int  fsync(int fildes);
int  fdatasync(int fildes);

#include <unistd.h>
#include <fcntl.h>
int fcntl(int fildes,  int cmd,  ...);

#include <stropts.h>
int ioctl(int fildes,  int request,  ... /* arg */);


/*
 * FILE SYSTEM
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int stat(const char *path,  struct stat *buf);
int fstat(int fd,  struct stat *buf);
int lstat(const char *path,  struct stat *buf);

#include <unistd.h>
int access(const char *pathname,  int mode);

#include <sys/stat.h>
mode_t umask(mode_t cmask);

#include <sys/stat.h>
int chmod(const char *path,  mode_t mode);
int fchmod(int fildes,  mode_t mode);

#include <unistd.h>
int chown(const char *path,  uid_t owner,  gid_t group);
int fchown(int fildes,  uid_t owner,  gid_t group);
int lchown(const char *path,  uid_t owner,  gid_t group);

#include <unistd.h>
int truncate(const char *path,  off_t length);
int ftruncate(int fildes,  off_t length);

#include <unistd.h>
int link(const char *path1,  const char *path2);
int unlink(const char *path);

#include <stdio.h>
int remove(const char *pathname);
int rename(const char *old,  const char *new);

#include <unistd.h>
int     symlink(const char *path1,  const char *path2);
ssize_t readlink(const char *restrict path,  char *restrict buf, size_t bufsize);

#include <utime.h>
int utime(const char *path,  const struct utimbuf *times);

#include <sys/stat.h>
int mkdir(const char *path,  mode_t mode);

#include <unistd.h>
int rmdir(const char *path);

#include <sys/types.h>
#include <dirent.h>
DIR *opendir(const char *name);
DIR *fdopendir(int fd);

#include <dirent.h>
struct dirent *readdir(DIR *dirp);
int readdir_r(DIR *dirp,  struct dirent *entry,  struct dirent **result);

#include <sys/types.h>
#include <dirent.h>
int closedir(DIR *dirp);

#include <dirent.h>
long telldir(DIR *dirp);

#include <dirent.h>
void seekdir(DIR *dirp,  long offset);

#include <unistd.h>
int chdir(const char *path);

#include <unistd.h>
int fchdir(int fildes);

#include <unistd.h>
char *getcwd(char *buf,  size_t size);
char *getwd(char *buf);
char *get_current_dir_name(void);

#include <ftw.h>
int ftw(const char *dirpath, int (*fn) (const char *fpath, const struct stat *sb, int typeflag), int nopenfd);
int nftw(const char *dirpath, int (*fn) (const char *fpath, const struct stat *sb, int typeflag,  struct FTW *ftwbuf), int nopenfd,  int flags);


/*
 * STDIO
 */
#include <wchar.h>
int fwide(FILE *stream,  int mode);

#include <stdio.h>
void setbuf(FILE *stream,  char *buf);
void setbuffer(FILE *stream,  char *buf,  size_t size);
void setlinebuf(FILE *stream);
int  setvbuf(FILE *stream,  char *buf,  int mode,  size_t size);

FILE *fopen(const char *path,  const char *mode);
FILE *fdopen(int fd,  const char *mode);
FILE *freopen(const char *path,  const char *mode,  FILE *stream);

int fileno(FILE *stream);
int fclose(FILE *fp);

int   getchar(void);
int   getc(FILE *stream);
int   fgetc(FILE *stream);
char *fgets(char *s,  int size,  FILE *stream);
char *gets(char *s);

int   ungetc(int c,  FILE *stream);

int putchar(int c);
int putc(int c,  FILE *stream);
int fputc(int c,  FILE *stream);
int fputs(const char *s,  FILE *stream);
int puts(const char *s);

size_t fread(void *ptr,  size_t size,  size_t nmemb,  FILE *stream);
size_t fwrite(const void *ptr,  size_t size,  size_t nmemb,	FILE *stream);

void clearerr(FILE *stream);
int  feof(FILE *stream);
int  ferror(FILE *stream);

int	  fseek(FILE *stream,  long offset,  int whence);
long  ftell(FILE *stream);
void  rewind(FILE *stream);
int   fseeko(FILE *stream,  off_t offset,  int whence);
off_t ftello(FILE *stream);

int fgetpos(FILE *stream,  fpos_t *pos);
int fsetpos(FILE *stream,  fpos_t *pos);

#include <stdarg.h>
int printf(const char *format,  ...);
int fprintf(FILE *stream,  const char *format,  ...);
int sprintf(char *str,  const char *format,  ...);
int snprintf(char *str,  size_t size,  const char *format,  ...);
int vprintf(const char *format,  va_list ap);
int vfprintf(FILE *stream,  const char *format,  va_list ap);
int vsprintf(char *str,  const char *format,  va_list ap);
int vsnprintf(char *str,  size_t size,  const char *format,  va_list ap);

#include <stdarg.h>
int scanf(const char *format,  ...);
int fscanf(FILE *stream,  const char *format,  ...);
int sscanf(const char *str,  const char *format,  ...);
int vscanf(const char *format,  va_list ap);
int vsscanf(const char *str,  const char *format,  va_list ap);
int vfscanf(FILE *stream,  const char *format,  va_list ap);

char *tmpnam(char *s);
FILE *tmpfile(void);
char *tempnam(const char *dir,  const char *pfx);

int mkstemp(char *template);
int mkostemp(char *template,  int flags);
int mkstemps(char *template,  int suffixlen);
int mkostemps(char *template,  int suffixlen,  int flags);


/*
 * SYSINFO
 */
#include <sys/types.h>
#include <pwd.h>
void setpwent(void);
struct passwd *getpwent(void);
void endpwent(void);

struct passwd *getpwnam(const char *name);
struct passwd *getpwuid(uid_t uid);
int getpwnam_r(const char *name,  struct passwd *pwd, char *buf,  size_t buflen,  struct passwd **result);
int getpwuid_r(uid_t uid,  struct passwd *pwd, char *buf,  size_t buflen,  struct passwd **result);

#include <shadow.h>
void setspent(void);
struct spwd *getspent(void);
void endspent(void);

struct spwd *getspnam(const char *name);
struct spwd *fgetspent(FILE *fp);
struct spwd *sgetspent(const char *s);

int putspent(struct spwd *p,  FILE *fp);

int lckpwdf(void);
int ulckpwdf(void);

/* GNU extension */
int getspent_r(struct spwd *spbuf, char *buf, size_t buflen, struct spwd **spbufp);
int getspnam_r(const char *name,  struct spwd *spbuf, char *buf, size_t buflen, struct spwd **spbufp);
int fgetspent_r(FILE *fp, struct spwd *spbuf, char *buf, size_t buflen, struct spwd **spbufp);
int sgetspent_r(const char *s, struct spwd *spbuf, char *buf, size_t buflen, struct spwd **spbufp);

#include <sys/types.h>
#include <grp.h>
void setgrent(void);
struct group *getgrent(void);
void endgrent(void);

struct group *getgrnam(const char *name);
struct group *getgrgid(gid_t gid);

int getgrnam_r(const char *name, struct group *grp, char *buf, size_t buflen, struct group **result);
int getgrgid_r(gid_t gid, struct group *grp, char *buf, size_t buflen, struct group **result);

#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
int getgroups(int size,  gid_t list[]);
int setgroups(size_t size,  const gid_t *list);
int initgroups(const char *user,  gid_t group);

#include <pwd.h>	struct passwd	/etc/passwd
#include <grp.h>	struct group	/etc/group
#include <shadow.h>	struct spwd		/etc/shadow 
#include <netdb.h>	struct hostent	/etc/hosts
#include <netdb.h>	struct netent	/etc/networks
#include <netdb.h>	struct protoent /etc/protocols
#include <netdb.h>	struct servent	/etc/services
#include <>			struct utmp		/var/run/utmp
#include <>			struct wtmp		/var/log/wtmp

#include <sys/utsname.h>
int uname(struct utsname *buf);

#include <sys/time.h>
int gettimeofday(struct timeval *tv,  struct timezone *tz);
int settimeofday(const struct timeval *tv,  const struct timezone *tz);

#include <time.h>
time_t time(time_t *t);

char *asctime(const struct tm *tm);
char *asctime_r(const struct tm *tm,  char *buf);

char *ctime(const time_t *timep);
char *ctime_r(const time_t *timep,  char *buf);

struct tm *gmtime(const time_t *timep);
struct tm *gmtime_r(const time_t *timep,  struct tm *result);

struct tm *localtime(const time_t *timep);
struct tm *localtime_r(const time_t *timep,  struct tm *result);

time_t mktime(struct tm *tm);

#include <time.h>
size_t strftime(char *s,  size_t max,  const char *format, const struct tm *tm);


/*
 * PROC ENV
 */
#include <unistd.h>
#include <stdlib.h>
int  main(int argc, char **argv);
void exit(int status);
void _exit(int status);
void _Exit(int status);
int  atexit(void (*function)(void));

#include <stdlib.h>
void *malloc(size_t size);
void *calloc(size_t nmemb,  size_t size);
void *realloc(void *ptr,  size_t size);
void  free(void *ptr);

char *getenv(const char *name);
int   putenv(char *string);
int   setenv(const char *name,  const char *value,  int overwrite);
int   unsetenv(const char *name);

#include <setjmp.h>
int	 setjmp(jmp_buf env);
void longjmp(jmp_buf env,  int val);
int  sigsetjmp(sigjmp_buf env,  int savesigs);
void siglongjmp(sigjmp_buf env,  int val);

#include <sys/time.h>
#include <sys/resource.h>
int getrlimit(int resource,  struct rlimit *rlim);
int setrlimit(int resource,  const struct rlimit *rlim);
int prlimit(pid_t pid,  int resource,  const struct rlimit *new_limit, struct rlimit *old_limit);


/*
 * PROC CONTOL
 */
#include <sys/types.h>
#include <unistd.h>
int setuid(uid_t uid);
int setgid(gid_t gid);
int setreuid(uid_t ruid,  uid_t euid);
int setregid(gid_t rgid,  gid_t egid);
int seteuid(uid_t euid);
int setegid(gid_t egid);

#include <sys/types.h>
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);

#include <unistd.h>
pid_t fork(void);
pid_t vfork(void);

#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *status);
pid_t waitpid(pid_t pid,  int *status,  int options);
int   waitid(idtype_t idtype,  id_t id,  siginfo_t *infop,  int options);

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
pid_t wait3(int *status,  int options, struct rusage *rusage);
pid_t wait4(pid_t pid,  int *status,  int options, struct rusage *rusage);

#include <unistd.h>
extern char **environ;
int execl(const char *path,  const char *arg,  ...);
int execlp(const char *file,  const char *arg,  ...);
int execle(const char *path,  const char *arg, ...,  char * const envp[]);
int execv(const char *path,  char *const argv[]);
int execvp(const char *file,  char *const argv[]);
int execvpe(const char *file,  char *const argv[], char *const envp[]);

#include <stdlib.h>
int system(const char *command);

#include <unistd.h>
int acct(const char *filename);

#include <unistd.h>
char *getlogin(void);
int getlogin_r(char *buf,  size_t bufsize);

#include <stdio.h>
char *cuserid(char *string);

#include <sys/times.h>
clock_t times(struct tms *buf);


/*
 * PROC RELATIONSHIP
 */
#include <unistd.h>
int   setpgid(pid_t pid,  pid_t pgid);
pid_t getpgid(pid_t pid);
int   setpgrp(void);                   /* System V version */
pid_t getpgrp(void);                 /* POSIX.1 version */
int   setpgrp(pid_t pid,  pid_t pgid);  /* BSD version */
pid_t getpgrp(pid_t pid);            /* BSD version */

pid_t setsid(void);
pid_t getsid(pid_t pid);

#include <termios.h>
pid_t tcgetsid(int fd);


/*
 * SIGNAL HANDLE
 */
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum,  sighandler_t handler);
#include <sys/types.h>
int kill(pid_t pid,  int sig);
int raise(int sig);
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
int pause(void);

int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set,  int signum);
int sigdelset(sigset_t *set,  int signum);
int sigismember(const sigset_t *set,  int signum);

int sigvec(int sig,  struct sigvec *vec,  struct sigvec *ovec);
int sigmask(int signum);
int sigblock(int mask);
int sigsetmask(int mask);
int siggetmask(void);

int sigprocmask(int how,  const sigset_t *set,  sigset_t *oldset);
int sigaction(int signum,  const struct sigaction *act, struct sigaction *oldact);

#include <setjmp.h>
void siglongjmp(sigjmp_buf env,  int val);
int	 sigsetjmp(sigjmp_buf env,  int savesigs);
int  sigsuspend(const sigset_t *mask);

#include <stdlib.h>
void abort(void);
int  system(const char *command);

#include <unistd.h>
unsigned int sleep(unsigned int seconds);

void psignal(int sig,  const char *s);
void psiginfo(const siginfo_t *pinfo,  const char *s);

#include <string.h>
char *strsignal(int sig);
extern const char * const sys_siglist[];

int sigwaitinfo(const sigset_t *set,  siginfo_t *info);
int sigtimedwait(const sigset_t *set,  siginfo_t *info, const struct timespec *timeout);
int sigwait(const sigset_t *set,  int *sig);

#include <sys/signalfd.h>
int signalfd(int fd,  const sigset_t *mask,  int flags);


/*
 * TERM ADDR
 */
#include <termios.h>
#include <unistd.h>
int tcgetattr(int fd,  struct termios *termios_p);
int tcsetattr(int fd,  int optional_actions, const struct termios *termios_p);
int tcsendbreak(int fd,  int duration);
int tcdrain(int fd);
int tcflush(int fd,  int queue_selector);
int tcflow(int fd,  int action);

speed_t cfgetispeed(const struct termios *termios_p);
speed_t cfgetospeed(const struct termios *termios_p);

void cfmakeraw(struct termios *termios_p);
int cfsetispeed(struct termios *termios_p,  speed_t speed);
int cfsetospeed(struct termios *termios_p,  speed_t speed);
int cfsetspeed(struct termios *termios_p,  speed_t speed);


/*
 * SOCKET API
 */


/*
 * IPC API
 */

/*PIPE*/
#include <unistd.h>
int pipe(int pipefd[2]);
int pipe2(int pipefd[2],  int flags);

#include <stdio.h>
FILE *popen(const char *command,  const char *type);
int   pclose(FILE *stream);

/*FIFO*/
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char *pathname,  mode_t mode);

/*PXMQ*/
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
mqd_t mq_open(const char *name,  int oflag);
mqd_t mq_open(const char *name,  int oflag,  mode_t mode, struct mq_attr *attr);

int mq_close(mqd_t mqdes);
int mq_unlink(const char *name);
int mq_getattr(mqd_t mqdes,  struct mq_attr *attr);
int mq_setattr(mqd_t mqdes,  struct mq_attr *newattr, struct mq_attr *oldattr);
int mq_send(mqd_t mqdes,  const char *msg_ptr, size_t msg_len,  unsigned msg_prio);
int mq_timedsend(mqd_t mqdes,  const char *msg_ptr, size_t msg_len,  unsigned msg_prio, const struct timespec *abs_timeout);
int mq_notify(mqd_t mqdes,  const struct sigevent *sevp);

ssize_t mq_receive(mqd_t mqdes,  char *msg_ptr, size_t msg_len,  unsigned *msg_prio);
ssize_t mq_timedreceive(mqd_t mqdes,  char *msg_ptr, size_t msg_len,  unsigned *msg_prio, const struct timespec *abs_timeout);


/*SVMQ*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int msgget(key_t key,  int msgflg);
int msgctl(int msqid,  int cmd,  struct msqid_ds *buf);
int msgsnd(int msqid,  const void *msgp,  size_t msgsz,  int msgflg);
ssize_t msgrcv(int msqid,  void *msgp,  size_t msgsz,  long msgtyp, int msgflg);

/*MUTEX*/
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timespec *restrict abs_timeout);
int pthread_mutex_getprioceiling(const pthread_mutex_t *restrict mutex, int *restrict prioceiling);
int pthread_mutex_setprioceiling(pthread_mutex_t *restrict mutex, int prioceiling,  int *restrict old_ceiling);
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *restrict attr,  int *restrict prioceiling);
int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int prioceiling);
int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *restrict attr,  int *restrict protocol);
int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol);
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr,  int *restrict pshared);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict attr, int *restrict type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr,  int type);

/*COND*/
#include <pthread.h>
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_condattr_init(pthread_condattr_t *attr);
int pthread_condattr_destroy(pthread_condattr_t *attr);
int pthread_condattr_getclock(const pthread_condattr_t *restrict attr, clockid_t *restrict clock_id);
int pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);
int pthread_condattr_getpshared(const pthread_condattr_t  *restrict attr, int *restrict pshared);
int pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared);

/*RWLOCK*/
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict abs_timeout);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict abs_timeout);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr,  int *restrict pshared);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared);

/*RECORD LOCK fcntl(SETLK|SETLKW|GETLK)*/

/*PXSEM*/
#include <semaphore.h>
sem_t *sem_open(const char *name,  int oflag);
sem_t *sem_open(const char *name,  int oflag, mode_t mode,  unsigned int value);

int sem_init(sem_t *sem,  int pshared,  unsigned int value);
int sem_destroy(sem_t *sem);
int sem_getvalue(sem_t *sem,  int *sval);
int sem_post(sem_t *sem);
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_timedwait(sem_t *sem,  const struct timespec *abs_timeout);
int sem_close(sem_t *sem);
int sem_unlink(const char *name);

/*SVSEM*/
#include <sys/ipc.h>
#include <sys/sem.h>
int semget(key_t key,  int nsems,  int semflg);
int semop(int semid,  struct sembuf *sops,  unsigned nsops);
int semtimedop(int semid,  struct sembuf *sops,  unsigned nsops, struct timespec *timeout);
int semctl(int semid,  int semnum,  int cmd,  ...);

/*SHM*/
#include <sys/mman.h>
void *mmap(void *addr,  size_t length,  int prot,  int flags, int fd,  off_t offset);
int   munmap(void *addr,  size_t length);
int   msync(void *addr,  size_t length,  int flags);

/*PXSHM*/
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
int shm_open(const char *name,  int oflag,  mode_t mode);
int shm_unlink(const char *name);

/*SVSHM*/
#include <sys/ipc.h>
#include <sys/shm.h>
int   shmget(key_t key,  size_t size,  int shmflg);
void *shmat(int shmid,  const void *shmaddr,  int shmflg);
int   shmdt(const void *shmaddr);
int   shmctl(int shmid,  int cmd,  struct shmid_ds *buf);

/*THE END*/
