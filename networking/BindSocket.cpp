/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:29:42 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 10:44:57 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindSocket.hpp"

WS::BindSocket::BindSocket(int domain, int service, int protocol, int port, u_long interface)
	: WS::SimpleSocket(domain, service, protocol, port, interface)
{
	connection = network_connection(sock, address);
	test_connection(connection);
}

WS::BindSocket::~BindSocket()
{	
}

int	WS::BindSocket::network_connection(int sock, struct sockaddr_in address)
{
	return bind(sock, (struct sockaddr*)&address, sizeof(address));
}