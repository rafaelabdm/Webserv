/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:29:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/16 11:27:07 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <iostream> //std::cout
# include <netdb.h> //addrinfo struct
# include <arpa/inet.h>
# include <sys/socket.h> // socket()
# include <sys/types.h> // socket()
# include <string.h> // memset()
# include <unistd.h> // close()
# include <stdlib.h> // close()
# include <errno.h> //errno

//my headers
# include "colors.hpp"
# include "Server.hpp"
# include "ConfigFile.hpp"

//DEFINES QUE SERÃO SUBSTITUÍDOS PELO .CONF
# include "temporary_defines.hpp"

namespace ft
{
	class Socket
	{
		private:
		struct addrinfo		_hints;
		struct addrinfo*	_servinfo;
		int					_sock;
		ft::t_server_config	_server;

		void setAddrStruct(void);
		void loadAddressInfo();
		void createSocket();
		
		public:
		Socket(ft::t_server_config& server);
		~Socket();
		void	bind();
		void	listen();
		int		accept();
		void	connect();
		int		getSock();

		class	SocketException : std::exception
		{
			public:
			const char* what() const throw();
		};
	};
}

# include "Socket.ipp"

#endif /* Socket_hpp */