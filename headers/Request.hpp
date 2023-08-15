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

namespace WS
{
	class Request
	{
		private:
		std::string	_method;
		std::string	_path;
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