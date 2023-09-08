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

#include <check_argc.hpp>
#include <help_option.hpp>
#include <WebServer.hpp>

int main(const int argc, const char **argv, const char **envp)
{
	if (ft::help_option(argv))
		return (0);

	if (ft::check_argc(argc))
		return (1);

	try
	{
		ft::WebServer ws(argv[1], envp);

		ws.start_servers();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::cout
			<< "Webserv can't operate in an unsafe environment." << std::endl;
	}

	return (0);
}
