/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.ipp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:09:32 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/09/13 04:09:32 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CGI.hpp>

ft::CGI::CGI(void)
{
	std::cout << FT_SETUP << "Creating CGI execution." << std::endl;
}

ft::CGI::CGI(const std::string &script_path) : _script_path(script_path)
{
	std::cout << FT_SETUP << "Creating CGI execution." << std::endl;
}

ft::CGI::~CGI(void)
{
	std::cout << FT_CLOSE << "Closing CGI execution." << std::endl;
}

std::string ft::CGI::executePythonScript(void)
{
	std::cout << FT_CGI << "Executing Python CGI." << std::endl;

	std::string requestBody = "";
	std::string tempFile = FT_TEMP_FILE;

	std::ofstream temp_file_stream(tempFile.c_str());

	if (!temp_file_stream.is_open())
		throw ft::CGI::CouldNotCreateTemporaryFileException();

	temp_file_stream << requestBody;
	temp_file_stream.close();

	int pipefd[2];
	if (pipe(pipefd) == -1)
		throw ft::CGI::CouldNotCreatePipeException();

	pid_t pid = fork();
	if (pid == FT_PARENT_PROCESS)
		throw ft::CGI::CouldNotCreateChildProcessException();

	if (pid == FT_CHILD_PROCESS)
	{
		close(pipefd[FT_READ_FD]);

		if (dup2(pipefd[FT_WRITE_FD], STDOUT_FILENO) == -1)
			_exit(EXIT_FAILURE);

		close(pipefd[FT_WRITE_FD]);

		char *python_args[] = {(char *)FT_PYTHON, (char *)_script_path.c_str(), (char *)tempFile.c_str(), NULL};
		execv(FT_PYTHON_PATH, python_args);

		_exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[FT_WRITE_FD]);

		char buffer[128];
		std::string result = "";
		ssize_t bytesRead;

		while ((bytesRead = read(pipefd[FT_READ_FD], buffer, sizeof(buffer))) > 0)
			result += std::string(buffer, bytesRead);

		close(pipefd[FT_READ_FD]);

		int status;
		waitpid(pid, &status, 0);

		if (std::remove(tempFile.c_str()) != 0)
			throw ft::CGI::CouldNotDeleteTemporaryFileException();

		std::cout << FT_OK << "CGI successfully executed." << std::endl;

		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			return result;
		else
			throw ft::CGI::CouldNotExecutePythonScriptException();
	}

	return ("");
}

const char *ft::CGI::CouldNotCreateTemporaryFileException::what() const throw()
{
	return (FT_ERROR "Could not create temporary file.");
}

const char *ft::CGI::CouldNotWriteTemporaryFileException::what() const throw()
{
	return (FT_ERROR "Could not write temporary file.");
}

const char *ft::CGI::CouldNotCreatePipeException::what() const throw()
{
	return (FT_ERROR "Could not create pipe.");
}

const char *ft::CGI::CouldNotCreateChildProcessException::what() const throw()
{
	return (FT_ERROR "Could not create child process.");
}

const char *ft::CGI::CouldNotDeleteTemporaryFileException::what() const throw()
{
	return (FT_ERROR "Could not delete temporary file.");
}

const char *ft::CGI::CouldNotExecutePythonScriptException::what() const throw()
{
	return (FT_ERROR "Could not execute python script.");
}
