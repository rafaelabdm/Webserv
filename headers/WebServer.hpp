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

# include <colors.hpp>
# include "ConfigFile.hpp"
# include <iostream>
# include <messages.hpp>
# include <signal_handler.hpp>
# include "Socket.hpp"
# include <vector>

namespace ft
{
	class WebServer
	{
		private:
		ft::ConfigFile			_config_file;
		std::vector<ft::Socket>	_connections;

		public:
		WebServer(const std::string& config_file);
		~WebServer();
		void	start_servers();
	};
}

# include "WebServer.ipp"

#endif /* WebServer_hpp */