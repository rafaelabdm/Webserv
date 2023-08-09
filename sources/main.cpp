/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:50:42 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/09 12:26:58 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

//c++ -Wall -Wextra -Werror -std=c++98 src/main.cpp src/Socket.cpp -o webserv

int	main(void)
{
	try
	{
		WS::Socket sk("localhost", "8000");
		sk.bind();
		sk.listen();
		while(1)
			sk.accept();
	}
	catch (WS::Socket::SocketException &e)
	{
		std::cout << e.what() << std::endl;
	}
	
}