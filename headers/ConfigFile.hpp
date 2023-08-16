/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:49:59 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/14 14:49:59 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP

// # include <cctype>
# include <colors.hpp>
# include <exception>
# include <iostream>
# include <fstream>
# include <sstream>
// # include <map>
# include <messages.hpp>
# include <signal_handler.hpp>
// # include <string>
# include <vector>

namespace ft
{
	typedef struct	s_server_config
	{
		std::string	host;
		std::string	port;
	}	t_server_config;

	class ConfigFile
	{
		public:
			ConfigFile(const std::string& file);
			~ConfigFile(void);

		size_t	size(void) const;

		t_server_config	getServer(size_t server_id) const;

		std::string	getHost(size_t server_id) const;
		std::string	getPort(size_t server_id) const;

		class CouldNotOpenConfigFileException;
		class BadTokenException;

		private:
			std::vector<ft::t_server_config>	_servers;
	};

	class ConfigFile::CouldNotOpenConfigFileException : public std::exception
	{ public: const char* what() const throw(); };

	class ConfigFile::BadTokenException : public std::exception
	{ public: const char* what() const throw(); };

	static std::string				readFileContents(const std::string& filename);
	static std::vector<std::string>	tokenizer(const std::string& fileContent);
	static std::string				trim_spaces(const std::string& str);

	static ft::t_server_config	parseServer(const std::vector<std::string>& tokens, size_t& i);
	static void					parseHost(std::string& host, const std::vector<std::string>& tokens, size_t& i);
	static void					parsePort(std::string& port, const std::vector<std::string>& tokens, size_t& i);
}

# include <ConfigFile.ipp>

#endif //CONFIGFILE_HPP
