/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:37:31 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 10:41:14 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTSOCKET_HPP
# define CONNECTSOCKET_HPP

# include "SimpleSocket.hpp"

namespace WS
{
	class ConnectSocket: public SimpleSocket
	{
		public:
		ConnectSocket(int domain, int service, int protocol, int port, u_long interface);
		~ConnectSocket();
		int network_connection(int sock, struct sockaddr_in address);
	};
}

#endif /* ConnectSocket_hpp */