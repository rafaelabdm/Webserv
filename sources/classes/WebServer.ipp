/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServer.ipp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:37:17 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/10 11:20:55 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServer.hpp"

WS::WebServer::WebServer()
{
	//ler arquivo de configuração...
	//criar servidores de acordo com o arquivo
	//abrir servidores pra conexão
	connections.push_back(new Socket(MY_HOST, MY_PORT));
	// connections.push_back(new Socket(MY_HOST, "8081"));
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

struct pollfd	*remove_pollfds(struct pollfd	*old_pollfds, int& fd_count, int fds_position)
{
	struct pollfd	*new_pollfds;
	
	fd_count--;
	new_pollfds = new struct pollfd[fd_count];
	for (int i = 0; i < fd_count; i++)
	{
		if (i != fds_position)
			new_pollfds[i] = old_pollfds[i];
	}
	delete[] old_pollfds;
	return (new_pollfds);
}

struct pollfd	*realloc_pollfds(struct pollfd	*old_pollfds, int& fd_count, int new_socket)
{
	struct pollfd	*new_pollfds;
	
	std::cout << "Realocando..." << std::endl;
	new_pollfds = new struct pollfd[fd_count + 1];
	for (int i = 0; i < fd_count; i++)
	{
		new_pollfds[i] = old_pollfds[i];
	}
	new_pollfds[fd_count].fd = new_socket;
	new_pollfds[fd_count].events = POLLIN;
	(fd_count)++;
	delete[] old_pollfds;
	return (new_pollfds);
}

void	WS::WebServer::handle_connections()
{

	int				fd_count = 1; //1
	struct pollfd	*pfds = new struct pollfd[fd_count];
	int				num_events;
	int				new_socket = -1;
	char			client_buf[256];
	std::string		msg = "Hello There, from your server!\n";

	pfds[0].fd = connections[0]->getSock();
	pfds[0].events = POLLIN; // Tell me when ready to read


	while(1)
	{
		std::cout << "LOOP 1" << std::endl;
		num_events = poll(pfds, fd_count, 10000);
		if (num_events == -1)
		{
			std::cout << "LOOP 1 error" << std::endl;
			exit(9);
		}
		for (int i = 0; i < fd_count; i++)
		{
			std::cout << "LOOP 2 ==> fd[" << pfds[i].fd << "]" << std::endl;
			if (pfds[i].revents & POLLIN)
			{
				if (pfds[i].fd == connections[0]->getSock())
				{
					new_socket = connections[0]->accept();
					pfds = realloc_pollfds(pfds, fd_count, new_socket);
				} 
				else
				{
					std::cout << "RECV CONNECTION" <<std::endl;
					int nbytes = recv(pfds[i].fd, client_buf, sizeof(client_buf), 0);
					int sender_fd = pfds[i].fd;
					if (nbytes <= 0)
					{
						if (nbytes == 0)
							std::cout << "pollserver: socket[" << sender_fd << "] hung up\n" << std::endl;
						else
							std::cout << "recv error: " << strerror(errno) << std::endl;
						close(pfds[i].fd);
						pfds = remove_pollfds(pfds, fd_count, i);
					}
					else
					{
						for(int j = 0; j < fd_count; j++)
						{
							int dest_fd = pfds[j].fd;
							if (dest_fd != connections[0]->getSock())
							{
								std::cout << "SEND" << std::endl;
								if(send(dest_fd, msg.data(), msg.length(), 0) == -1)
								{
									std::cout << "error: " << strerror(errno) << std::endl;
								}
								close(dest_fd);
								pfds = remove_pollfds(pfds, fd_count, i);
							}
						}
					}
				}
			}
		}
	}
}