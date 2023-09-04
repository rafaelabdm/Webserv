/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:42:17 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/15 10:29:32 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <vector>
# include <iostream>
# include <algorithm>
# include "colors.hpp"

namespace ft
{
	class Request
	{
		private:
		std::string	_endpoint;
		std::string	_method;
		std::string	_protocol;
		std::string	_host;
		std::string _content_type;
		std::string	_body;

		void	getRequestInfo(std::string buffer);
		void	getFirstLineInfo(std::string request);
		std::string	getBoundry();
		
		void	setHost(std::string request);
		void	setMethod(std::string method);
		void	setPath(std::string path);
		void	setBody(std::string request);
		void	setContentType(std::string content);
		void	setProtocol(std::string protocol);

		public:
		Request(std::string client_buffer);
		~Request();
		std::string	getMethod();
		std::string	getPath();
		std::string	getProtocol();
		std::string	getHost();
		std::string	getEndpoint();
		std::string	getContentType();
		std::string	getBody();
	};
}

# include "Request.ipp"

#endif /* Request_hpp */