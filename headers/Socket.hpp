/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:29:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/09 13:01:16 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "colors.hpp"
# include <iostream> //std::cout
# include <netdb.h> //addrinfo struct
# include <arpa/inet.h>
# include <sys/socket.h> // socket()
# include <sys/types.h> // socket()
# include <string.h> // memset()
# include <unistd.h> // close()
# include <stdlib.h> // close()
# include <errno.h> //errno


//DEFINES QUE SERÃO SUBSTITUÍDOS PELO ARQUIVO .CONF
# define MY_PORT "8080"
# define MY_HOST "localhost"

namespace WS
{
	class Socket
	{
		private:
		struct addrinfo		hints;
		struct addrinfo		*servinfo;
		const char			*host;
		const char			*port;
		int					sock;

		void setAddrStruct(void);
		void loadAddressInfo();
		void createSocket();
		
		public:
		Socket(const std::string host, const std::string port);
		Socket(const std::string port);
		Socket();
		~Socket();
		void	bind();
		void	listen();
		void	accept();
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