/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:37:29 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 10:44:48 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ConnectSocket.hpp"

WS::ConnectSocket::ConnectSocket(int domain, int service, int protocol, int port, u_long interface)
	: WS::SimpleSocket(domain, service, protocol, port, interface)
{
	connection = network_connection(sock, address);
	test_connection(connection);
}

WS::ConnectSocket::~ConnectSocket()
{
}

int	WS::ConnectSocket::network_connection(int sock, struct sockaddr_in address)
{
	return connect(sock, (struct sockaddr*)&address, sizeof(address));
}