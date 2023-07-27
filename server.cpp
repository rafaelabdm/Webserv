/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:06:20 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 12:51:23 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ws_library.hpp"

// PORTAS ABAIXO DE 1024 PRECISA DE PERMISSÃO ROOT/SUDO
// sudo ./webserv
int	main(void)
{
	//SOCKET CONNECTION TEST
	// std::cout << "Starting Listen Socket..." << std::endl;
	// WS::ListenSocket ls = WS::ListenSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
	// std::cout << "Success!!!" << std::endl;

	//SERVER
	WS::TestServer ts;
	return (0);	
}