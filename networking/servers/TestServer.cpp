/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:08:25 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 13:10:18 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"

WS::TestServer::TestServer()
	: WS::SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
	launch_server();
}

WS::TestServer::~TestServer()
{
	
}

void WS::TestServer::accept_socket()
{
	struct sockaddr_in addr = socket->get_address();
	int addr_len = sizeof(addr);
	new_socket = accept(socket->get_sock(), (struct sockaddr *) &addr, (socklen_t *)&addr_len);
	read(new_socket, buffer, 30000);
}

void WS::TestServer::handle_socket()
{
	std::cout << buffer << std::endl;
}

void WS::TestServer::answer_socket()
{
	std::string hello = "Hello from server!";
	write(new_socket, hello.data(), hello.length());
	close(new_socket);
}

void WS::TestServer::launch_server()
{
	while (true)
	{
		std::cout << "Waiting for connection..." << std::endl;
		accept_socket();
		handle_socket();
		answer_socket();
		std::cout << "=============DONE============" << std::endl;
	}
}
