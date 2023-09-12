/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.ipp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:15:39 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/12 16:18:43 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

ft::Response::Response(ft::Request &request, std::vector<ft::Socket *> &servers) : _request(request), _server(setServer(servers))
{
	std::cout
		<< FT_EVENT
		<< "Request for server "
		<< FT_HIGH_LIGHT_COLOR << _request.getHost() << RESET_COLOR
		<< " is being processed."
		<< std::endl;

	checkProtocol();
	if (!checkEndpoint())
		return;
	if (!checkMethod())
		return;
	if (checkRedirect())
		return;
	if (checkAutoindex())
		return;
	processRequest();

	std::cout
		<< FT_OK
		<< "Request for server "
		<< FT_HIGH_LIGHT_COLOR << _request.getHost() << RESET_COLOR
		<< " was processed."
		<< std::endl;
}

ft::Response::~Response()
{
}

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

ft::t_server_config ft::Response::setServer(std::vector<ft::Socket *> &servers)
{
	std::vector<ft::Socket *>::iterator it;
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

void ft::Response::checkProtocol()
{
	if (_request.getProtocol() != "HTTP/1.1")
		throw ft::Response::WrongProtocolException();
	return;
}

bool ft::Response::checkEndpoint()
{
	std::vector<t_location_config>	locations = _server.locations;
	size_t 							pos = _request.getEndpoint().find("/", 1);
	
	if (pos == std::string::npos)
		pos = _request.getEndpoint().length();
	for (long unsigned int i = 0; i < locations.size(); i++)
	{
		if (_request.getEndpoint().compare(0, pos, locations[i].endpoint) == 0)
		{
			_location = locations[i];
			return (true);
		}
	}
	_status_code = FT_STATUS_CODE_404;
	handleNotFound();
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

void ft::Response::handleNotFound()
{
	_content_type = "text/html";
	_date = "";
	_connection_type = "Keep-alive";
	_body = getErrorPage();
	_content_length = numberToString(_body.size());
}

std::string ft::Response::getErrorPage()
{
	std::string error_page = _server.error_pages[_status_code];
	std::string path = FT_ERROR_PAGE_PATH;
	if (error_page == "")
		path.append(FT_DEFAULT_404_PAGE);
	else
		path.append(error_page);
	std::ifstream file(path.c_str());

	std::string page;
	std::string line;
	while (std::getline(file, line))
	{
		page.append(line);
		page.append("\n");
	}
	return page;
}

bool ft::Response::checkIndexes(std::string file_name)
{
	for (long unsigned int i = 0; i < _location.indexes.size(); i++)
	{
		if (file_name == _location.indexes[i])
			return (true);
	}
	return (false);
}

std::string ft::Response::getPage()
{
	DIR *dr;
	struct dirent *en;
	std::string path_to_dir = "./";
	std::string resource = "";

	path_to_dir.append(_location.root);
	dr = opendir(path_to_dir.data());
	if (dr == NULL)
	{
		std::cout << FT_WARNING << "Directory not found" << std::endl;
		_status_code = FT_STATUS_CODE_404;
		return (getErrorPage());
	}

	if (_request.getEndpoint() != _location.endpoint)
		resource = _request.getEndpoint().substr(_location.endpoint.length() + 1, _request.getEndpoint().length() - _location.endpoint.length() - 1);
	
	while (ft::keep() && (en = readdir(dr)) != NULL)
	{
		if (resource != "" ? resource == en->d_name : checkIndexes(en->d_name))
			break ;
	}
	
	if (en == NULL)
	{
		std::cout << FT_WARNING << "File not found" << std::endl;
		_status_code = FT_STATUS_CODE_404;
		return (getErrorPage());
	}

	path_to_dir.append("/");
	std::ifstream file(path_to_dir.append(en->d_name).c_str());
	closedir(dr);

	std::string page = "";
	std::string line;
	while (std::getline(file, line))
	{
		page.append(line);
		page.append("\n");
	}
	return page;
}

bool ft::Response::checkMethod()
{
	if (_location.allowed_methods_get == true && _request.getMethod() == "GET")
		return (true);
	if (_location.allowed_methods_post == true && _request.getMethod() == "POST")
		return (true);
	if (_location.allowed_methods_delete == true && _request.getMethod() == "DELETE")
		return (true);
	_status_code = FT_STATUS_CODE_405;
	_content_type = "text/plain";
	_body = "method not allowed";
	_content_length = numberToString(_body.size());
	return (false);
}

bool ft::Response::checkRedirect()
{
	if (_location.redirect != "")
	{
		_status_code = FT_STATUS_CODE_301;
		_content_length = "0";
		_location.endpoint = _location.redirect;
		return (true);
	}
	return (false);
}

std::string ft::Response::getResourceContentType()
{
	size_t	dot;
	std::string resource;
	std::map<std::string, std::string> types;
	types.insert(std::make_pair(".html", "text/html"));
	types.insert(std::make_pair(".txt", "text/plain"));
	types.insert(std::make_pair(".png", "image/png"));
	types.insert(std::make_pair(".jpg", "image/jpg"));
	types.insert(std::make_pair(".jpeg", "image/jpeg"));
	types.insert(std::make_pair(".gif", "image/gif"));

	dot = _request.getEndpoint().find_last_of(".");
	//checar tipo de indexes da location
	if (dot == std::string::npos)
		return ("text/html");
	
	resource = _request.getEndpoint().substr(dot, _request.getEndpoint().length() - dot);
	return (types[resource]);
}

void ft::Response::processRequest()
{
	if (_request.getMethod() == "GET")
	{
		_body = getPage();
		_content_type = getResourceContentType();
		_content_length = numberToString(_body.size());
		_connection_type = "Keep-alive";
	}
	else if (_request.getMethod() == "POST")
	{
		if (atoi(_request.getContentLength().data()) > atoi(_location.max_body_size.data()))
		{
			_status_code = FT_STATUS_CODE_413;
			_connection_type = "Keep-alive";
			_body = getPage();
			_content_type = getResourceContentType();
			_content_length = numberToString(_body.size());
			return;
		}
		saveBodyContent();
		_body = getPage();
		_content_type = getResourceContentType();
		_content_length = numberToString(_body.size());
	}
	else if (_request.getMethod() == "DELETE")
		deleteFile();
}

void ft::Response::deleteFile()
{
	std::string body = _request.getBody();
	std::string file_name = FT_SAVE_DIR_PATH;
	int status;

	file_name.append(body);
	status = std::remove(file_name.data());
	!status ? _status_code = FT_STATUS_CODE_204 : _status_code = FT_STATUS_CODE_404;
}

void ft::Response::saveBodyContent()
{
	std::string body = _request.getBody();

	size_t start;
	size_t end;

	start = body.find("filename=", 0) + 10;
	end = body.find("\"", start);

	std::string file_name = FT_SAVE_DIR_PATH;
	file_name.append(body.substr(start, end - start));

	start = body.find("Content-Type:", 0);
	end = body.find("\n", start) + 3;
	start = end;

	std::ofstream file;
	file.open(file_name.data(), std::ios::binary);
	if (!file.is_open())
	{
		std::cout << FT_WARNING << "Couldn't save file. Dir not found!" << std::endl;
		_status_code = FT_STATUS_CODE_404;
		return ;
	}
	file << body.substr(start, body.length() - start);
	file.close();
}

bool	ft::Response::checkAutoindex()
{
	if (_location.autoindex != true ||\
		(_location.endpoint != _request.getEndpoint() &&\
		 _location.endpoint + "/" != _request.getEndpoint()))
		return (false);
	
	DIR *dr;
	struct dirent *en;
	std::string path_to_dir = ".";
	
	path_to_dir.append(_location.root);
	dr = opendir(path_to_dir.data());
	if (dr == NULL)
	{
		std::cout << FT_WARNING << "Directory not found" << std::endl;
		_status_code = FT_STATUS_CODE_404;
		handleNotFound();
	}
	
	_body = "<!DOCTYPE html>\n\
			<html lang=\"en\">\n\
				<head>\n\
    				<meta charset=\"UTF-8\">\n\
    				<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n\
   					<title>Autoindex</title>\n\
				</head>\n\
				<body>\n\
					<h2>Lista de Links</h2>\n\
    				<ul>\n";

	while (ft::keep() && (en = readdir(dr)) != NULL)
	{
		_body.append("<li><a href=\"http://localhost:8081");
		_body.append(_location.endpoint);
		_body.append("/");
		_body.append(en->d_name);
		_body.append("\">");
		_body.append(en->d_name);
		_body.append("</a></li>\n");
	}

	_body.append("    </ul>\n</body>\n</html>");
	_content_type = "text/html";
	_content_length = numberToString(_body.size());
	closedir(dr);
	return (true);
}

bool	ft::Response::checkCGI()
{
	return (false);
}

const char *ft::Response::ServerNotFoundException::what() const throw()
{
	return (FT_ERROR "Server not found :/");
}

const char *ft::Response::WrongProtocolException::what() const throw()
{
	return (FT_ERROR "Protocol not accepted");
}
