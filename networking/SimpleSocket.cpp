/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:10:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/21 11:05:22 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleSocket.hpp"

WS::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface)
{
	address.sin_family = domain;
	address.sin_port = htons(port); //converter os bites da ordem do host para a ordem da rede (network)
	address.sin_addr.s_addr = htonl(interface);
	sock = socket(domain, service, protocol);
	test_connection(sock);
	connection = network_connection(sock, address);
	test_connection(connection);
}

void WS::SimpleSocket::test_connection(int connection_to_test)
{
	if (connection_to_test < 0)
	{
		perror("Failed to connect...");
		exit(EXIT_FAILURE);
	}
}

struct sockaddr_in  WS::SimpleSocket::get_address()
{
	return (address);
}

int WS::SimpleSocket::get_sock()
{
	return (sock);
}

int WS::SimpleSocket::get_connection()
{
	return (connection);
}