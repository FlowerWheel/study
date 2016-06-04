linux 系统库函数 (2010-08-12 17:36:04)转载▼
标签： 杂谈	分类： Linux
第1章 字符测试函数
isalnum(测试字符是否为英文字母或数字)
isalpha(测试字符是否为英文字母)
isascii(测试字符是否为ASCII码字符)
isblank(测试字符是否为空格字符)
iscntrl(测试字符是否为ASCII码的控制字符)
isdigit(测试字符是否为阿拉伯数字)
isgraph(测试字符是否为可打印字符)
islower(测试字符是否为小写英文字母)
isprint(测试字符是否为可打印字符)
isspace(测试字符是否为空格字符)
ispunct(测试字符是否为标点符号或特殊符号)
isupper(测试字符是否为大写英文字母)
isxdigit(测试字符是否为16进制数字)
第2章 数据转换函数
atof(将字符串转换成浮点型数)
atoi(将字符串转换成整型数)
atol(将字符串转换成长整型数)
ecvt(将浮点型数转换成字符串，取四舍五入)
fcvt(将浮点型数转换为字符串，取四舍五入)
gcvt(将浮点型数转换为字符串，取四舍五入)
strtod(将字符串转换成浮点型数)
strtol(将字符串转换成长整型数)
strtoul(将字符串转换成无符号长整型数)
toascii(将整型数转换成合法的ASCII码字符)
tolower(将大写字母转换成小写字母)
toupper(将小写字母转换成大写字母)
第3章 内存配置函数
alloca(配置内存空间)
brk(改变数据字节的范围)
calloc(配置内存空间)
free(释放原先配置的内存)
getpagesize(取得内存分页大小)
malloc(配置内存空间)
mmap(建立内存映射)
munmap(解除内存映射)
realloc(更改己配置的内存空间)
sbrk(增加程序可用的数据空间)
第4章 时间函数
asctime(将时间和日期以字符串格式表示)
clock(取得进程占用CPU的大约时间)
ctime(将时间和日期以字符串格式表示)
difftime(计算时间差距)
ftime(取得目前的时间和日期)
gettimeofday(取得目前的时间)
gmtime(取得目前的时间和日期)
localtime(取得当地目前的时间和日期)
mktime(将时间结构数据转换成经过的秒数)
settimeofday(设置目前的时间)
strftime(格式化日期和时间)
time(取得目前的时间)
tzset(设置时区以供时间转换)
第5章 字符串处理函数
bcmp(比较内存内容)
bcopy(拷贝内存内容)
bzero(将一段内存内容全清为零)
ffs(在一整型数中查找第一个值为真的位)
index(查找字符串中第一个出现的指定字符)
memccpy(拷贝内存内容)
memchr(在某一内存范围中查找一特定字符)
memcmp(比较内存内容)
memcpy(拷贝内存内容)
memfrob(对内存区域编码)
memmove(拷贝内存内容)
memset(将一段内存空间填入某值)
rindex(查找字符串中最后一个出现的指定字符)
strcasecmp(忽略大小写比较字符串)
strcat(连接两字符串)
strchr(查找字符串中第一个出现的指定字符)
strcmp(比较字符串)
strcoll(采用目前区域的字符排列次序来比较字符串)
strcpy(拷贝字符串)
strcspn(返回字符串中连续不含指定字符串内容的字符数)
strdup(复制字符串)
strfry(随机重组字符串内的字符)
strlen(返回字符串长度)
strncasecmp(忽略大小写比较字符串)
strncat(连接两字符串)
strncmp(比较字符串)
strncpy(拷贝字符串)
strpbrk(查找字符串中第一个出现的指定字符)
strrchr(查找字符串中最后一个出现的指定字符)
strspn(返回字符串中连续不合指定字符串内容的字符数)
strstr(在一字符串中查找指定的字符串)
strtok(分割字符串)
第6章 数学计算函数
abs(计算整型数的绝对值)
acos(取反余弦函数值)
asin(取反正弦函数值)
atan(取反正切函数值)
atan2(取得反正切函数值)
ceil(取不小于参数的最小整型数)
cos(取余弦函数值)
cosh(取双曲线余弦函数值)
div(取得两整型数相除后的商及余数)
exp(计算指数)
fabs(计算浮点型数的绝对值)
frexp(将浮点型数分为底数与指数)
hypot(计算直角三角形斜边长)
labs(计算长整型数的绝对值)
ldexp(计算2的次方值)
ldiv(取得两长整数相除后的商及余数)
log(计算以e为底的对数值)
log10(计算以10为底的对数值)
modf(将浮点型数分解成整数与小数)
pow(计算次方值)
sin(取正弦函数值)
sinh(取双曲线正弦函数值)
sqrt(计算平方根值)
tan(取正切函数值)
tanh(取双曲线正切函数值)
第7章 用户和组函数
cuserid(取得用户帐号名称)
endgrent(关闭组文件)
endpwent(关闭密码文件)
endutent(关闭utmp文件)
fgetgrent(从指定的文件来读取组格式)
fgetpwent(从指定的文件来读取密码格式)
getegid(取得有效的组识别码)
geteuid(取得有效的用户识别码)
getgid(取得真实的组识别码)
getgrent(从组文件文件中取得帐号的数据)
getgrgid(从组文件中取得指定gid的数据)
getgrnan(从组文件中取得指定组的数据)
getgroups(取得组代码)
getlogin(取得登录的用户帐号名称)
getpw(取得指定用户的密码文件数据)
getpwent(从密码文件中取得帐号的数据)
getpwnam(从密码文件中取得指定帐号的数据)
getpwuid(从密码文件中取得指定uid的数据)
getuid(取得真实的用户识别码)
getutent(从utmp文件中取得帐号登录数据)
getutid(从utmp文件中查找特定的记录)
getutline(从utmp文件中查找特定的记录)
initgroups(初始化组清单)
logwtmp(将一登录数据记录到wtmp文件)
pututline(将utmp记录写入文件)
setegid(设置有效的组识别码)
seteuid(设置有效的用户识别码)
setfsgid(设置文件系统的组识别码)
setfsuid(设置文件系统的用户识别码)
setgid(设置真实的组识别码)
setgrent(从头读取组文件中的组数据)
setgroups(设置组代码)
setpwent(从头读取密码文件中的帐号数据)
setregid(设置真实及有效的组识别码)
setreuid(设置真实及有效的用户识别码)
setuid(设置真实的用户识别码)
setutent(从头读取utmp/文件中的登录数据)
updwtmp(将一登录数据记录到wtmp文件)
utmpname(设置utmp文件路径)
第8章 数据加密函数
crypt(将密码或数据编码)
getpass(取得一密码输入)
第9章 数据结构函数
bsearch(二元搜索)
hcreate(建立哈希表)
hdestory(删除哈希表)
hsearch(哈希表搜索)
insque(加入一项目至队列中)
lfind(线性搜索)
lsearch(线性搜索)
qsort(利用快速排序法排列数组)
rremque(从队列中删除一项目)
tdelete(从二叉树中删除数据)
tfind(搜索二叉树)
tsearch(二叉树)
twalk(走访二叉树)
第10章 随机数函数
drand48(产生一个正的浮点型随机数)
erand48(产生一个正的浮点型随机数)
initstate(建立随机数状态数组)
jrand48(产生一个长整型数随机数)
lcong48(设置48位运算的随机数种子)
lrand48(产生一个正的长整型随机数)
mrand48(产生一个长整型随机数)
nrand48(产生一个正的长整型随机数)
rand(产生随机数)
random(产生随机数)
seed48(设置48位运算的随机数种子)
setstate(建立随机数状态数组)
srand(设置随机数种子)
srand48(设置48位运算的随机数种子)
srandom(设置随机数种子)
第11章 初级I／O函数
close(关闭文件)
creat(建立文件)
dup(复制文件描述词)
dup2(复制文件描述词)
fcntl(文件描述词操作)
flock(锁定文件或解除锁定)
fsync(将缓冲区数据写回磁盘)
lseek(移动文件的读写位置)
mkstemp(建立唯一的临时文件)
open(打开文件)
read(由己打开的文件读取数据)
sync(将缓冲区数据写回磁盘)
write(将数据写入已打开的文件内)
第12章 标准I／O函数
clearerr(清除文件流的错误旗标)
fclose(关闭文件)
fdopen(将文件描述词转为文件指针)
feof(检查文件流是否读到了文件尾)
fflush(更新缓冲区)
fgetc(由文件中读取一个字符)
fgetpos(取得文件流的读取位置)
fgets(由文件中读取一字符串)
fileno(返回文件流所使用的文件描述词)
fopen(打开文件)
fputc(将一指定字符写入文件流中)
fputs(将一指定的字符串写入文件内)
fread(从文件流读取数据)
freopen(打开文件)
fseek(移动文件流的读写位置)
fsetpos(移动文件流的读写位置)
ftell(取得文件流的读取位置)
fwrite(将数据写至文件流)
getc(由文件中读取一个字符)
getchar(由标准输入设备内读进一字符)
gets(由标准输入设备内读进一字符串)
mktemp(产生唯一的临时文件文件名)
putc(将一指定字符写入文件中)
putchar(将指定的字符写到标准输出设备)
puts(将指定的字符串写到标准输出设备)
rewind(重设文件流的读写位置为文件开头)
setbuf(设置文件流的缓冲区)
setbuffer(设置文件流的缓冲区)
setlinebuf(设置文件流为线性缓冲区)
setvbuf(设置文件流的缓冲区)
tmpfile(建立临时文件)
ungetc(将一指定字符写回文件流中)
第13章 进程及流程控制
abort(以异常方式结束进程)
assert(若测试的条件不成立则终止进程)
atexit(设置程序正常结束前调用的函数)
execl(执行文件)
execle(执行文件)
execlp(从PATH环境变量中查找文件并执行)
execv(执行文件)
execve(执行文件)
execvp(执行文件)
exit(正常结束进程)
_exit(结束进程执行)
fork(建立一个新的进程)
getpgid(取得进程组识别码)
getpgrp(取得进程组识别码)
getpid(取得进程识别码)
getppid(取得父进程的进程识别码)
getpriority(取得程序进程执行优先权)
longjmp(跳转到原先setjmp保存的堆栈环境)
nice(改变进程优先顺序)
on＿exit(设置程序正常结束前调用的函数)
ptrace(进程追踪)
setjmp(保存目前堆栈环境)
setpgid(设置进程组识别码)
setpgrp(设置进程组识别码)
setpriority(设置程序进程执行优先权)
siglongjmp(跳转到原先sigsetjmp保存的堆栈环境)
sigsetjmp(保存目前堆栈环境)
system(执行shell命令)
wait(等待子进程中断或结束)
waitpid(等待子进程中断或结束)
第14章 格式化输人输出函数
fprintf(格式化输出数据至文件)
fscanf(格式化字符串输入)
printf(格式化输出数据)
scanf(格式化字符串输入)
snprintf(格式化字符串复制)
sprintf(格式化字符串复制)
sscanf(格式化字符串输入)
vfprintf(格式化输出数据至文件)
vfcanf(格式化字符串输入)
vprintf(格式化输出数据)
vscanf(格式化字符串输入)
vsnprintf(格式化字符串复制)
vsprintf(格式化字符串复制)
vsscanf(格式化字符串输入)
第15章 文件及目录函数
access(判断是否具有存取文件的权限)
alphasort(依字母顺序排序目录结构)
chdir(改变当前的工作目录)
chmod(改变文件的权限)
chown(改变文件的所有者)
chroot(改变根目录)
closedir(关闭目录)
fchdir(改变当前的工作目录)
fchmod(改变文件的权限)
fchown(改变文件的所有者)
fstat(由文件描述词取得文件状态)
ftruncate(改变文件大小)
ftw(遍历目录树)
get_current_dir_name(取得当前的工作目录)
getcwd(取得当前的工作目录)
getwd(取得当前的工作目录)
lchown(改变文件的所有者)
link(建立文件连接)
lstat(由文件描述词取得文件状态)
nftw(遍历目录树)
opendir(打开目录)
readdir(读取目录)
readlink(取得符号连接所指的文件)
realpath(将相对目录路径转换成绝对路径)
remove(删除文件)
rename(更改文件名称或位置)
rewinddir(重设读取目录的位置为开头位置)
scandir(读取特定的目录数据)
seekdir(设置下回读取目录的位置)
stat(取得文件状态)
symlink(建立文件符号连接)
telldir(取得目录流的读取位置)
truncate(改变文件大小)
umask(设置建立新文件时的权限遮罩)
unlink(删除文件)
utime(修改文件的存取时间和更改时间)
utimes(修改文件的存取时间和更改时间)
第16章　信号函数
alarm(设置信号传送闹钟)
kill(传送信号给指定的进程)
pause(让进程暂停直到信号出现)
psignal(列出信号描述和指定字符串)
raise(传送信号给目前的进程)
sigaction(查询或设置信号处理方式)
sigaddset(增加一个信号至信号集)
sigdelset(从信号集里删除一个信号)
sigemptyset(初始化信号集)
sigfillset(将所有信号加入至信号集)
sigismember(测试某个信号是否已加入至信号集里)
signal(设置信号处理方式)
sigpause(暂停直到信号到来)
sigpending(查询被搁置的信号)
sigprocmask(查询或设置信号遮罩)
sigsuspend(暂停直到信号到来)
sleep(让进程暂停执行一段时间)
isdigit(测试字符是否为阿拉伯数字)
第17章 错误处理函数
ferror(检查文件流是否有错误发生)
perror(打印出错误原因信息字符串)
streror(返回错误原因的描述字符串)
第18章 管道相关函数
mkfifo(建立具名管道)
pclose(关闭管道I／O)
pipe(建立管道)
popen(建立管道I/O)
第19章 Socket相关函数
accept(接受socket连线)
bind(对socket定位)
connect(建立socket连线)
endprotoent(结束网络协议数据的读取)
endservent(结束网络服务数据的读取)
gethostbyaddr(由IP地址取得网络数据)
gethostbyname(由主机名称取得网络数据)
getprotobyname(由网络协议名称取得协议数据)
getprotobynumber(由网络协议编号取得协议数据)
getprotoent(取得网络协议数据)
getservbyname(依名称取得网络服务的数据)
getservbyport(依port号码取得网络服务的数据)
getservent(取得主机网络服务的数据)
getsockopt(取得socket状态)
herror(打印出网络错误原因信息字符串)
hstrerror(返回网络错误原因的描述字符串)
htonl(将32位主机字符顺序转换成网络字符顺序)
htons(将16位主机字符顺序转换成网络字符顺序)
inet_addr(将网络地址转成网络二进制的数字)
inet_aton(将网络地址转成网络二进制的数字)
inet_ntoa(将网络二进制的数字转换成网络地址)
listen(等待连接)
ntohl(将32位网络字符顺序转换成主机字符顺序)
ntohs(将16位网络字符顺序转换成主机字符顺序)
recv(经socket接收数据)
recvfrom(经socket接收数据)
recvmsg(经socket接收数据)
send(经socket传送数据)
sendmsg(经socket传送数据)
sendto(经socket传送数据)
setprotoent(打开网络协议的数据文件)
setservent(打开主机网络服务的数据文件)
setsockopt(设置socket状态)
shutdown(终止socket通信)
socket(建立一个socket通信)
第20章 进程通信(IPC)函数
ftok(将文件路径和计划代号转为System VIPCkey)
msgctl(控制信息队列的运作)
msgget(建立信息队列)
msgrcv(从信息队列读取信息)
msgsnd(将信息送入信息队列)
semctl(控制信号队列的操作)
semget(配置信号队列)
semop(信号处理)
shmat(attach共享内存)
shmctl(控制共享内存的操作)
shmdt(detach共享内存)
shmget(配置共享内存)
第21章 记录函数
closelog(关闭信息记录)
openlog(准备做信息记录)
syslog(将信息记录至系统日志文件)
第22章 环境变量函数
getenv(取得环境变量内容)
putenv(改变或增加环境变量)
setenv(改变或增加环境变量)
unsetenv(清除环境变量内容)
第23章 正则表达式
regcomp(编译正则表达式字符串)
regerror(取得正则搜索的错误原因)
regexec(进行正则表达式的搜索)
regfree(释放正则表达式使用的内存)
第24章 动态函数
dlclose(关闭动态函数库文件)
dlerror(动态函数错误处理)
dlopen(打开动态函数库文件)
dlsym(从共享对象中搜索动态函数)
第25章 其他函数
getopt(分析命令行参数)
isatty(判断文件描述词是否是为终端机)
select(I/O多工机制)
ttyname(返回一终端机名称)
