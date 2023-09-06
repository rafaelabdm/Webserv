/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.ipp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:41:55 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/15 10:29:18 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

ft::Request::Request(std::string client_buffer) : _endpoint(""),  _method(""), _content_length("") ,_body("")
{
	getRequestInfo(client_buffer);
}

ft::Request::~Request()
{
	std::cout << RED << "Method: [" << _method << "]" << RESET_COLOR << std::endl;
	std::cout << YELLOW << "Endpoint: [" << _endpoint << "]" << RESET_COLOR << std::endl;
	std::cout << CYAN << "Protocol: [" << _protocol << "]" << RESET_COLOR << std::endl;
	std::cout << GREEN << "Host: [" << _host << "]" << RESET_COLOR << std::endl;
	std::cout << MAGENTA << "Content-Type: [" << _content_type << "]" << RESET_COLOR << std::endl;
	std::cout << BLUE << "Content-Length: [" << _content_length << "]" << RESET_COLOR << std::endl;
	// std::cout << BLUE << "Body: [" << _body << "]" << RESET_COLOR << std::endl;
}


//getters

std::string			ft::Request::getMethod()
{
	return (_method);
}

std::string	ft::Request::getPath()
{
	return (_endpoint);
}

std::string	ft::Request::getProtocol()
{
	return (_protocol);
}

std::string	ft::Request::getHost()
{
	return (_host);
}

std::string	ft::Request::getEndpoint()
{
	return (_endpoint);
}

std::string	ft::Request::getContentType()
{
	return (_content_type);
}

std::string	ft::Request::getContentLength()
{
	return (_content_length);
}

std::string	ft::Request::getBody()
{
	return (_body);
}


//setters

void	ft::Request::setMethod(std::string method)
{
	_method = method;
}

void	ft::Request::setPath(std::string path)
{
	_endpoint = path;
}

std::string ft::Request::getBoundry()
{
	size_t	start;

	start = _content_type.find("boundary=", 0) + 9;
	return (_content_type.substr(start, _content_type.length() - start));
}

void	ft::Request::setBody(std::string request)
{
	std::string boundry;
	size_t		start;
	size_t		end;

	if (_content_type.find("boundary", 0) != std::string::npos)
	{
		boundry = getBoundry();
		start = request.find("boundary=", 0) + boundry.length() + 11;
		start = request.find(boundry, start) + boundry.length() + 2;
		end = request.rfind(boundry, request.length()) - 2;
		_body = request.substr(start, end - start);
		return ;
	}
	start = request.rfind("\n", request.length()) + 1;
	_body = request.substr(start, request.length() - start);
}

void	ft::Request::setHost(std::string request)
{
	size_t	start;
	size_t	end;

	start = request.find("Host: ", 0) + 6;
	end = request.find("\r", start); //bizarramente tem um \r vindo no request?
	_host = request.substr(start, end - start);
}

void	ft::Request::setContentType(std::string request)
{
	size_t						start;
	size_t						end;

	start = request.find("Content-Type: ", 0);
	if (start == std::string::npos)
		return ;
	start += 14;
	end = request.find("\r", start);
	_content_type = request.substr(start, end - start);
}

void	ft::Request::setContentLength(std::string request)
{
	size_t						start;
	size_t						end;

	start = request.find("Content-Length: ", 0);
	if (start == std::string::npos)
		return ;
	start += 16;
	end = request.find("\r", start);
	_content_length = request.substr(start, end - start);
}

void	ft::Request::setProtocol(std::string protocol)
{
	_protocol = protocol;
}

void	ft::Request::getFirstLineInfo(std::string request)
{
	std::vector<std::string>	req;
	bool						stop;
	size_t						start;
	size_t						end;

	stop = false;
	start = 0;
	for (end = 0; !stop; end++)
	{
		if (request[end] == ' ' || request[end] == '\n' || request[end] == '\r')
		{
			if (request[end] == '\n')
				stop = true;
			req.push_back(request.substr(start, end - start));
			start = end + 1;
		}
	}
	setMethod(req[0]);
	setPath(req[1]);
	setProtocol(req[2]);
}

void	ft::Request::getRequestInfo(std::string buffer)
{
	getFirstLineInfo(buffer);
	setHost(buffer);
	setContentType(buffer);
	setContentLength(buffer);
	if (_method == "POST" || _method == "DELETE")
		setBody(buffer);
}