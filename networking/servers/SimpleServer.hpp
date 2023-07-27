/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 11:54:45 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 12:52:36 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESERVER_HPP
# define SIMPLESERVER_HPP

# include "../sockets/ListenSocket.hpp"

namespace WS
{
	class SimpleServer
	{
		protected:
		WS::ListenSocket * socket;
		virtual void accept_socket() = 0;
		virtual void handle_socket() = 0;
		virtual void answer_socket() = 0;
		public:
		SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg);
		~SimpleServer();
		virtual void launch_server() = 0; 
	};
}

#endif