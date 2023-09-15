/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:29:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/15 09:42:05 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <cstring>
#include <iostream>

#include <colors.hpp>
#include <iostream>
#include <messages.hpp>
#include <ConfigFile.hpp>

namespace ft
{
	class Socket
	{
	private:
		struct addrinfo _hints;
		struct addrinfo *_servinfo;
		int _sock;
		ft::t_server_config _server;

		void setAddrStruct();
		void loadAddressInfo();
		void createSocket();

	public:
		Socket(const ft::t_server_config &server);
		~Socket();
		void bind();
		void listen();
		int accept();

		ft::t_server_config getServer();
		int getSock();
		std::string getPort();
		std::vector<std::string> getHosts();

		class GetAddrInfoException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class SocketException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class SetSockOptException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class FcntlException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class BindException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class ListenException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class AcceptException : public std::exception
		{
		public:
			const char *what() const throw();
		};
		class ConnectException : public std::exception
		{
		public:
			const char *what() const throw();
		};
	};
}

#include "Socket.ipp"

#endif /* Socket_hpp */