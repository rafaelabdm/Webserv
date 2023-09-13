/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:05:54 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/13 13:26:36 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "Request.hpp"
# include "ConfigFile.hpp"
# include <string>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FT_CHILD_PROCESS 0

# define FT_READ_FD 0
# define FT_WRITE_FD 1

# define FT_PYTHON "python3"
# define FT_PYTHON_PATH "/bin/python3"

namespace ft {
	class CGI
	{
		private:
		const char**			_envp;
		ft::Request&			_request;
		ft::t_location_config&	_location;
		int						_pipe[2];
		std::string				_response_body;
	
		void	runScript();
		std::string	getQuery();
		std::string	getResource();
		bool		 checkExecutable();
		std::vector<std::string>	setEnv();
		void	child();
		void	parent();
		
		public:
		CGI(ft::Request& request, ft::t_location_config& location);
		~CGI();
		
		std::string getResponseBody();
	};
}

# include "CGI.ipp"

#endif /* CGI.hpp */