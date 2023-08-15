/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:42:17 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/15 09:07:05 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>

namespace WS
{
	class Request
	{
		private:
		std::string	_request;

		public:
		Request(char *client_buffer);
		~Request();
	};
}

#endif /* Request_hpp */