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

WS::Request::Request(char *client_buffer)
{
	getRequestInfo(client_buffer);
}

WS::Request::~Request()
{
	std::cout << "Method: " << _method << std::endl;
	std::cout << "Path: " << _path << std::endl;
}

void	WS::Request::setMethod(std::string m)
{
	if (m == "GET")
		_method = "GET";
	else if (m == "POST")
		_method = "POST";
	else if (m == "DELETE")
		_method = "DELETE";
}

void	WS::Request::setPath(std::string p)
{
	_path = p;
}

std::string			WS::Request::getMethod()
{
	return (_method);
}

std::string	WS::Request::getPath()
{
	return (_path);
}

void	WS::Request::getRequestInfo(char *buffer)
{
	std::vector<std::string>	req;
	std::string					temp;
	bool						stop;
	int							j;
	
	temp = buffer;
	stop = false;
	j = 0;
	for (int i = 0; !stop; i++)
	{
		if (buffer[i] == ' ')
		{
			if (j != 0)
				stop = true;
			req.push_back(temp.substr(j, i - j));
			j = i + 1;
		}
	}

	setMethod(req[0]);
	setPath(req[1]);
}