/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:35:44 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/10 11:18:38 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

WS::Socket::Socket(const std::string s_name, const std::string s_port) : host(s_name.c_str()), port(s_port.c_str())
{
	loadAddressInfo();
	createSocket();
}

WS::Socket::Socket(const std::string s_port) : host(NULL), port(s_port.c_str())
{
	loadAddressInfo();
	createSocket();
}

WS::Socket::Socket(void) : host(NULL), port("8080")
{
	loadAddressInfo();
	createSocket();
}

WS::Socket::~Socket()
{
}

void	WS::Socket::setAddrStruct(void)
{
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; //TCP or UDP
	hints.ai_flags = AI_PASSIVE; // allows bind
}

void	WS::Socket::loadAddressInfo()
{
	int	status;

	setAddrStruct();
	status = getaddrinfo(host, port, &hints, &servinfo);
	if(status)
	{
		std::cerr << RED << "getaddrinfo error: " << RESET_COLOR << gai_strerror(status) << std::endl;
		throw SocketException();
	}
	std::cout << GREEN << "Address loaded successfully!" << RESET_COLOR << std::endl;
}

void	WS::Socket::createSocket()
{
	sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
	if (sock < 0)
	{
		std::cerr << RED << "socket error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Socket created successfully!" << RESET_COLOR << std::endl;
}

int	WS::Socket::getSock()
{
	return(sock);
}

void	WS::Socket::bind()
{
	int status;
	int	yes = 1;
	
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		std::cerr << RED << "setsockopt error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Setsockopt successfull!" << RESET_COLOR << std::endl;

	status = ::bind(sock, servinfo->ai_addr, servinfo->ai_addrlen);
	if (status < 0)
	{
		std::cerr << RED << "bind error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Bind successfull!" << RESET_COLOR << std::endl;

	freeaddrinfo(servinfo);
}

void	WS::Socket::listen()
{
	int status;

	status = ::listen(sock, 10);
	if (status < 0)
	{
		std::cerr << RED << "listen error: " << RESET_COLOR << strerror(errno) << std::endl;
		throw SocketException();
	}
	std::cout << GREEN << "Listen successfull!" << RESET_COLOR << std::endl;
}

int	WS::Socket::accept()
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int	new_socket;

	addr_size = sizeof their_addr;
	new_socket = ::accept(sock, (struct sockaddr *)&their_addr, &addr_size);
	if (new_socket < 0)
	{
		std::cerr << RED << "accept error: " << RESET_COLOR << strerror(errno) << std::endl;
		throw SocketException();
	}
	std::cout << GREEN << "Accept successfully!" << RESET_COLOR << std::endl;
	return (new_socket);
}

void	WS::Socket::connect()
{
	int status;

	status = ::connect(sock, servinfo->ai_addr, servinfo->ai_addrlen);
	if (status < 0)
	{
		std::cerr << RED << "connect error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Connect successfull!" << RESET_COLOR << std::endl;
}

const char* WS::Socket::SocketException::what() const throw()
{
	return ("erro :/");
}