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

#include <help_option.hpp>
#include <messages.hpp>
#include <WebServer.hpp>
#include <Request.hpp>

/**
 * @brief Verify the number of arguments
 * 
 * @param argc Number of arguments
 * @return true if argc is bigger than 2
 * @return false if is equal or lower than 2
 */
static bool	check_argc(const int argc)
{
	if (argc > 2)
		std::cout << FT_MANY_ARGS << std::endl;

	return (argc > 2);
}

int	main(const int argc, const char** argv, const char** envp)
{
	if (ft::help_option(argv))
		return (0);

	if (check_argc(argc))
		return (1);

	std::string	configuration_file;
	configuration_file = (argc == 1 ? FT_DEFAULT_CONFIG_FILE : argv[1]);
	ft::WebServer	ws(configuration_file.c_str());

	ws.start_servers();

	return (0);
	(void) envp;
}

// int main(void)
// {
// 	char buffer[300];

// 	int fd = open("/home/rabustam/42sp/wb_main/examples/request_test", O_RDONLY);
// 	if (fd < 0)
// 		return (42);
// 	read(fd, &buffer, 300);

// 	ft::Request req(buffer);
// }
