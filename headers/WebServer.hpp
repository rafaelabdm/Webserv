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
# include <poll.h>

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

namespace ft
{
	class WebServer
	{
		private:
		ft::ConfigFile				_config_file;
		std::vector<ft::Socket*>	_connections;
		std::string					get_page();

		public:
		WebServer(const std::string& config_file);
		~WebServer();
		void	start_servers();

		class	PollException : std::exception
		{
			public:
			const char* what() const throw();
		};
	};

	struct pollfd	*realloc_pollfds(struct pollfd	*old_pollfds, int& fd_count, int new_socket);
	struct pollfd	*remove_pollfds(struct pollfd	*old_pollfds, int& fd_count, int fds_position);
}

# include "WebServer.ipp"

#endif /* WebServer_hpp */