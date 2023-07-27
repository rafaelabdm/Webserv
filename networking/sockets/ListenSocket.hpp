/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListenSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 10:54:49 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 11:03:37 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENSOCKET_HPP
# define LISTENSOCKET_HPP

# include "BindSocket.hpp"

namespace WS
{
	class ListenSocket: public BindSocket
	{
		private:
		int backlog;
		int listening;

		public:
		ListenSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
		~ListenSocket();
		
		void start_listen();
	};
}

#endif