/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_option.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:33:36 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/11 21:33:36 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <help_option.hpp>

static void	print_help_message(void)
{
	std::cout << "Usage: ./webserv [<Configuration File>.conf] \n";
	std::cout << "   or: ./webserv \n\n";
	std::cout << "A HTTP server in C++ 98 \n\n";
	std::cout << "	-h, --help	display this help page and exit. \n\n";
	std::cout << "By default, \"./examples/webserv.conf\" will load if no ";
	std::cout << "configuration file is provided. \n\n";
	std::cout << "More about this project can be found on \n";
	std::cout << "https://github.com/rafaelabdm/Webserv/";
	std::cout << std::endl;
}

bool	ft::help_option(const char** options)
{
	if (!options)
		return (false);

	for (int i = 0; options[i]; i++)
	{
		const std::string	str_option = options[i];

		if (str_option == "-h" || str_option == "--help")
		{
			print_help_message();

			return (true);
		}
	}

	return (false);
}
