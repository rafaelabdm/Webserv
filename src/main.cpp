/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:50:42 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/02 13:19:49 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Socket.hpp"

//c++ -Wall -Wextra -Werror src/main.cpp src/Socket.cpp -o webserv

int	main(void)
{
	WS::Socket sk("3490");
	// WS::Socket sk;
	sk.bind();
	sk.listen();
	while(1)
		sk.accept();
	// sk.connect();
}