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

void	ft::Request::setBody(char* body)
{
	std::string req = body;
	int i = req.find("\n\n", 0) + 2;
	req = req.substr(i, req.length() - i);
	_body = req;
}

void	ft::Request::setHost(std::string host)
{
	_host = host;
}

void	ft::Request::setContentType(std::string content)
{
	_content_type = content;
}

void	ft::Request::setProtocol(std::string protocol)
{
	_protocol = protocol;
}

void	ft::Request::getFirstLineInfo(char *buffer, std::vector<std::string>& req)
{
	std::string					temp;
	bool						stop;
	int							start;
	int							end;

	temp = buffer;
	stop = false;
	start = 0;
	for (end = 0; !stop; end++)
	{
		if (buffer[end] == ' ' || buffer[end] == '\n')
		{
			if (buffer[end] == '\n')
				stop = true;
			req.push_back(temp.substr(start, end - start));
			start = end + 1;
		}
	}
	setMethod(req[0]);
	setPath(req[1]);
	setProtocol(req[2]);
}

void	ft::Request::getRequestInfo(char *buffer)
{
	std::vector<std::string>	req;
	std::string					temp;
	int							start;
	int							end;
	
	getFirstLineInfo(buffer, req);
	temp = buffer;

	start = temp.find("Host: ", 0) + 6;
	end = temp.find("\n", start);
	req.push_back(temp.substr(start, end - start));

	start = temp.find("Content-Type: ", 0) + 14;
	end = temp.find("\n", start);
	req.push_back(temp.substr(start, end - start));

	setHost(req[3]);
	setContentType(req[4]);
	if (_method == "POST")
		setBody(buffer);
}