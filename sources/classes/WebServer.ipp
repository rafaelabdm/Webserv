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

ft::WebServer::WebServer(const std::string& config_file) : _config_file(config_file)
{
	std::cout
		<< FT_SETUP
		<< "Setting up Web server from "
		<< GREEN << config_file << RESET_COLOR
		<< " file."
		<< std::endl;

	for (size_t i = 0; ft::keep() && i < _config_file.size(); i++)
		_connections.push_back(new ft::Socket(_config_file.getServer(i)));

	std::vector<ft::Socket*>::iterator it;

	for (it = _connections.begin(); it != _connections.end(); it++)
	{
		(*it)->bind();
		(*it)->listen();
	}
}

ft::WebServer::~WebServer()
{
	std::cout << FT_CLOSE << "Closing Web server." << std::endl;

	std::vector<ft::Socket*>::iterator it;

	for (it = _connections.begin(); it != _connections.end(); it++)
		delete *it;

	std::cout << FT_OK << "Web server closed." << std::endl;
}

void	ft::WebServer::start_servers()
{
	std::cout << FT_SETUP << "Starting up Web server" << std::endl;

	int				fd_count = 1; //1
	struct pollfd	*pfds = new struct pollfd[fd_count];
	int				num_events;
	int				new_socket = -1;
	char			client_buf[256];

	// memset(pfds, 0 , sizeof(pfds));
	pfds[0].fd = _connections[0]->getSock();
	pfds[0].events = POLLIN; // Tell me when ready to read

	while(ft::keep())
	{
		std::cout << "LOOP 1" << std::endl;

		try
		{
			num_events = poll(pfds, fd_count, (3 * 60 * 1000));
			if (num_events == -1)
				throw PollException();
			std::cout << FT_OK << "Loop 1 is fine." << std::endl;
			for (int i = 0; ft::keep() && i < fd_count; i++)
			{
				std::cout << "LOOP 2 ==> fd[" << pfds[i].fd << "]" << std::endl;

				if (pfds[i].revents & POLLIN)
				{
					if (pfds[i].fd == _connections[0]->getSock())
					{
						new_socket = _connections[0]->accept();
						if (new_socket < 0)
						{
							if (errno != EWOULDBLOCK)
							{
								perror("  accept() failed");
							}
							break;
						}
						pfds = realloc_pollfds(pfds, fd_count, new_socket);
					}
					else
					{
						std::cout << "RECV CONNECTION" <<std::endl;
						int nbytes = recv(pfds[i].fd, client_buf, sizeof(client_buf), 0);
						std::cout << client_buf << std::endl;
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
							for(int j = 0; ft::keep() && j < fd_count; j++)
							{
								int dest_fd = pfds[j].fd;
								if (dest_fd != _connections[0]->getSock())
								{
									std::cout << "SEND" << std::endl;
									// std::string msg = get_page();
									std::string msg = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
									if(send(dest_fd, msg.data(), msg.length(), 0) == -1)
									{
										std::cout << "error: " << strerror(errno) << std::endl;
									}
								}
							}
						}
					}
				}
			}
		}
		catch (PollException& e)
		{
			std::cerr << e.what() << std::endl;
			break;
		}
	}

	std::cout << FT_OK << "Web server ready to rock!" << std::endl;

	std::cout
		<< FT_WARNING << "Press Ctrl + C to stop the Web server." << std::endl;
}

std::string	ft::WebServer::get_page()
{
	// std::string page;
	DIR *dr;
	struct dirent *en;
	std::string path = "./examples/";
	
	dr = opendir("./examples/");
	// en = readdir(dr);
	if( dr != NULL ) {
			for(int i = 0;ft::keep() && i < 3; i++) {
				en = readdir( dr );
				if( en == NULL ) break;

				std::cout << "[" << en->d_name << "]\n";
				// printf( "%s\n", direntp->d_name );
			}
	}
	std::ifstream file(path.append(en->d_name).c_str());
	closedir(dr);

// HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!
//    std::string page = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
   std::string page = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 12\n\n";
   std::string line;
   while(std::getline(file, line))
   {
		page.append(line);
		page.append("\n");
   }
   return page;
}

struct pollfd	*ft::realloc_pollfds(struct pollfd	*old_pollfds, int& fd_count, int new_socket)
{
	struct pollfd	*new_pollfds;
	
	std::cout << "Realocando..." << std::endl;
	new_pollfds = new struct pollfd[fd_count + 1];
	for (int i = 0; i < fd_count; i++)
	{
		new_pollfds[i] = old_pollfds[i];
	}
	new_pollfds[fd_count].fd = new_socket;
	new_pollfds[fd_count].revents = POLLIN;
	(fd_count)++;
	delete[] old_pollfds;
	return (new_pollfds);
}

struct pollfd	*ft::remove_pollfds(struct pollfd	*old_pollfds, int& fd_count, int fds_position)
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

const char* ft::WebServer::PollException::what() const throw()
{
	return (FT_FAIL "LOOP 1 error");
}