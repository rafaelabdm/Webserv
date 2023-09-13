/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:09:29 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/09/13 04:09:29 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

// C
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

// C++98
#include <fstream>
#include <stdexcept>
#include <cstring>

// my headers
#include <colors.hpp>
#include <messages.hpp>
#include <close_fds.hpp>

#define FT_CHILD_PROCESS 0
#define FT_PARENT_PROCESS -1

#define FT_READ_FD 0
#define FT_WRITE_FD 1

#define FT_TEMP_DIR "./tmp/"
#define FT_TEMP_FILE FT_TEMP_DIR "request_bodyXXXXXX"

#define FT_PYTHON "python3"
#define FT_PYTHON_PATH "/usr/bin/python3"

namespace ft
{
	class CGI
	{
	public:
		CGI(void);
		CGI(const std::string &script_path);
		~CGI(void);

		std::string executePythonScript(void);

		class CouldNotCreateTemporaryFileException;
		class CouldNotWriteTemporaryFileException;
		class CouldNotCreatePipeException;
		class CouldNotCreateChildProcessException;
		class CouldNotDeleteTemporaryFileException;
		class CouldNotExecutePythonScriptException;

	private:
		std::string _script_path;
		const char **_envp;
	};

	class CGI::CouldNotCreateTemporaryFileException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class CGI::CouldNotWriteTemporaryFileException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class CGI::CouldNotCreatePipeException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class CGI::CouldNotCreateChildProcessException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class CGI::CouldNotDeleteTemporaryFileException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class CGI::CouldNotExecutePythonScriptException : public std::exception
	{
	public:
		const char *what() const throw();
	};
} // namespace ft

#include <CGI.ipp>

#endif // CGI_HPP
