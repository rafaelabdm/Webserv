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
#include <valid_argc.hpp>
#include <WebServer.hpp>
#include <Request.hpp>

// int	main(const int argc, const char** argv)
// {
// 	// Initial checks
// 	{
// 		if (ft::help_option(argv[1]))
// 			return (0);

// 		if (!ft::valid_argc(argc))
// 			return (1);
// 	}

// 	// Main Web server stuffs
// 	ft::WebServer	ws(argv[1]);

// 	ws.start_servers();

// 	return (0);
// }

int main(void)
{
	char buffer[300];

	int fd = open("/home/rabustam/42sp/wb_main/examples/request_test", O_RDONLY);
	if (fd < 0)
		return (42);
	read(fd, &buffer, 300);

	ft::Request req(buffer);
}
