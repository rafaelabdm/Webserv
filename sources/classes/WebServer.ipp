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

ft::WebServer::WebServer(const char *configuration_file, const char **envp)
{
	(void)envp;

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

	// Initializes Ctrl + C signal handler
	ft::keep();

	for (size_t i = 0; ft::keep() && i < _config_file.size(); i++)
		_connections.push_back(new ft::Socket(_config_file.getServer(i)));

	std::vector<ft::Socket *>::iterator it;

	for (it = _connections.begin(); it != _connections.end(); it++)
	{
		(*it)->bind();
		(*it)->listen();
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
	try
	{
		_epoll = epoll_create(1);
		if (_epoll < 0)
			throw EpollException();
	}
	catch (EpollException &e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
	}
}

void ft::WebServer::epollAddServers()
{
	struct epoll_event events_setup;
	std::vector<ft::Socket *>::iterator it;

	events_setup.events = EPOLLIN | EPOLLOUT;
	try
	{
		for (it = _connections.begin(); it != _connections.end(); it++)
		{
			events_setup.data.fd = (*it)->getSock();
			if (epoll_ctl(_epoll, EPOLL_CTL_ADD, (*it)->getSock(), &events_setup) < 0)
				throw EpollCtlException();
		}
	}
	catch (EpollCtlException &e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
	}
}

int ft::WebServer::epoll_wait(struct epoll_event *events)
{
	int nfds;

	try
	{
		nfds = ::epoll_wait(_epoll, events, 10, -1); // 10 = numero maximo de eventos, mudar depois
		if (nfds == -1 && ft::keep())
			throw EpollWaitException();
		return (nfds);
	}
	catch (EpollWaitException &e)
	{
		std::cerr << e.what() << strerror(errno) << std::endl;
		return (-1);
	}
}

int ft::WebServer::isServerSideEvent(int epoll_fd)
{
	std::vector<ft::Socket *>::iterator it;

	std::cout
		<< FT_EVENT
		<< "Server side event happened on fd "
		<< FT_HIGH_LIGHT_COLOR << epoll_fd << RESET_COLOR
		<< "." << std::endl;

	for (it = _connections.begin(); it != _connections.end(); it++)
	{
			if (epoll_fd == (*it)->getSock())
			return ((*it)->accept());
	}
	return (0);
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
	int bytes = 1;

	std::memset(client_buffer, 0, FT_DEFAULT_CLIENT_BUFFER_SIZE);
	while (bytes != -1 && bytes != 0)
	{
		bytes = ::recv(client_fd, client_buffer, sizeof(client_buffer), 0);
		if (bytes > 0)
		{
			std::cout << FT_EVENT << "Receiving " << bytes
				<< ((bytes <= 1)? " byte.": " bytes.")
				<< std::endl;
			total_request.append(client_buffer, bytes);
		}
	}
	std::cout << FT_EVENT << total_request.length()
		<< ((total_request.length() <= 1)? " byte": " bytes")
		<< " received."
		<< std::endl;
	// std::cout << "REQUEST:\n" << total_request << std::endl;

	//----------------------TEST-------------------------------
	if (total_request.length() > 0)
	{
		Request request(total_request);
		Response response(request, _connections);
		std::string msg = response.getResponse();
		::send(client_fd, msg.data(), msg.length(), 0);
	}
	events_setup.data.fd = client_fd;
	epoll_ctl(_epoll, EPOLL_CTL_DEL, client_fd, &events_setup);
	close(client_fd);

	//---------------------------------------------------------

	// events_setup.events = EPOLLOUT;
	// epoll_ctl(_epoll, EPOLL_CTL_MOD, client_fd, &events_setup);
}

void ft::WebServer::send(int client_fd, struct epoll_event &events_setup)
{
	std::cout << YELLOW << "hello from write" << RESET_COLOR << std::endl;

	std::string msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

	::send(client_fd, msg.data(), msg.length(), 0);

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
	struct epoll_event events[10]; // 10 = numero maximo de eventos, mudar depois
	struct epoll_event events_setup;

	epoll();
	epollAddServers();

	while (ft::keep())
	{
		number_of_events = epoll_wait(events);
		for (int n = 0; n < number_of_events; n++)
		{
			if ((new_conn = isServerSideEvent(events[n].data.fd)) != 0)
			{
				fcntl(new_conn, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
				events_setup.data.fd = new_conn;
				events_setup.events = EPOLLIN;
				if (epoll_ctl(_epoll, EPOLL_CTL_ADD, new_conn, &events_setup) == -1)
					throw EpollCtlException();
			}
			else if (events[n].events & EPOLLIN)
				recv(events[n].data.fd, events_setup);
			// else if (events[n].events & EPOLLOUT)
			// 	send(events[n].data.fd, events_setup);
		}
	}
}

const char *ft::WebServer::EpollException::what() const throw()
{
	return (FT_ERROR "epoll error: ");
}

const char *ft::WebServer::EpollCtlException::what() const throw()
{
	return (FT_ERROR "epoll_ctl error: ");
}

const char *ft::WebServer::EpollWaitException::what() const throw()
{
	return (FT_ERROR "epoll_wait error: ");
}
