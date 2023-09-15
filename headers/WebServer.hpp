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
#define WEBSERVER_HPP

#include <dirent.h>
#include <sys/epoll.h>
#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "ConfigFile.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "Socket.hpp"

#include "colors.hpp"
#include "messages.hpp"
#include "signal_handler.hpp"

#define FT_DEFAULT_CONFIG_FILE "./configurations/my_server.conf"
#define FT_DEFAULT_CLIENT_BUFFER_SIZE 1024
#define FT_MAX_EVENT_SIZE 100

namespace ft
{
	class WebServer
	{
	private:
		ft::ConfigFile _config_file;
		std::vector<ft::Socket *> _connections;
		std::map<int, std::string> _request_list;
		int _epoll;
		bool _is_sudo;

		void epoll();
		void epollAddServers();
		int epoll_wait(struct epoll_event *events);

		void checkSudo();

		int isServerSideEvent(int epoll_fd);
		void recv(int client_fd, struct epoll_event &events_setup);
		void send(int client_fd, struct epoll_event &events_setup);

		int			getRequestTotalLength(std::string request);
		std::string getBoundry(std::string request);

	public:
		WebServer(const char *configuration_file);
		~WebServer();
		void start_servers();

		class EpollException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class EpollCtlException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class EpollWaitException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class cantGetUserInfoException : public std::exception
		{
		public:
			const char *what() const throw();
		};

		class needSudoException : public std::exception
		{
		public:
			const char *what() const throw();
		};
	};
}

#include "WebServer.ipp"

#endif /* WebServer_hpp */