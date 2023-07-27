/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:10:02 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 10:28:18 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESOCKET_HPP
# define SIMPLESOCKET_HPP

# include <stdio.h>
# include <iostream>
# include <sys/socket.h> //socket function
# include <netinet/in.h> //address structure

namespace WS
{
	class SimpleSocket
	{
		protected:
		struct sockaddr_in	address;
		int					sock;
		int					connection;

		public:
		SimpleSocket(int domain, int service, int protocol, int port, u_long interface);
		virtual int network_connection(int sock, struct sockaddr_in address) = 0; //bind or connect
		void test_connection(int connection_to_test);
		struct sockaddr_in get_address();
		int get_sock();
		int get_connection();
	};
}

#endif /* SimpleSocket_hpp */