/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 18:24:26 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 18:24:26 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ConfigFile.hpp>

int	main(void)
{
	try
	{
		ft::ConfigFile	config("webserv.conf");

		// std::cout << config;
		// std::cout << config.size() << std::endl;

		// std::cout << config.getServers();
		// std::cout << config.getServer(0);

		// std::cout << config.getPort(0) << std::endl;
		// std::cout << config.getServerNames(0) << std::endl;
		// std::cout << config.getServerName(0, 0) << std::endl;
		// std::cout << config.getErrorPages(0) << std::endl;
		// std::cout << config.getErrorPage(0, "404") << std::endl;

		// std::cout << config.getLocations(0);
		// std::cout << config.getLocation(0, 0);

		// std::cout << config.getLocationEndpoint(0, 1) << std::endl;
		// std::cout << config.getLocationRoot(0, 0) << std::endl;
		// std::cout << config.getLocationRedirect(0, 2) << std::endl;
		// std::cout << config.getLocationIndexes(0, 0) << std::endl;
		// std::cout << config.getLocationIndex(0, 0, 0) << std::endl;
		// std::cout << ((config.getLocationUploadEnabled(0, 3) == true)? "true": "false") << std::endl;
		// std::cout << config.getLocationUploadDir(0, 3) << std::endl;
		// std::cout << ((config.getLocationCgiEnabled(0, 4) == true)? "true": "false") << std::endl;
		// std::cout << config.getLocationCgiDir(0, 4) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Webserv can't work in an unsafe environment." << std::endl;
	}

	return (0);
}
