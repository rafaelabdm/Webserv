/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:54:26 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 11:34:46 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListenSocket.hpp"

WS::ListenSocket::ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bklg)
	: WS::BindSocket(domain, service, protocol, port, interface)
{
	backlog = bklg;
	start_listen();
	test_connection(listening);
}

WS::ListenSocket::~ListenSocket()
{
}

void	WS::ListenSocket::start_listen()
{
	listening = listen(sock, backlog);
}

