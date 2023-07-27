/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:08:40 by rabustam          #+#    #+#             */
/*   Updated: 2023/07/27 12:39:52 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_HPP
# define TESTSERVER_HPP

# include "SimpleServer.hpp"
# include <unistd.h>

namespace WS
{
	class TestServer : public SimpleServer
	{
		private:
		char	buffer[30000] = {0};
		int		new_socket;
		
		void accept_socket();
		void handle_socket();
		void answer_socket();
		public:
		TestServer();
		~TestServer();
		void launch_server(); 
	};
}

#endif