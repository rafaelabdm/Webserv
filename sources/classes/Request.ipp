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

ft::Request::Request(char *client_buffer) : _endpoint(""),  _method(""), _body("")
{
	getRequestInfo(client_buffer);
}

ft::Request::~Request()
{
	std::cout << RED << "Method: " << _method << RESET_COLOR << std::endl;
	std::cout << YELLOW << "Endpoint: " << _endpoint << RESET_COLOR << std::endl;
	std::cout << CYAN << "Protocol: " << _protocol << RESET_COLOR << std::endl;
	std::cout << GREEN << "Host: " << _host << RESET_COLOR << std::endl;
	std::cout << MAGENTA << "Content-Type: " << _content_type << RESET_COLOR << std::endl;
	std::cout << BLUE << "Body: " << _body << RESET_COLOR << std::endl;
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

void	ft::Request::setBody(std::string request)
{
	size_t	start;

	start = request.find("\n\n", 0) + 2;
	_body = request.substr(start, request.length() - start);
}

void	ft::Request::setHost(std::string request)
{
	size_t	start;
	size_t	end;

	start = request.find("Host: ", 0) + 6;
	end = request.find("\n", start);
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
	end = request.find("\n", start);
	_content_type = request.substr(start, end - start);
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
		if (request[end] == ' ' || request[end] == '\n')
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

void	ft::Request::getRequestInfo(char *buffer)
{
	std::string					request;
	
	request = buffer;
	getFirstLineInfo(request);
	setHost(request);
	setContentType(request);
	if (_method == "POST")
		setBody(buffer);
}