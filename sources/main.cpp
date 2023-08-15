/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:50:42 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/15 10:23:51 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include "WebServer.hpp"
#include "Request.hpp"


//c++ -Wall -Wextra -Werror -std=c++98 src/main.cpp src/Socket.cpp -o webserv

int	main(void)
{
	WS::WebServer server;
	// try
	// {
	// 	WS::Socket sk("localhost", "8000");
	// 	sk.bind();
	// 	sk.listen();
	// 	while(1)
	// 		sk.accept();
	// }
	// catch (WS::Socket::SocketException &e)
	// {
	// 	std::cout << e.what() << std::endl;
	// }
	// char buf[225] = "GET / HTTP/1.1\n bla bla bla";
	// WS::Request req(buf);
}