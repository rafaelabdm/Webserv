/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.ipp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:35:44 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/09 20:29:55 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

ft::Socket::Socket(const t_server_config &server) : _server(server)
{
	std::cout << FT_SETUP << "Setting up " << FT_HIGH_LIGHT_COLOR << this->_server.server_names[0] << RESET_COLOR << " socket on port " << FT_HIGH_LIGHT_COLOR << this->_server.port << RESET_COLOR << "." << std::endl;

	loadAddressInfo();
	createSocket();

	std::cout << FT_OK << FT_HIGH_LIGHT_COLOR << this->_server.server_names[0] << RESET_COLOR << " socket on port " << FT_HIGH_LIGHT_COLOR << this->_server.port << RESET_COLOR << " is in a nice." << std::endl;
	std::cout << std::endl;
}

ft::Socket::~Socket()
{
	std::cout << FT_CLOSE << "Closing " << FT_HIGH_LIGHT_COLOR << this->_server.server_names[0] << RESET_COLOR << " socket on port " << FT_HIGH_LIGHT_COLOR << this->_server.port << RESET_COLOR << "." << std::endl;
}

void ft::Socket::setAddrStruct(void)
{
	std::memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC;	  // IPv4 or IPv6
	_hints.ai_socktype = SOCK_STREAM; // TCP or UDP
	_hints.ai_flags = AI_PASSIVE;	  // allows bind
}

void ft::Socket::loadAddressInfo()
{
	std::cout << FT_SETUP << "Loading address info." << std::endl;
	int status;

	setAddrStruct();

	status = getaddrinfo(this->_server.server_names[0].c_str(), this->_server.port.c_str(), &_hints, &_servinfo);

	if (status)
	{
		std::cout << FT_STATUS << "Address info status: " << gai_strerror(status) << std::endl;
		throw GetAddrInfoException();
	}

	std::cout << FT_OK << "Address loaded successfully!" << std::endl;
}

void ft::Socket::createSocket()
{
	_sock = socket(_servinfo->ai_family, _servinfo->ai_socktype, _servinfo->ai_protocol);

	std::cout << FT_SETUP << "Creating Socket." << std::endl;
	if (_sock < 0)
	{
		freeaddrinfo(_servinfo);
		throw SocketException();
	}
	std::cout << FT_OK << "Socket created successfully!" << std::endl;

	int yes = 1;

	std::cout << FT_SETUP << "Setting up Socket." << std::endl;
	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		freeaddrinfo(_servinfo);
		throw SetSockOptException();
	}
	std::cout << FT_OK << "Socket configured successfully!" << std::endl;

	std::cout << FT_SETUP << "Setting Socket to non blocking mode." << std::endl;
	int status = fcntl(_sock, F_SETFL, O_NONBLOCK, FD_CLOEXEC); // non_blocking
	if (status < 0)
	{
		freeaddrinfo(_servinfo);
		throw FcntlException();
	}
	std::cout << FT_OK << "Socket are now in non blocking mode!" << std::endl;
}

int ft::Socket::getSock()
{
	return (_sock);
}

void ft::Socket::bind()
{
	int status;

	std::cout
		<< FT_SETUP
		<< "Binding Socket "
		<< FT_HIGH_LIGHT_COLOR << getHosts()[0] << RESET_COLOR
		<< "." << std::endl;

	status = ::bind(_sock, _servinfo->ai_addr, _servinfo->ai_addrlen);

	if (status < 0)
	{
		std::cout << FT_STATUS << "Bind status: " << strerror(errno) << std::endl;
		throw BindException();
	}

	std::cout << FT_OK << "Bind successfull!" << std::endl;

	std::cout << FT_SETUP << "Freeing Address Info memory" << std::endl;
	freeaddrinfo(_servinfo);
	std::cout << FT_OK << "Address Info memory is now free" << std::endl;
}

void ft::Socket::listen()
{
	int status;

	std::cout
		<< FT_SETUP
		<< "Putting Socket "
		<< FT_HIGH_LIGHT_COLOR << getHosts()[0] << RESET_COLOR
		<< " in Listen Mode."
		<< std::endl;

	status = ::listen(_sock, 10);
	if (status < 0)
	{
		std::cout << FT_STATUS << "Listen status: " << strerror(errno) << std::endl;
		throw ListenException();
	}
	std::cout << FT_OK << "Socket is now in Listen Mode!" << std::endl;
}

int ft::Socket::accept()
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	int new_socket;

	std::cout << FT_EVENT << "Accept requested." << std::endl;
	addr_size = sizeof their_addr;
	new_socket = ::accept(_sock, (struct sockaddr *)&their_addr, &addr_size);
	if (new_socket < 0)
	{
		std::cout << FT_STATUS << "Accept status: " << strerror(errno) << std::endl;
		throw AcceptException();
	}
	std::cout << FT_OK << "Accept successfull!" << std::endl;
	return (new_socket);
}

void ft::Socket::connect()
{
	try
	{
		int status;

		status = ::connect(_sock, _servinfo->ai_addr, _servinfo->ai_addrlen);
		if (status < 0)
			throw ConnectException();
		std::cout << FT_OK << "Connect successfull!" << std::endl;
	}
	catch (ConnectException &e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
		freeaddrinfo(_servinfo);
	}
}

std::string ft::Socket::getPort()
{
	return (_server.port);
}

std::vector<std::string> ft::Socket::getHosts()
{
	std::string host;
	std::vector<std::string> hosts;

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

ft::t_server_config ft::Socket::getServer()
{
	return (_server);
}

const char *ft::Socket::GetAddrInfoException::what() const throw()
{
	return (FT_ERROR "Can't get Address's info.");
}

const char *ft::Socket::SocketException::what() const throw()
{
	return (FT_ERROR "Can't create Socket.");
}

const char *ft::Socket::SetSockOptException::what() const throw()
{
	return (FT_ERROR "Can't configure Socket.");
}

const char *ft::Socket::FcntlException::what() const throw()
{
	return (FT_ERROR "Can't set Socket to non blocking mode.");
}

const char *ft::Socket::BindException::what() const throw()
{
	return (FT_ERROR "Can't bind socket with IP and port.");
}

const char *ft::Socket::ListenException::what() const throw()
{
	return (FT_ERROR "Can't put Socket in Listen Mode.");
}

const char *ft::Socket::AcceptException::what() const throw()
{
	return (FT_ERROR "Accept rejected.");
}

const char *ft::Socket::ConnectException::what() const throw()
{
	return (FT_ERROR "Connect rejected.");
}
