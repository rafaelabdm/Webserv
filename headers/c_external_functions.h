#ifndef C_EXTERNAL_FUNCTIONS_H
# define C_EXTERNAL_FUNCTIONS_H

# include <errno.h>
/**
 * @brief 
 * 
 */
extern int	errno;

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param addr 
 * @param addrlen 
 * @return int 
 */
int	accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param pathname 
 * @param mode 
 * @return int 
 */
int	access(const char *pathname, int mode);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param addr 
 * @param addrlen 
 * @return int 
 */
int	bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param path 
 * @return int 
 */
int	chdir(const char *path);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param fd 
 * @return int 
 */
int	close(int fd);

# include <dirent.h>
/**
 * @brief 
 * 
 * @param dirp 
 * @return int 
 */
int	closedir(DIR *dirp);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param addr 
 * @param addrlen 
 * @return int 
 */
int	connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param oldfd 
 * @return int 
 */
int	dup(int oldfd);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param oldfd 
 * @param newfd 
 * @return int 
 */
int	dup2(int oldfd, int newfd);

# include <sys/epoll.h>
/**
 * @brief 
 * 
 * @param size 
 * @return int 
 */
int	epoll_create(int size);

# include <sys/epoll.h>
/**
 * @brief 
 * 
 * @param epfd 
 * @param op 
 * @param fd 
 * @param event 
 * @return int 
 */
int	epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

# include <sys/epoll.h>
/**
 * @brief 
 * 
 * @param epfd 
 * @param events 
 * @param maxevents 
 * @param timeout 
 * @return int 
 */
int	epoll_wait
(
	int epfd,
	struct epoll_event *events,
	int maxevents,
	int timeout
);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param pathname 
 * @param argv 
 * @param envp 
 * @return int 
 */
int	execve(const char *pathname, char *const argv[], char *const envp[]);

# include <fcntl.h>
/**
 * @brief 
 * 
 */
int	fcntl(int fd, int cmd, ... /* arg */ );

# include <sys/types.h>
/**
 * @brief 
 * 
 * @return pid_t 
 */
pid_t	fork(void);

# include <netdb.h>
/**
 * @brief 
 * 
 * @param res 
 */
void	freeaddrinfo(struct addrinfo *res);

# include <netdb.h>
/**
 * @brief 
 * 
 * @param errcode 
 * @return const char* 
 */
const	char *gai_strerror(int errcode);

# include <netdb.h>
/**
 * @brief 
 * 
 * @param node 
 * @param service 
 * @param hints 
 * @param res 
 * @return int 
 */
int	getaddrinfo
(
	const char *node,
	const char *service,
	const struct addrinfo *hints,
	struct addrinfo **res
);

# include <netdb.h>
/**
 * @brief 
 * 
 * @param name 
 * @return struct protoent* 
 */
struct protoent	*getprotobyname(const char *name);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param addr 
 * @param addrlen 
 * @return int 
 */
int	getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param backlog 
 * @return int 
 */
int	listen(int sockfd, int backlog);

# include <sys/event.h>
/**
 * @brief 
 * 
 * @param kq 
 * @param changelist 
 * @param nchanges 
 * @param eventlist 
 * @param nevents 
 * @param timeout 
 * @return int 
 */
int	kevent
(
	int kq,
	const struct kevent *changelist,
	int nchanges,
	struct kevent *eventlist,
	int nevents,
	const struct timespec *timeout
);

# include <signal.h>
/**
 * @brief 
 * 
 * @param pid 
 * @param sig 
 * @return int 
 */
int	kill(pid_t pid, int sig);

# include <sys/event.h>
/**
 * @brief 
 * 
 * @return int 
 */
int	kqueue(void);

# include <arpa/inet.h>
/**
 * @brief 
 * 
 * @param netlong 
 * @return uint32_t 
 */
uint32_t	ntohl(uint32_t netlong);

# include <arpa/inet.h>
/**
 * @brief 
 * 
 * @param netshort 
 * @return uint16_t 
 */
uint16_t	ntohs(uint16_t netshort);

# include <arpa/inet.h>
/**
 * @brief 
 * 
 * @param hostlong 
 * @return uint32_t 
 */
uint32_t	htonl(uint32_t hostlong);

# include <arpa/inet.h>
/**
 * @brief 
 * 
 * @param hostshort 
 * @return uint16_t 
 */
uint16_t	htons(uint16_t hostshort);

# include <dirent.h>
/**
 * @brief 
 * 
 * @param name 
 * @return DIR* 
 */
DIR	*opendir(const char *name);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param pipefd 
 * @return int 
 */
int	pipe(int pipefd[2]);

# include <poll.h>
/**
 * @brief 
 * 
 * @param fds 
 * @param nfds 
 * @param timeout 
 * @return int 
 */
int	poll(struct pollfd fds[], nfds_t nfds, int timeout);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param fd 
 * @param buf 
 * @param count 
 * @return ssize_t 
 */
ssize_t	read(int fd, void *buf, size_t count);

# include <dirent.h>
/**
 * @brief 
 * 
 * @param dirp 
 * @return struct dirent* 
 */
struct dirent	*readdir(DIR *dirp);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param buf 
 * @param len 
 * @param flags 
 * @return ssize_t 
 */
ssize_t	recv(int sockfd, void *buf, size_t len, int flags);

# include <sys/select.h>
/**
 * @brief 
 * 
 * @param nfds 
 * @param readfds 
 * @param writefds 
 * @param exceptfds 
 * @param timeout 
 * @return int 
 */
int	select
(
	int nfds,
	fd_set *readfds,
	fd_set *writefds,
	fd_set *exceptfds,
	struct timeval *timeout
);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param buf 
 * @param len 
 * @param flags 
 * @return ssize_t 
 */
ssize_t	send(int sockfd, const void *buf, size_t len, int flags);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param sockfd 
 * @param level 
 * @param optname 
 * @param optval 
 * @param optlen 
 * @return int 
 */
int	setsockopt
(
	int sockfd,
	int level,
	int optname,
	const void *optval,
	socklen_t optlen
);

# include <signal.h>
/**
 * @brief 
 * 
 * @param sig 
 * @param func 
 */
void	(*signal(int sig, void (*func)(int)))(int);

# include <sys/socket.h>
/**
 * @brief 
 * 
 * @param domain 
 * @param type 
 * @param protocol 
 * @return int 
 */
int	socket(int domain, int type, int protocol);

# include <sys/types.h>
/**
 * @brief 
 * 
 * @param domain 
 * @param type 
 * @param protocol 
 * @param sv 
 * @return int 
 */
int	socketpair(int domain, int type, int protocol, int sv[2]);

# include <sys/stat.h>
/**
 * @brief 
 * 
 * @param pathname 
 * @param buf 
 * @return int 
 */
int	stat(const char *pathname, struct stat *buf);

# include <string.h>
/**
 * @brief 
 * 
 * @param errnum 
 * @return char* 
 */
char	*strerror(int errnum);

# include <sys/wait.h>
/**
 * @brief 
 * 
 * @param pid 
 * @param status 
 * @param options 
 * @return pid_t 
 */
pid_t	waitpid(pid_t pid, int *status, int options);

# include <unistd.h>
/**
 * @brief 
 * 
 * @param fd 
 * @param buf 
 * @param count 
 * @return ssize_t 
 */
ssize_t	write(int fd, const void *buf, size_t count);

#endif // C_EXTERNAL_FUNCTIONS_H
