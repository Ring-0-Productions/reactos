/* POSIX+ system calls (machine generated: do not edit!) */
#include "../include/psxss.h"
#include "../include/syscall.h"
PSX_SYSTEM_CALL SystemCall [] =
{
(void*)syscall_null,
(void*)syscall_fork,
(void*)syscall_authenticateuser,
(void*)syscall_waitpid,
(void*)syscall__exit,
(void*)syscall_kill,
(void*)syscall_sigaction,
(void*)syscall_sigprocmask,
(void*)syscall_sigpending,
(void*)syscall_sigsuspend,
(void*)syscall_alarm,
(void*)syscall_getpsids,
(void*)syscall_syscall12,
(void*)syscall_syscall13,
(void*)syscall_getgroups,
(void*)syscall_syscall15,
(void*)syscall_syscall16,
(void*)syscall_setsid,
(void*)syscall_setpgid,
(void*)syscall_syscall19,
(void*)syscall_syscall20,
(void*)syscall_times,
(void*)syscall_ttyname,
(void*)syscall_isatty,
(void*)syscall_sysconf,
(void*)syscall_open,
(void*)syscall_umask,
(void*)syscall_link,
(void*)syscall_mkdir,
(void*)syscall_mkfifo,
(void*)syscall_rmdir,
(void*)syscall_rename,
(void*)syscall_stat,
(void*)syscall_fstat,
(void*)syscall_access,
(void*)syscall_chmod,
(void*)syscall_chown,
(void*)syscall_utime,
(void*)syscall_pathconf,
(void*)syscall_fpathconf,
(void*)syscall_pipe,
(void*)syscall_syscall41,
(void*)syscall_dup2,
(void*)syscall_close,
(void*)syscall_read,
(void*)syscall_write,
(void*)syscall_fcntl,
(void*)syscall_lseek,
(void*)syscall_tcgetattr,
(void*)syscall_tcsetattr,
(void*)syscall_tcsendbreak,
(void*)syscall_tcdrain,
(void*)syscall_tcflush,
(void*)syscall_tcflow,
(void*)syscall_tcgetpgrp,
(void*)syscall_tcsetpgrp,
(void*)syscall_getpwuid,
(void*)syscall_getpwnam,
(void*)syscall_getgrgid,
(void*)syscall_getgrnam,
(void*)syscall_unlink,
(void*)syscall_readdir,
(void*)syscall_ftruncate,
(void*)syscall_syscall63,
(void*)syscall_semctl,
(void*)syscall_semget,
(void*)syscall_semop,
(void*)syscall_shmat,
(void*)syscall_shmctl,
(void*)syscall_shmdt,
(void*)syscall_shmget,
(void*)syscall_msgctl,
(void*)syscall_msgget,
(void*)syscall_msgrcv,
(void*)syscall_msgsnd,
(void*)syscall_socket,
(void*)syscall_accept,
(void*)syscall_bind,
(void*)syscall_connect,
(void*)syscall_getpeername,
(void*)syscall_getsockname,
(void*)syscall_getsockopt,
(void*)syscall_listen,
(void*)syscall_recv,
(void*)syscall_recvfrom,
(void*)syscall_send,
(void*)syscall_sendto,
(void*)syscall_setsockopt,
(void*)syscall_shutdown,
(void*)syscall_gethostbyname,
(void*)syscall_gethostbyaddr,
(void*)syscall_getprotobyname,
(void*)syscall_getprotobynumber,
(void*)syscall_getservbyname,
(void*)syscall_getservbyport,
(void*)syscall_select,
(void*)syscall_statvfs,
(void*)syscall_fstatvfs,
(void*)syscall_ptsname,
(void*)syscall__fdptcheck,
(void*)syscall_ioctl,
(void*)syscall_mmap,
(void*)syscall_syscall102,
(void*)syscall_uidtontsid,
(void*)syscall_gettzenv,
(void*)syscall_pututxline,
(void*)syscall_renamewtmpx,
(void*)syscall_fsync,
(void*)syscall_setgetitimer,
(void*)syscall_setuser,
(void*)syscall_ipcs,
0
};
/* EOF */