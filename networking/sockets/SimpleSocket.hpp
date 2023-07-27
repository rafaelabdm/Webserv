/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 10:10:02 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 12:17:12 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESOCKET_HPP
# define SIMPLESOCKET_HPP

# include <iostream>
# include <netinet/in.h> //address structure
# include <stdio.h>
# include <sys/socket.h> //socket function
# include <sys/types.h>


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
		~SimpleSocket();
		virtual int network_connection(int sock, struct sockaddr_in address) = 0; //bind or connect
		void test_connection(int connection_to_test);
		//GETTERS
		struct sockaddr_in get_address();
		int get_sock();
		int get_connection();
	};
}

#endif /* SimpleSocket_hpp */