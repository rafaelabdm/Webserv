/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:29:32 by rabustam          #+#    #+#             */
/*   Updated: 2023/08/14 10:29:21 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <colors.hpp>
# include <iostream>
# include <messages.hpp>

namespace ft
{
	class Socket
	{
		private:
		std::string	_host;
		std::string	_port;

		public:
		Socket(const std::string& host, const std::string& port);
		~Socket();
	};
}

# include "Socket.ipp"

#endif /* Socket_hpp */