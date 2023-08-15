/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:32:11 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/15 10:30:42 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include "Socket.hpp"
# include <vector>
# include <poll.h>


#include <dirent.h>
#include <fstream>
#include <string>
namespace WS
{
	class WebServer
	{
		private:
		std::vector<WS::Socket*>	connections; //lista de conexões
		std::string						get_page();

		public:
		WebServer();
		~WebServer();
		void	start_servers();
		void	handle_connections();
	};
}

# include "WebServer.ipp"

#endif /* WebServer_hpp */