/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:42:17 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/16 11:21:41 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <vector>
# include <iostream>

namespace ft
{
	class Request
	{
		private:
		std::string	_endpoint;
		std::string	_method;
		//????		_body; POST/DELETE
		
		void	getRequestInfo(char *buffer);
		void	setMethod(std::string m);
		void	setPath(std::string p);

		public:
		Request(char *client_buffer);
		~Request();
		std::string	getMethod();
		std::string	getPath();
	};
}

# include "Request.ipp"

#endif /* Request_hpp */