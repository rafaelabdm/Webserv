/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.ipp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:15:39 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/31 11:38:14 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

ft::Response::Response(ft::Request& request, std::vector<ft::Socket*>& servers): _request(request), _server(setServer(servers))
{
	checkProtocol();
	checkEndpoint();
	std::cout << "Request for server " << _request.getHost() << " is being processed." << std::endl;
}

ft::Response::~Response()
{
}


//	esboço da resposta 
std::string ft::Response::getResponse()
{
	std::string response = "";

	response.append("HTTP/1.1 ");
	response.append(_status_code);
	// response.append(" ");
	// response.append(_status_msgs[_status_code]);
	response.append("\nContent-Type: ");
	response.append(_content_type);
	response.append("\nContent-Length: ");
	response.append(_content_length);
	response.append("\nServer: ");
	response.append(_request.getHost());
	response.append("\nDate: ");
	response.append(_date);
	response.append("\nConnection: ");
	response.append(_connection_type);
	response.append("\n\n");
	response.append(_body);
	
	return (response);
}

ft::Socket	ft::Response::setServer(std::vector<ft::Socket*>& servers)
{
	std::vector<ft::Socket*>::iterator it;
	std::vector<std::string> hosts;

	for (it = servers.begin(); it != servers.end(); it++)
	{
		hosts = (*it)->getHosts();
		for (long unsigned int i = 0; i < hosts.size(); i++)
		{
			if (hosts[i] == _request.getHost())
				return (*(*it));
		}
	}
	throw ft::Response::ServerNotFoundException();
}

void	ft::Response::checkProtocol()
{
	if (_request.getProtocol() != "HTTP/1.1")
		throw ft::Response::WrongProtocolException();
	return ;
}

void	ft::Response::checkEndpoint()
{
	// std::vector<t_server_locations> locations = _server.locations;
	
	// for (int i = 0; i < locations.size(); i++)
	// {
	// 	if (locations[i]._endpoint == _request.getEndpoint())
	// 	{
	// 		//show -> guardar location para montar a response
	// 		return ;
	// 	}
	// }
	// _status_code = "404"; //not found
}

const char* ft::Response::ServerNotFoundException::what() const throw()
{
	return (FT_FAIL "server not found :/");
}

const char* ft::Response::WrongProtocolException::what() const throw()
{
	return (FT_FAIL "Protocol not accepted");
}
