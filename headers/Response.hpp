/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:53:16 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/06 11:59:08 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "Request.hpp"
# include "Socket.hpp"
# include "signal_handler.hpp"
# include <dirent.h>
# include <cstdio>
# include <vector>
# include <map>

//temps defines
# define ERROR_PAGE_PATH	"/home/rabustam/42sp/wb_main/examples/"

namespace ft
{
	class Response
	{
		private:
		ft::Request&			_request;
		ft::t_server_config		_server;
		ft::t_location_config	_location;
		std::string				_protocol;
		std::string 			_status_code;
		std::string 			_content_type;
		std::string 			_content_length;
		std::string 			_connection_type;
		std::string 			_date;
		std::string 			_body;
		
		ft::t_server_config	setServer(std::vector<ft::Socket*>& servers);
		void			checkProtocol();
		bool			checkEndpoint();
		bool			checkMethod();
		bool			checkRedirect();
		bool			checkIndexes(std::string file_name);
		void			processRequest();
		void			handleNotFound();
		std::string		numberToString(int size);
		std::string		getErrorPage();
		std::string		getPage();
		void			saveBodyContent();
		void			deleteFile();

		
		public:
		Response(ft::Request& request, std::vector<ft::Socket*>& servers);
		~Response();

		std::string getResponse();


		class	ServerNotFoundException : std::exception
		{
			public:
			const char* what() const throw();
		};
		class	WrongProtocolException : std::exception
		{
			public:
			const char* what() const throw();
		};
	};
}

# include "Response.ipp"

#endif