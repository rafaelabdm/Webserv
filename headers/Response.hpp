/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:53:16 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/25 08:57:14 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Request.hpp"
# include "Socket.hpp"
# include <vector>

namespace ft
{
	class Response
	{
		private:
		std::string _protocol;
		std::string _status_code;
		std::string _content_type;
		std::string _content_lenght;
		std::string _connection_type;
		
		public:
		Response(ft::Request request, std::vector<ft::Socket> servers);
		~Response();
	};
}

# include "Response.ipp"

#endif