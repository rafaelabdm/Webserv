/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:55:31 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 12:02:10 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleServer.hpp"

WS::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
	socket = new ListenSocket( domain,  service,  protocol,  port, interface,  bklg);
}

WS::SimpleServer::~SimpleServer()
{
	delete socket;
}