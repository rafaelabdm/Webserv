/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:35:44 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/08 10:14:58 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

ft::Socket::Socket(const t_server_config& server) : _server(server)
{
	std::cout << FT_SETUP << "Setting up " << GREEN << this->_server.server_names[0] << RESET_COLOR << " socket on port " << GREEN << this->_server.port << RESET_COLOR << "." << std::endl;

	loadAddressInfo();
	createSocket();

	std::cout << FT_OK << GREEN << this->_server.server_names[0] << RESET_COLOR << " socket on port " << GREEN << this->_server.port << RESET_COLOR << " is in a nice." << std::endl;
}

ft::Socket::~Socket()
{
	std::cout << FT_CLOSE << "Closing " << GREEN << this->_server.server_names[0] << RESET_COLOR << " socket on port " << GREEN << this->_server.port << RESET_COLOR << "." << std::endl;
}

void	ft::Socket::setAddrStruct(void)
{
	std::memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC; // IPv4 or IPv6
	_hints.ai_socktype = SOCK_STREAM; //TCP or UDP
	_hints.ai_flags = AI_PASSIVE; // allows bind
}

void	ft::Socket::loadAddressInfo()
{
	int	status;

	setAddrStruct();
	try
	{
		status = getaddrinfo(this->_server.server_names[0].c_str(), this->_server.port.c_str(), &_hints, &_servinfo);

		if(status)
			throw GetAddrInfoException();
		std::cout << FT_OK << "Address loaded successfully!" << std::endl;
	}
	catch (Socket::GetAddrInfoException& e)
	{
		std::cerr << e.what() << gai_strerror(status) << std::endl;
	}
}

void	ft::Socket::createSocket()
{
	_sock = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);

	try
	{
		if (_sock < 0)
			throw SocketException();
		std::cout << FT_OK << "Socket created successfully!" << std::endl;
		
		int	yes = 1;

		if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
			throw SetSockOptException();
		std::cout << FT_OK << "Setsockopt successfull!" << std::endl;

		int status = fcntl(_sock, F_SETFL, O_NONBLOCK, FD_CLOEXEC); //non_blocking
		if (status < 0)
			throw SetSockOptException();
		std::cout << FT_OK << "fcntl successfull!" << std::endl;

	}
	catch (SocketException& e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
	}
}

int	ft::Socket::getSock()
{
	return(_sock);
}

void	ft::Socket::bind()
{

	try
	{
		int status;

		status = ::bind(_sock, _servinfo->ai_addr, _servinfo->ai_addrlen);
		if (status < 0)
			throw BindException();
		std::cout << FT_OK << "Bind successfull!" << std::endl;
	}
	catch (SetSockOptException& e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
	}
	catch (BindException& e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
	}

	freeaddrinfo(_servinfo);
}

void	ft::Socket::listen()
{
	try
	{
		int status;

		status = ::listen(_sock, 10);
		if (status < 0)
			throw ListenException();
		std::cout << FT_OK << "Listen successfull!" << std::endl;
	}
	catch (ListenException& e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
	}
}

int	ft::Socket::accept()
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int	new_socket;

	try
	{
		addr_size = sizeof their_addr;
		new_socket = ::accept(_sock, (struct sockaddr *)&their_addr, &addr_size);
		if (new_socket < 0)
			throw AcceptException();
		std::cout << FT_OK << "Accept successfull!" << std::endl;
	}
	catch (AcceptException& e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
	}
	return (new_socket);
}

void	ft::Socket::connect()
{
	try
	{
		int status;

		status = ::connect(_sock, _servinfo->ai_addr, _servinfo->ai_addrlen);
		if (status < 0)
			throw ConnectException();
		std::cout << FT_OK << "Connect successfull!" << std::endl;
	}
	catch (ConnectException& e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
	}
}

std::string	ft::Socket::getPort()
{
	return (_server.port);
}

std::vector<std::string> ft::Socket::getHosts()
{
	std::string host;
	std::vector<std::string>hosts;
	
	for (long unsigned int i = 0; i < _server.server_names.size(); i++)
	{
		host = "";
		host.append(_server.server_names[i]);
		host.append(":");
		host.append(_server.port);
		hosts.push_back(host);
	}
	return (hosts);
}

ft::t_server_config	ft::Socket::getServer()
{
	return (_server);
}

const char* ft::Socket::GetAddrInfoException::what() const throw()
{
	return (FT_ERROR "getaddrinfo error: ");
}

const char* ft::Socket::SocketException::what() const throw()
{
	return (FT_ERROR "socket error: ");
}

const char* ft::Socket::SetSockOptException::what() const throw()
{
	return (FT_ERROR "setsockopt error: ");
}

const char* ft::Socket::BindException::what() const throw()
{
	return (FT_ERROR "bind error: ");
}

const char* ft::Socket::ListenException::what() const throw()
{
	return (FT_ERROR "bind error: ");
}

const char* ft::Socket::AcceptException::what() const throw()
{
	return (FT_ERROR "accept error: ");
}

const char* ft::Socket::ConnectException::what() const throw()
{
	return (FT_ERROR "accept error: ");
}
