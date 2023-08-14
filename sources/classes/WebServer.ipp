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

ft::WebServer::WebServer(const std::string& config_file) : _config_file(config_file)
{
	std::cout
		<< FT_SETUP
		<< "Setting up Web server from "
		<< GREEN << config_file << RESET_COLOR
		<< " file."
		<< std::endl;

	for (size_t i = 0; ft::keep() && i < _config_file.size(); i++)
		_connections.push_back(Socket(_config_file.getHost(i), _config_file.getPort(i)));
}

ft::WebServer::~WebServer()
{
	std::cout << FT_CLOSE << "Closing Web server." << std::endl;

	std::cout << FT_OK << "Web server closed." << std::endl;
}

void	ft::WebServer::start_servers()
{
	std::cout << FT_SETUP << "Starting up Web server" << std::endl;

	std::cout << FT_OK << "Web server ready to rock!" << std::endl;

	std::cout
		<< FT_WARNING << "Press Ctrl + C to stop the Web server." << std::endl;
}
