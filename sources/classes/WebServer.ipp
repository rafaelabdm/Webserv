/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:37:17 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/09 13:02:07 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

WS::WebServer::WebServer()
{
	//ler arquivo de configuração...
	//criar servidores de acordo com o arquivo
	//abrir servidores pra conexão
	connections.push_back(new Socket(MY_HOST, MY_PORT));
	connections.push_back(new Socket(MY_HOST, "8081"));
	//pra cada conexão inicial, dar bind e listen...
	start_servers();
	handle_connections();
}

WS::WebServer::~WebServer()
{
	// pra cada coneção dar delete()
}

void	WS::WebServer::start_servers()
{
	std::vector<WS::Socket*>::iterator it;

	for (it = connections.begin(); it != connections.end(); it++)
	{
		(*it)->bind();
		(*it)->listen();
	}
}

void	WS::WebServer::handle_connections()
{

	//poll tem que monitorar todas as conexões e lidar com novas
	while(1)
		connections[0]->accept();
		// connections[1]->accept();
	
}