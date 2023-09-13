/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.ipp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:05:30 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/13 15:48:02 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

ft::CGI::CGI(ft::Request& request, ft::t_location_config& location) 
	: _request(request), _location(location)
{
	if (!checkExecutable())
	{
		_response_body = "500";
		return ;
	}
	runScript();	
}

ft::CGI::~CGI()
{
}

void	ft::CGI::runScript()
{
	pid_t	pid;

    if (::pipe(_pipe) != 0)
	{
		perror("pipe");
		throw std::exception();
	}
    pid = fork();
    if (pid == FT_CHILD_PROCESS) {
        child();
    } else if (pid > 0) {
        parent();
    } else {
        perror("cgi fork");
        throw std::exception();
    }
}

std::string ft::CGI::getQuery()
{
	std::string query;
	size_t		start;

	start = _request.getEndpoint().find('?');
	if (start == std::string::npos)
		return ("");
	query = _request.getEndpoint().substr(start + 1);
	return (query);
}

std::string ft::CGI::getResource()
{
	return (_request.getEndpoint().substr(_request.getEndpoint().rfind('/') + 1, _request.getEndpoint().find('?') - _request.getEndpoint().rfind('/') - 1));
}

bool ft::CGI::checkExecutable()
{
	std::string path = _location.root.substr(1) + "/" + getResource();
	
	if (access(path.c_str(), X_OK) != 0)
		return (false);
	return (true);
}

std::vector<std::string>	ft::CGI::setEnv()
{
	std::vector<std::string>	env;
	std::string 				query;
	std::string 				resource;

	query = getQuery();
	resource = getResource();
	
	env.resize(9);
	env[0] = "REQUEST_METHOD=" + _request.getMethod();
    env[1] = "QUERY_STRING=" + query;
    env[2] = "CONTENT_TYPE=text/html";
    env[3] = "CONTENT_LENGTH=" + _request.getContentLength();
    env[4] = "DOCUMENT_ROOT=" + _location.root;
    env[5] = "SCRIPT_FILENAME=" + resource;
    env[6] = "SCRIPT_NAME=" + resource;
    env[7] = "REDIRECT_STATUS=200";
    env[8] = "REQUEST_BODY=" + _request.getBody();

	return (env);
}

void	ft::CGI::child()
{
	std::vector<std::string>	env = setEnv();
	std::string					resource = _location.root.substr(1) + "/" + getResource();
	char const					*argv[] = {FT_PYTHON_PATH, resource.c_str(), NULL};
	char const					*envp[] = {env[0].c_str(),
											env[1].c_str(),
											env[2].c_str(),
											env[3].c_str(),
											env[4].c_str(),
											env[5].c_str(),
											env[6].c_str(),
											env[7].c_str(),
											env[8].c_str(),
											NULL};
	if (dup2(_pipe[1], FT_WRITE_FD) == -1)
	{
		std::cout << FT_WARNING << "Dup2 falied." << std::endl;
		throw std::exception();
	}
	if (dup2(_pipe[0], FT_READ_FD) == -1)
	{
		std::cout << FT_WARNING << "Dup2 falied." << std::endl;
		throw std::exception();
	}
	if (execve(FT_PYTHON_PATH, (char * const *)argv, (char * const *)envp) == -1)
	{
		std::cout << FT_WARNING << "Execve falied." << std::endl;
		throw std::exception();
	}
}

void ft::CGI::parent()
{
	int		status;
	char	buf[4096];
	std::string		response;

	close(_pipe[1]);
	while (read(_pipe[0], buf, 4096) > 0)
	{
		response += buf;
		memset(buf, 0, 4096);
	}
	close(_pipe[0]);
	waitpid(-1, &status, 0);
	_response_body = response;
	std::cout << response << std::endl;
}

std::string ft::CGI::getResponseBody()
{
	return (_response_body);
}
