/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:53:16 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/25 10:56:06 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Request.hpp"
# include "Socket.hpp"
# include <vector>
# include <map>

namespace ft
{
	class Response
	{
		private:
		ft::Request _request;
		ft::Socket 	_server;
		std::string _protocol;
		std::string _status_code;
		std::string _content_type;
		std::string _content_length;
		std::string _connection_type;
		std::string _date;
		std::string _body;
		
		ft::Socket	setServer(std::vector<ft::Socket> servers);
		void		checkProtocol();
		void		checkEndpoint();

		
		public:
		Response(ft::Request request, std::vector<ft::Socket>& servers);
		~Response();

		std::string getResponse();
	};
}

# include "Response.ipp"

#endif