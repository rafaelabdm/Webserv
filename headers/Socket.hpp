/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:29:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/02 13:14:00 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "../headers/colors.hpp"
# include <iostream> //std::cout
# include <netdb.h> //addrinfo struct
# include <arpa/inet.h>
# include <sys/socket.h> // socket()
# include <sys/types.h> // socket()
# include <string.h> // memset()
#include <unistd.h> // close()

namespace WS
{
	class Socket
	{
		private:
		struct addrinfo		hints;
		struct addrinfo		*servinfo;
		const char			*server_name;
		const char			*port;
		int					sock;

		void setAddrStruct(void);
		void loadAddressInfo();
		void createSocket();
		
		public:
		Socket(const std::string server_name, const std::string port);
		Socket(const std::string port);
		Socket();
		~Socket();
		void	bind();
		void	listen();
		void	accept();
		void	connect();
		int getSock();
	};
}

#endif /* Socket_hpp */