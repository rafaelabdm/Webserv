/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.ipp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabustam <rabustam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 22:05:30 by rabustam          #+#    #+#             */
/*   Updated: 2023/09/15 09:50:32 by rabustam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

ft::CGI::CGI(ft::Request& request, ft::t_location_config& location) 
	: _request(request), _location(location)
{
	if (!checkExecutable())
		return ;
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
        std::cout << FT_WARNING << "Pipe falied." << std::endl;
		_response_body = FT_STATUS_CODE_500;
		return ;
	}
    pid = fork();
    if (pid == FT_CHILD_PROCESS) {
        child();
    } else if (pid > 0) {
        parent(pid);
    } else {
        std::cout << FT_WARNING << "Fork falied." << std::endl;
        _response_body = FT_STATUS_CODE_500;
		return ;
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
	
	if (access(path.c_str(), F_OK) != 0)
	{
		_response_body = FT_STATUS_CODE_404;
		return (false);
	}
	if (access(path.c_str(), R_OK) != 0)
	{
		_response_body = FT_STATUS_CODE_500;
		return (false);
	}
	if (access(path.c_str(), X_OK) != 0)
	{
		_response_body = FT_STATUS_CODE_500;
		return (false);
	}
	
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
		_response_body = FT_STATUS_CODE_500;
		return ;
	}
	if (dup2(_pipe[0], FT_READ_FD) == -1)
	{
		std::cout << FT_WARNING << "Dup2 falied." << std::endl;
		_response_body = FT_STATUS_CODE_500;
		return ;
	}
	if (execve(FT_PYTHON_PATH, (char * const *)argv, (char * const *)envp) == -1)
	{
		std::cout << FT_WARNING << "Execve falied." << std::endl;
		_response_body = FT_STATUS_CODE_500;
		return ;
	}
}

void ft::CGI::parent(pid_t pid)
{
	int		status;
	char	buf[4096];
	std::string		response;

	const int timeout_limit = 7;
    std::clock_t start_time;

	start_time = std::clock();
    while (true)
    {
        std::clock_t current_time = std::clock();
        double elapsed_time = static_cast<double>(current_time - start_time) / CLOCKS_PER_SEC;

		pid_t ret = waitpid(pid, &status, WNOHANG);
		if (ret == -1)
		{
			std::cout << FT_WARNING << "Waitpid falied." << std::endl;
			_response_body = FT_STATUS_CODE_500;
			return ;
		}
		if (ret > 0)
			break ;

        if (elapsed_time >= timeout_limit)
		{
			std::cout << FT_WARNING << "CGI Timeout." << std::endl;
			kill(pid, SIGTERM);
			_response_body = FT_STATUS_CODE_500;
			return ;
		}
    }
	close(_pipe[1]);
	std::memset(buf, 0, 4096);
	int ret = 1;
	while (ret)
	{
		ret = read(_pipe[0], buf, 4096);
		if (ret == -1)
		{
			std::cout << FT_WARNING << "Read falied." << std::endl;
			_response_body = FT_STATUS_CODE_500;
			return ;
		}
		response += buf;
		std::memset(buf, 0, 4096);
	}
	close(_pipe[0]);
	_response_body = response;
}

std::string ft::CGI::getResponseBody()
{
	return (_response_body);
}
