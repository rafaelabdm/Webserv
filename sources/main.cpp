/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:50:42 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/03 09:44:50 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

//c++ -Wall -Wextra -Werror -std=c++98 src/main.cpp src/Socket.cpp -o webserv

int	main(void)
{
	WS::Socket sk("rabustam.42.fr", "8080");
	// WS::Socket sk;
	sk.bind();
	sk.listen();
	while(1)
		sk.accept();
	// sk.connect();
}