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

int	main(const int argc, const char** argv, const char** envp)
{
	if (ft::help_option(argv))
		return (0);

	if (ft::check_argc(argc))
		return (1);

	std::string	configuration_file;
	configuration_file = (argc == 1 ? FT_DEFAULT_CONFIG_FILE : argv[1]);
	ft::WebServer	ws(configuration_file.c_str());

	ws.start_servers();

	return (0);
	(void) envp;
}
