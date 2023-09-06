/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:29:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/31 11:49:37 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <arpa/inet.h>
# include <errno.h> //errno
# include <netdb.h> //addrinfo struct
# include <sys/socket.h> // socket()
# include <sys/types.h> // socket()
# include <stdlib.h> // close()
# include <unistd.h> // close()
#include <fcntl.h> // fcntl()

# include <cstring> //std::memset
# include <iostream> //std::cout

# include <colors.hpp>
# include <iostream>
# include <messages.hpp>
# include <ConfigFile.hpp>

namespace ft
{
	class Socket
	{
		private:
		struct addrinfo		_hints;
		struct addrinfo		*_servinfo;
		int					_sock;
		ft::t_server_config	_server;

		void setAddrStruct();
		void loadAddressInfo();
		void createSocket();

		public:
		Socket(const ft::t_server_config& server);
		~Socket();
		void		bind();
		void		listen();
		int			accept();
		void		connect();

		//getters
		ft::t_server_config	getServer();
		int			getSock();
		std::string	getPort();
		std::vector<std::string> getHosts();

		class	GetAddrInfoException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	SocketException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	SetSockOptException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	BindException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	ListenException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	AcceptException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	ConnectException : std::exception
		{
			public:
			const char* what() const throw();
		};
	};
}

# include "Socket.ipp"

#endif /* Socket_hpp */