/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:37:17 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/10 11:20:55 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

ft::WebServer::WebServer(const char *configuration_file)
{
	// Initializes Ctrl + C signal handler
	ft::keep();

	std::string str_configuration_file;
	if (configuration_file == NULL)
		str_configuration_file = FT_DEFAULT_CONFIG_FILE;
	else
		str_configuration_file = configuration_file;

	if (str_configuration_file == "")
		str_configuration_file = FT_DEFAULT_CONFIG_FILE;

	std::cout
		<< FT_SETUP
		<< "Setting up Web server from "
		<< FT_HIGH_LIGHT_COLOR << str_configuration_file << RESET_COLOR
		<< " file."
		<< std::endl;
	std::cout << std::endl;

	_config_file = ConfigFile(str_configuration_file);

	checkSudo();
	if (_is_sudo == true)
		std::cout << FT_WARNING << "You can do, what SUDO!" << std::endl;
	if (_config_file.needSudo() == true && _is_sudo == false)
		throw needSudoException();

	for (size_t i = 0; ft::keep() && i < _config_file.size(); i++)
		_connections.push_back(new ft::Socket(_config_file.getServer(i)));

	std::vector<ft::Socket *>::iterator it;

	for (it = _connections.begin(); it != _connections.end(); it++)
	{
		try
		{
			(*it)->bind();
			(*it)->listen();
		}
		catch (ft::Socket::BindException& e)
		{
			std::vector<ft::Socket *>::iterator it;
			for (it = _connections.begin(); it != _connections.end(); it++)
				delete *it;
			throw e;
		}
		std::cout << std::endl;
	}
}

ft::WebServer::~WebServer()
{
	std::cout << FT_CLOSE << "Closing Web server." << std::endl;

	std::vector<ft::Socket *>::iterator it;

	std::cout << FT_CLOSE << "Freeing Socket memory." << std::endl;
	for (it = _connections.begin(); it != _connections.end(); it++)
		delete *it;

	std::cout << FT_OK << "Socket memory is now free!" << std::endl;

	std::cout << FT_CLOSE << "Closing epoll." << std::endl;
	close(_epoll);
	std::cout << FT_OK << "Epoll closed!" << std::endl;

	std::cout << FT_OK << "Web server closed!" << std::endl;
	std::cout << std::endl;
}

void ft::WebServer::epoll()
{
	_epoll = ::epoll_create(1);
	if (_epoll < 0)
	{
		std::cout << FT_STATUS << "Epoll status: " << strerror(errno) << std::endl;
		throw EpollException();
	}
}

void ft::WebServer::epollAddServers()
{
	struct epoll_event events_setup;
	std::vector<ft::Socket *>::iterator it;

	events_setup.events = EPOLLIN | EPOLLOUT;
	for (it = _connections.begin(); it != _connections.end(); it++)
	{
		events_setup.data.fd = (*it)->getSock();
		if (::epoll_ctl(_epoll, EPOLL_CTL_ADD, (*it)->getSock(), &events_setup) < 0)
		{
			std::cout << FT_STATUS << "Epoll Ctl status: " << strerror(errno) << std::endl;
			throw EpollCtlException();
		}
	}
}

int ft::WebServer::epoll_wait(struct epoll_event *events)
{
	int nfds;

	nfds = ::epoll_wait(_epoll, events, FT_MAX_EVENT_SIZE, -1);
	if (nfds == -1 && ft::keep())
	{
		std::cout << FT_STATUS << "Epoll Wait status: " << strerror(errno) << std::endl;
		throw EpollWaitException();
	}

	return (nfds);
}

void ft::WebServer::checkSudo()
{
	struct stat processStat;

	if (stat("/proc/self", &processStat) != 0)
		throw cantGetUserInfoException();

	if (processStat.st_uid == 0)
		_is_sudo = true;
	else
		_is_sudo = false;
}

int ft::WebServer::isServerSideEvent(int epoll_fd)
{
	std::vector<ft::Socket *>::iterator it;

	std::cout
		<< FT_EVENT
		<< "Server side event happened on fd "
		<< FT_HIGH_LIGHT_COLOR << epoll_fd << RESET_COLOR
		<< "." << std::endl;

	for (it = _connections.begin(); it != _connections.end() && ft::keep(); it++)
	{
		if (epoll_fd == (*it)->getSock())
			return ((*it)->accept());
	}
	return (0);
}

std::string ft::WebServer::getBoundry(std::string request)
{
	size_t start;
	size_t end;

	start = request.find("boundary=", 0) + 9;
	if (start == std::string::npos)
		return ("");
	end = request.find("\r", start);
	return (request.substr(start, end - start));
}

int  ft::WebServer::getRequestTotalLength(std::string request)
{
	size_t	start;
	size_t	end;
	int		length;
	std::string boundry;

	boundry = getBoundry(request);
	if (boundry == "")
		return (request.length());

	length = request.rfind(boundry, request.length()) - 2;
	start = request.find("Content-Length: ", 0);
	if (start == std::string::npos)
		return (request.length());
	start += 16;
	end = request.find("\r", start);
	length += std::atoi(request.substr(start, end - start).data());
	return (length);
}

void ft::WebServer::recv(int client_fd, struct epoll_event &events_setup)
{
	std::cout
		<< FT_EVENT
		<< "Recv event happened on fd "
		<< FT_HIGH_LIGHT_COLOR << client_fd << RESET_COLOR
		<< "." << std::endl;

	char client_buffer[FT_DEFAULT_CLIENT_BUFFER_SIZE];
	std::string total_request;
	int total_bytes = -1;
	int bytes = 0;
	int current_bytes_read = -2;

	std::memset(client_buffer, 0, FT_DEFAULT_CLIENT_BUFFER_SIZE);
	while (current_bytes_read < total_bytes && ft::keep())
	{
		bytes = ::recv(client_fd, client_buffer, sizeof(client_buffer), 0);
		if (bytes == 0)
			break ;
		if (bytes == -1)
			break ;
		if (total_bytes == -1)
		{
			current_bytes_read = 0;
			total_bytes = getRequestTotalLength(client_buffer);
		}
		if (bytes > 0)
		{
			std::cout << FT_EVENT << "Receiving " << bytes
					  << ((bytes <= 1) ? " byte." : " bytes.")
					  << std::endl;
			current_bytes_read += bytes;
			total_request.append(client_buffer, bytes);
		}
	}
	std::cout << FT_EVENT << total_request.length()
			  << ((total_request.length() <= 1) ? " byte" : " bytes")
			  << " received."
			  << " recv exited with " << bytes << " bytes."
			  << std::endl;

	if (bytes == -1)
		std::cout << FT_WARNING << "Falied to recive request from client [" << client_fd << "]" << std::endl;
	else if (total_request.length() > 0)
	{
		_request_list[client_fd] = total_request;
		events_setup.data.fd = client_fd;
		events_setup.events = EPOLLOUT;
		epoll_ctl(_epoll, EPOLL_CTL_MOD, client_fd, &events_setup);
		return ;
	}
	events_setup.data.fd = client_fd;
	epoll_ctl(_epoll, EPOLL_CTL_DEL, client_fd, &events_setup);
	close(client_fd);
}

void ft::WebServer::send(int client_fd, struct epoll_event &events_setup)
{
	std::cout
		<< FT_EVENT
		<< "Send event happened on fd "
		<< FT_HIGH_LIGHT_COLOR << client_fd << RESET_COLOR
		<< "." << std::endl;

	Request request(_request_list[client_fd]);
	Response response(request, _connections);
	std::string msg = response.getResponse();
	::send(client_fd, msg.data(), msg.length(), 0);
	_request_list.erase(client_fd);
	events_setup.data.fd = client_fd;
	epoll_ctl(_epoll, EPOLL_CTL_DEL, client_fd, &events_setup);
	close(client_fd);
}

void ft::WebServer::start_servers()
{
	std::cout << FT_SETUP << "Starting up Web server" << std::endl;
	std::cout << FT_WARNING << "Press Ctrl + C to stop the Web server." << std::endl;

	int number_of_events;
	int new_conn;
	struct epoll_event events[FT_MAX_EVENT_SIZE];
	struct epoll_event events_setup;

	epoll();
	epollAddServers();

	while (ft::keep())
	{
		number_of_events = epoll_wait(events);
		for (int n = 0; n < number_of_events && ft::keep(); n++)
		{
			if ((new_conn = isServerSideEvent(events[n].data.fd)) != 0)
			{
				::fcntl(new_conn, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
				events_setup.data.fd = new_conn;
				events_setup.events = EPOLLIN;
				if (::epoll_ctl(_epoll, EPOLL_CTL_ADD, new_conn, &events_setup) == -1)
				{
					std::cout << FT_STATUS << "Epoll Ctl status: " << strerror(errno) << std::endl;
					throw EpollCtlException();
				}
			}
			else if (events[n].events & EPOLLIN)
				recv(events[n].data.fd, events_setup);
			else if (events[n].events & EPOLLOUT)
				send(events[n].data.fd, events_setup);
		}
	}
}

const char *ft::WebServer::EpollException::what() const throw()
{
	return (FT_ERROR "Can't create epoll.");
}

const char *ft::WebServer::EpollCtlException::what() const throw()
{
	return (FT_ERROR "Can't manage file descriptor.");
}

const char *ft::WebServer::EpollWaitException::what() const throw()
{
	return (FT_ERROR "Can't wait events.");
}

const char *ft::WebServer::cantGetUserInfoException::what() const throw()
{
	return (FT_ERROR "Can't get user information.");
}

const char *ft::WebServer::needSudoException::what() const throw()
{
	return (FT_ERROR "Sudo required.");
}
