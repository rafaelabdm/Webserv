/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_external_functions.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 19:40:44 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/04 19:40:44 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef C_EXTERNAL_FUNCTIONS_H
# define C_EXTERNAL_FUNCTIONS_H

# include <sys/types.h>
// size_t, ssize_t, time_t, pid_t

# include <netinet/in.h>
/**
 * @brief Estrutura que representa um endereço de socket no domínio AF_INET.
 * 
 * A estrutura `sockaddr_in` é usada para representar um endereço de socket no domínio AF_INET (IPv4).
 * Ela contém informações sobre o endereço IP e o número da porta associados ao socket.
 * struct sockaddr_in
 * {
 *   sa_family_t sin_family; // Família do endereço (sempre AF_INET para IPv4)
 *   in_port_t sin_port; // Número da porta em ordem de byte de rede
 *   struct in_addr sin_addr; // Endereço IP em ordem de byte de rede
 *   unsigned char sin_zero[8]; // Preenchimento para alinhamento da estrutura
 * };
 * @note Esta estrutura é usada principalmente com as funções de sockets, como bind() e connect(),
 * para especificar o endereço ao qual o socket será vinculado ou conectado.
 * 
 * @see sockaddr para uma estrutura genérica que pode ser usada para representar endereços de socket em diferentes domínios.
 */
struct sockaddr_in;

# include <errno.h>
/**
 * @brief Variável externa que armazena o código do último erro ocorrido.
 * 
 * A variável externa `errno` é usada para armazenar o código do último erro ocorrido em uma chamada de função.
 * Essa variável é usada principalmente em funções do sistema operacional e da biblioteca padrão do C/C++
 * para indicar o motivo específico do erro que ocorreu durante a execução de uma operação.
 * 
 * O valor de `errno` é específico para cada thread e pode variar dependendo do sistema operacional e do contexto de execução.
 * Antes de fazer uma chamada de função que pode gerar um erro, é uma boa prática verificar o valor de `errno`
 * após a chamada para identificar se ocorreu algum erro e tomar ações apropriadas para tratá-lo.
 * 
 * @note O valor de `errno` só é válido após uma chamada de função que define esse valor.
 * Portanto, se não houver erros, o valor de `errno` pode ser indefinido e não deve ser usado.
 * 
 * @see perror() para exibir mensagens de erro descritivas baseadas em `errno`.
 */
extern int	errno;

// # include <sys/socket.h>
// /**
//  * @brief 
//  * 
//  * @param sockfd 
//  * @param addr 
//  * @param addrlen 
//  * @return int 
//  */
// int	accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param pathname 
//  * @param mode 
//  * @return int 
//  */
// int	access(const char *pathname, int mode);

# include <sys/socket.h>
/**
 * @brief Associa um endereço a um socket.
 * 
 * Esta função é usada para associar um endereço a um socket identificado pelo descritor de arquivo `sockfd`.
 * O endereço a ser associado é fornecido por meio da estrutura `sockaddr` apontada por `addr`.
 * O tamanho do endereço é especificado por `addrlen`.
 * 
 * @param sockfd O descritor do socket ao qual o endereço será associado.
 * @param addr Um ponteiro para a estrutura `sockaddr` que contém o endereço a ser associado.
 * @param addrlen O tamanho do endereço em bytes.
 * @return int 0 em caso de sucesso, ou -1 em caso de erro.
 * 
 * @note O tipo da estrutura `sockaddr` pode variar dependendo do domínio do socket utilizado.
 * Por exemplo, para sockets do domínio AF_INET (IPv4), a estrutura `sockaddr_in` é usada para representar o endereço.
 * É importante garantir que o tamanho e o tipo da estrutura `addr` sejam compatíveis com o domínio do socket utilizado.
 * 
 * @see socket() para criar um novo socket.
 */
int	bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param path 
//  * @return int 
//  */
// int	chdir(const char *path);

# include <unistd.h>
/**
 * @brief Fecha um descritor de arquivo (file descriptor).
 * 
 * Esta função é usada para fechar um descritor de arquivo (file descriptor) aberto anteriormente
 * pelo programa. Um descritor de arquivo é um inteiro que identifica um arquivo, um socket ou outro recurso
 * aberto no sistema operacional.
 * 
 * @param fd O descritor de arquivo a ser fechado.
 * @return int 0 em caso de sucesso, ou -1 em caso de erro.
 * 
 * @note Ao fechar um descritor de arquivo, o recurso associado a ele é liberado, tornando-o não mais válido.
 * Portanto, após chamar a função `close`, não é seguro usar o descritor de arquivo novamente.
 * Certifique-se de que não haja mais uso do descritor de arquivo após chamá-lo.
 * 
 * @see open() para abrir um arquivo ou recurso e obter um descritor de arquivo.
 */
int	close(int fd);

// # include <dirent.h>
// /**
//  * @brief 
//  * 
//  * @param dirp 
//  * @return int 
//  */
// int	closedir(DIR *dirp);

// # include <sys/socket.h>
// /**
//  * @brief 
//  * 
//  * @param sockfd 
//  * @param addr 
//  * @param addrlen 
//  * @return int 
//  */
// int	connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param oldfd 
//  * @return int 
//  */
// int	dup(int oldfd);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param oldfd 
//  * @param newfd 
//  * @return int 
//  */
// int	dup2(int oldfd, int newfd);

// # include <sys/epoll.h>
// /**
//  * @brief 
//  * 
//  * @param size 
//  * @return int 
//  */
// int	epoll_create(int size);

// # include <sys/epoll.h>
// /**
//  * @brief 
//  * 
//  * @param epfd 
//  * @param op 
//  * @param fd 
//  * @param event 
//  * @return int 
//  */
// int	epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

// # include <sys/epoll.h>
// /**
//  * @brief 
//  * 
//  * @param epfd 
//  * @param events 
//  * @param maxevents 
//  * @param timeout 
//  * @return int 
//  */
// int	epoll_wait
// (
// 	int epfd,
// 	struct epoll_event *events,
// 	int maxevents,
// 	int timeout
// );

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param pathname 
//  * @param argv 
//  * @param envp 
//  * @return int 
//  */
// int	execve(const char *pathname, char *const argv[], char *const envp[]);

// # include <fcntl.h>
// /**
//  * @brief 
//  * 
//  */
// int	fcntl(int fd, int cmd, ... /* arg */ );

// # include <sys/types.h>
// /**
//  * @brief 
//  * 
//  * @return pid_t 
//  */
// pid_t	fork(void);

// # include <netdb.h>
// /**
//  * @brief 
//  * 
//  * @param res 
//  */
// void	freeaddrinfo(struct addrinfo *res);

// # include <netdb.h>
// /**
//  * @brief 
//  * 
//  * @param errcode 
//  * @return const char* 
//  */
// const	char *gai_strerror(int errcode);

// # include <netdb.h>
// /**
//  * @brief 
//  * 
//  * @param node 
//  * @param service 
//  * @param hints 
//  * @param res 
//  * @return int 
//  */
// int	getaddrinfo
// (
// 	const char *node,
// 	const char *service,
// 	const struct addrinfo *hints,
// 	struct addrinfo **res
// );

// # include <netdb.h>
// /**
//  * @brief 
//  * 
//  * @param name 
//  * @return struct protoent* 
//  */
// struct protoent	*getprotobyname(const char *name);

// # include <sys/socket.h>
// /**
//  * @brief 
//  * 
//  * @param sockfd 
//  * @param addr 
//  * @param addrlen 
//  * @return int 
//  */
// int	getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

# include <sys/socket.h>
/**
 * @brief Coloca o socket no modo de escuta para conexões de entrada.
 * 
 * Esta função é usada para colocar o socket identificado pelo descritor de arquivo `sockfd`
 * no modo de escuta, aguardando conexões de entrada de clientes.
 * O parâmetro `backlog` especifica o tamanho da fila de conexões pendentes.
 * 
 * @param sockfd O descritor do socket que será colocado no modo de escuta.
 * @param backlog O tamanho da fila de conexões pendentes.
 * @return int 0 em caso de sucesso, ou -1 em caso de erro.
 * 
 * @note O valor de `backlog` determina quantas conexões de entrada pendentes podem ser enfileiradas para o socket.
 * Se o número de conexões pendentes exceder o valor especificado em `backlog`, as conexões adicionais serão recusadas.
 * O valor de `backlog` deve ser maior ou igual a 0. Se for 0, o socket será colocado no modo de escuta, mas sem conexões pendentes.
 * 
 * @see accept() para aceitar uma conexão de entrada.
 */
int	listen(int sockfd, int backlog);

// // # include <sys/event.h>
// /**
//  * @brief 
//  * 
//  * @param kq 
//  * @param changelist 
//  * @param nchanges 
//  * @param eventlist 
//  * @param nevents 
//  * @param timeout 
//  * @return int 
//  */
// int	kevent
// (
// 	int kq,
// 	const struct kevent *changelist,
// 	int nchanges,
// 	struct kevent *eventlist,
// 	int nevents,
// 	const struct timespec *timeout
// );

// # include <signal.h>
// /**
//  * @brief 
//  * 
//  * @param pid 
//  * @param sig 
//  * @return int 
//  */
// int	kill(pid_t pid, int sig);

// # include <sys/event.h>
// /**
//  * @brief 
//  * 
//  * @return int 
//  */
// int	kqueue(void);

// # include <arpa/inet.h>
// /**
//  * @brief 
//  * 
//  * @param netlong 
//  * @return uint32_t 
//  */
// uint32_t	ntohl(uint32_t netlong);

// # include <arpa/inet.h>
// /**
//  * @brief 
//  * 
//  * @param netshort 
//  * @return uint16_t 
//  */
// uint16_t	ntohs(uint16_t netshort);

// # include <arpa/inet.h>
// /**
//  * @brief 
//  * 
//  * @param hostlong 
//  * @return uint32_t 
//  */
// uint32_t	htonl(uint32_t hostlong);

// # include <arpa/inet.h>
// /**
//  * @brief 
//  * 
//  * @param hostshort 
//  * @return uint16_t 
//  */
// uint16_t	htons(uint16_t hostshort);

// # include <dirent.h>
// /**
//  * @brief 
//  * 
//  * @param name 
//  * @return DIR* 
//  */
// DIR	*opendir(const char *name);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param pipefd 
//  * @return int 
//  */
// int	pipe(int pipefd[2]);

// # include <poll.h>
// /**
//  * @brief 
//  * 
//  * @param fds 
//  * @param nfds 
//  * @param timeout 
//  * @return int 
//  */
// int	poll(struct pollfd fds[], nfds_t nfds, int timeout);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param fd 
//  * @param buf 
//  * @param count 
//  * @return ssize_t 
//  */
// ssize_t	read(int fd, void *buf, size_t count);

// # include <dirent.h>
// /**
//  * @brief 
//  * 
//  * @param dirp 
//  * @return struct dirent* 
//  */
// struct dirent	*readdir(DIR *dirp);

// # include <sys/socket.h>
// /**
//  * @brief 
//  * 
//  * @param sockfd 
//  * @param buf 
//  * @param len 
//  * @param flags 
//  * @return ssize_t 
//  */
// ssize_t	recv(int sockfd, void *buf, size_t len, int flags);

// # include <sys/select.h>
// /**
//  * @brief 
//  * 
//  * @param nfds 
//  * @param readfds 
//  * @param writefds 
//  * @param exceptfds 
//  * @param timeout 
//  * @return int 
//  */
// int	select
// (
// 	int nfds,
// 	fd_set *readfds,
// 	fd_set *writefds,
// 	fd_set *exceptfds,
// 	struct timeval *timeout
// );

// # include <sys/socket.h>
// /**
//  * @brief 
//  * 
//  * @param sockfd 
//  * @param buf 
//  * @param len 
//  * @param flags 
//  * @return ssize_t 
//  */
// ssize_t	send(int sockfd, const void *buf, size_t len, int flags);

# include <sys/socket.h>
/**
 * @brief Configura opções em um socket.
 * 
 * Esta função é usada para configurar opções em um socket existente, identificado pelo descritor de arquivo sockfd.
 * As opções especificadas são definidas no nível para o socket.
 * O nome da opção a ser configurada é fornecido em optname, e o valor da opção é especificado em optval.
 * O tamanho do valor da opção é especificado em optlen.
 * 
 * @param sockfd O descritor do socket para o qual a opção será configurada.
 * @param level O nível em que a opção será configurada, como SOL_SOCKET (nível do socket).
 * @param optname O nome da opção a ser configurada.
 * @param optval Um ponteiro para o valor da opção a ser configurada.
 * @param optlen O tamanho do valor da opção em bytes.
 * @return int 0 em caso de sucesso, ou -1 em caso de erro.
 * 
 * @note O comportamento dessa função pode variar dependendo do sistema operacional e das opções específicas fornecidas.
 * É importante verificar a documentação do sistema operacional para obter detalhes sobre as opções suportadas e seus valores válidos.
 * 
 * @see getsockopt() para obter opções de configuração existentes em um socket.
 */
int	setsockopt
(
	int sockfd,
	int level,
	int optname,
	const void *optval,
	socklen_t optlen
);

// # include <signal.h>
// /**
//  * @brief 
//  * 
//  * @param sig 
//  * @param func 
//  */
// void	(*signal(int sig, void (*func)(int)))(int);

# include <sys/socket.h>
/**
 * @brief Cria um novo socket para comunicação em rede.
 * 
 * Esta função cria um novo socket usando os parâmetros fornecidos.
 * O socket pode ser usado para comunicação em rede em um domínio específico,
 * com um determinado tipo e protocolo.
 * 
 * @param domain O domínio do endereço do socket, como AF_INET (IPv4) ou AF_INET6 (IPv6).
 * @param type O tipo de socket, como SOCK_STREAM (TCP) ou SOCK_DGRAM (UDP).
 * @param protocol O protocolo a ser usado. Em geral, o valor 0 é utilizado para escolher automaticamente o protocolo adequado.
 * @return int O descritor do socket criado, ou -1 em caso de erro.
 */
int	socket(int domain, int type, int protocol);

// # include <sys/types.h>
// /**
//  * @brief 
//  * 
//  * @param domain 
//  * @param type 
//  * @param protocol 
//  * @param sv 
//  * @return int 
//  */
// int	socketpair(int domain, int type, int protocol, int sv[2]);

// # include <sys/stat.h>
// /**
//  * @brief 
//  * 
//  * @param pathname 
//  * @param buf 
//  * @return int 
//  */
// int	stat(const char *pathname, struct stat *buf);

// # include <string.h>
// /**
//  * @brief 
//  * 
//  * @param errnum 
//  * @return char* 
//  */
// char	*strerror(int errnum);

// # include <sys/wait.h>
// /**
//  * @brief 
//  * 
//  * @param pid 
//  * @param status 
//  * @param options 
//  * @return pid_t 
//  */
// pid_t	waitpid(pid_t pid, int *status, int options);

// # include <unistd.h>
// /**
//  * @brief 
//  * 
//  * @param fd 
//  * @param buf 
//  * @param count 
//  * @return ssize_t 
//  */
// ssize_t	write(int fd, const void *buf, size_t count);

#endif // C_EXTERNAL_FUNCTIONS_H
