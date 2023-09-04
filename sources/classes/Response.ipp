/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.ipp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:15:39 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/04 13:22:12 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

ft::Response::Response(ft::Request& request, std::vector<ft::Socket*>& servers): _request(request), _server(setServer(servers))
{
	std::cout << "Request for server " << _request.getHost() << " is being processed." << std::endl;
	checkProtocol();
	if (!checkEndpoint() || !checkMethod())
	{
		handleNotFound();
		return ;
	}
	if (checkRedirect())
		return ;
	processRequest();
	std::cout << "Request for server " << _request.getHost() << " was processed." << std::endl;
}

ft::Response::~Response()
{
}


//	retorno da classe Response para o WebServer
std::string ft::Response::getResponse()
{
	std::string response = "";

	response.append("HTTP/1.1 ");
	response.append(_status_code);
	// response.append(" ");
	// response.append(_status_msgs[_status_code]);
	response.append("\nLocation: ");
	response.append(_location.endpoint);
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

ft::t_server_config ft::Response::setServer(std::vector<ft::Socket*>& servers)
{
	std::vector<ft::Socket*>::iterator it;
	std::vector<std::string> hosts;

	for (it = servers.begin(); it != servers.end(); it++)
	{
		hosts = (*it)->getHosts();
		for (long unsigned int i = 0; i < hosts.size(); i++)
		{
			if (hosts[i] == _request.getHost())
				return ((*it)->getServer());
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

bool	ft::Response::checkEndpoint()
{
	std::vector<t_location_config> locations = _server.locations;

	for (long unsigned int i = 0; i < locations.size(); i++)
	{
		if (locations[i].endpoint == _request.getEndpoint())
		{
			_location = locations[i];
			return (true);
		}
	}
	_status_code = "404"; //not found
	return (false);
}

std::string ft::Response::numberToString(int size)
{
    std::stringstream length;
    std::string str;

    length << size;
	str = length.str();
    return str;
}


void	ft::Response::handleNotFound()
{
	_content_type = "text/html";
	_date = "";
	_connection_type = "Keep-alive";
	_body = getErrorPage();
	_content_length = numberToString(_body.size());
}

std::string	ft::Response::getErrorPage()
{
	std::string error_page = _server.error_pages[_status_code];
	std::string path = ERROR_PAGE_PATH;
	path.append(error_page);
	std::ifstream file(path.c_str());

	std::string page;
	std::string line;
	while(std::getline(file, line))
	{
		page.append(line);
		page.append("\n");
	}
	return page;
}

std::string	ft::Response::getPage()
{
	DIR*			dr;
	struct dirent*	en;
	std::string		path_to_dir = "./";
	
	path_to_dir.append(_location.root);
	dr = opendir(path_to_dir.data());
	if( dr == NULL )
	{
		// throw ft::Response::RootNotFpundException();
		std::cout << "ERROR: DIR NOT FOUND" << std::endl;
	}
	std::cout << _location.indexes[0] << std::endl;
		
	for(int i = 0; ft::keep() && en->d_name != _location.indexes[0]; i++) {
		en = readdir(dr);
		if (en == NULL)
		{
			// throw ft::Response::PageNotFpundException();
			std::cout << "ERROR: FILE NOT FOUND" << std::endl;
		}
	}

	path_to_dir.append("/");
	std::ifstream file(path_to_dir.append(en->d_name).c_str());
	closedir(dr);

	std::string page = "";
	std::string line;
	while(std::getline(file, line))
	{
		page.append(line);
		page.append("\n");
	}
	return page;
}

bool	ft::Response::checkMethod()
{
	if (_location.allowed_methods_get && _request.getMethod() == "GET")
		return (true);
	if (_location.allowed_methods_post && _request.getMethod() == "POST")
		return (true);
	if (_location.allowed_methods_delete && _request.getMethod() == "DELETE")
		return (true);
	_status_code = "405"; //method not allowed
	return (false);
}

bool	ft::Response::checkRedirect()
{
	if (_location.redirect != "")
	{
		_status_code = "301"; //moved permanently
		_content_length = "0";
		return (true);
	}
	return (false);
}

void	ft::Response::processRequest()
{
	if (_request.getMethod() == "GET")
	{
		_body = getPage();
		_content_type = "text/html"; //depois ver como vamos checar isso pra devolver
		_content_length = numberToString(_body.size());
	}
	else if (_request.getMethod() == "POST")
	{
		//checkBody(); -> body size && content_type
		//se o size > tamanho maximo, retorna 413 #request-entity-too-large
		//se o content type != do aceito, retorna 415 #unsupported-media-type
		saveBodyContent();
	}
	else if (_request.getMethod() == "DELETE")
	{
		
	}
	
}

void	ft::Response::saveBodyContent()
{
	std::string body = _request.getBody();
	
	size_t	start;
	size_t	end;

	start = body.find("filename=", 0) + 10;
	end = body.find("\"", start);
	
	std::string	file_name = "./examples/";
	file_name.append(body.substr(start, end - start));

	start = body.find("PNG", 0) - 1;

	std::ofstream	file;
	file.open(file_name.data(), std::ios::binary);
	file << body.substr(start, body.length() - start);
	file.close();
}

const char* ft::Response::ServerNotFoundException::what() const throw()
{
	return (FT_FAIL "server not found :/");
}

const char* ft::Response::WrongProtocolException::what() const throw()
{
	return (FT_FAIL "Protocol not accepted");
}
