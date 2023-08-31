/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:32:11 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/10 09:17:02 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

//C
# include <dirent.h>
// # include <poll.h>
# include <sys/epoll.h>

//C++98
# include <fstream>
# include <iostream>
# include <vector>

//Classes
# include "ConfigFile.hpp"
# include "Request.hpp"
# include "Socket.hpp"

//my headers
# include "colors.hpp"
# include "messages.hpp"
# include "signal_handler.hpp"

# define FT_DEFAULT_CONFIG_FILE "./examples/webserv.conf"

namespace ft
{
	class WebServer
	{
		private:
		ft::ConfigFile				_config_file;
		std::vector<ft::Socket*>	_connections;
		int							_epoll;


		void	epoll();
		void	epollAddServers();
		int		epoll_wait(struct epoll_event* events);

		int		isServerSideEvent(int epoll_fd);
		void	recv(int client_fd, struct epoll_event& events_setup);
		void	send(int client_fd, struct epoll_event& events_setup);


		std::string		get_page();

		public:
		WebServer(const std::string& config_file);
		~WebServer();
		void	start_servers();

		class	EpollException : std::exception
		{
			public:
			const char* what() const throw();
		};

		class	EpollCtlException : std::exception
		{
			public:
			const char* what() const throw();
		};

		class	EpollWaitException : std::exception
		{
			public:
			const char* what() const throw();
		};
	};
}

# include "WebServer.ipp"

#endif /* WebServer_hpp */