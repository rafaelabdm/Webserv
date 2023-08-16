/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:35:44 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/16 11:26:07 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

ft::Socket::Socket(t_server_config& server) : _server(server)
{
	loadAddressInfo();
	createSocket();
}

ft::Socket::~Socket()
{
}

void	ft::Socket::setAddrStruct(void)
{
	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
	_hints.ai_socktype = SOCK_STREAM; //TCP or UDP
	_hints.ai_flags = AI_PASSIVE; // allows bind
}

void	ft::Socket::loadAddressInfo()
{
	int	status;

	setAddrStruct();
	status = getaddrinfo(_server.host.c_str(), _server.port.c_str(), &_hints, &_servinfo);
	if(status)
	{
		std::cerr << RED << "getaddrinfo error: " << RESET_COLOR << gai_strerror(status) << std::endl;
		throw SocketException();
	}
	std::cout << GREEN << "Address loaded successfully!" << RESET_COLOR << std::endl;
}

void	ft::Socket::createSocket()
{
	_sock = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);
	if (_sock < 0)
	{
		std::cerr << RED << "socket error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Socket created successfully!" << RESET_COLOR << std::endl;
}

int	ft::Socket::getSock()
{
	return(_sock);
}

void	ft::Socket::bind()
{
	int status;
	int	yes = 1;
	
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		std::cerr << RED << "setsockopt error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Setsockopt successfull!" << RESET_COLOR << std::endl;

	status = ::bind(_sock, _servinfo->ai_addr, _servinfo->ai_addrlen);
	if (status < 0)
	{
		std::cerr << RED << "bind error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Bind successfull!" << RESET_COLOR << std::endl;

	freeaddrinfo(_servinfo);
}

void	ft::Socket::listen()
{
	int status;

	status = ::listen(_sock, 10);
	if (status < 0)
	{
		std::cerr << RED << "listen error: " << RESET_COLOR << strerror(errno) << std::endl;
		throw SocketException();
	}
	std::cout << GREEN << "Listen successfull!" << RESET_COLOR << std::endl;
}

int	ft::Socket::accept()
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int	new_socket;

	addr_size = sizeof their_addr;
	new_socket = ::accept(_sock, (struct sockaddr *)&their_addr, &addr_size);
	if (new_socket < 0)
	{
		std::cerr << RED << "accept error: " << RESET_COLOR << strerror(errno) << std::endl;
		throw SocketException();
	}
	std::cout << GREEN << "Accept successfully!" << RESET_COLOR << std::endl;
	return (new_socket);
}

void	ft::Socket::connect()
{
	int status;

	status = ::connect(_sock, _servinfo->ai_addr, _servinfo->ai_addrlen);
	if (status < 0)
	{
		std::cerr << RED << "connect error: " << RESET_COLOR << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
		throw SocketException();
	}
	std::cout << GREEN << "Connect successfull!" << RESET_COLOR << std::endl;
}

const char* ft::Socket::SocketException::what() const throw()
{
	return ("erro :/");
}