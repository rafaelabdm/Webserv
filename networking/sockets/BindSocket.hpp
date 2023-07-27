/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindSocket.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 09:29:44 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 10:39:28 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

# include "SimpleSocket.hpp"

namespace WS
{
	class BindSocket : public SimpleSocket
	{
		public:
		BindSocket(int domain, int service, int protocol, int port, u_long interface);
		~BindSocket();
		int network_connection(int sock, struct sockaddr_in address);
	};
}


#endif /* BindSocket_hpp */