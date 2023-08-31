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

# include <colors.hpp>
# include <exception>
# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <messages.hpp>
# include <vector>

namespace ft
{
	typedef struct	s_location_config
	{
		std::string					endpoint;
		std::string					root;
		std::string					redirect;
		std::vector<std::string>	indexes;
		bool						upload_enabled;
		std::string					upload_dir;
		bool						cgi_enabled;
		std::string					cgi_dir;

	}	t_location_config;

	typedef struct	s_server_config
	{
		std::string							port;
		std::vector<std::string>			server_names;
		std::map<std::string, std::string>	error_pages;
		std::vector<ft::t_location_config>	locations;
	}	t_server_config;

	class ConfigFile
	{
		public:
			ConfigFile(const std::string& file);
			~ConfigFile(void);

			size_t	size(void) const;

			std::vector<ft::t_server_config>	getServers(void) const;
			ft::t_server_config					getServer(size_t server_id) const;

			std::string							getPort(size_t server_id) const;
			std::vector<std::string>			getServerNames(size_t server_id) const;
			std::string							getServerName(size_t server_id, size_t server_name_id) const;
			std::map<std::string, std::string>	getErrorPages(size_t server_id) const;
			std::string							getErrorPage(size_t server_id, std::string page) const;

			std::vector<ft::t_location_config>	getLocations(size_t server_id) const;
			ft::t_location_config				getLocation(size_t server_id, size_t location_id) const;

			std::string					getLocationEndpoint(size_t server_id, size_t location_id) const;
			std::string					getLocationRoot(size_t server_id, size_t location_id) const;
			std::string					getLocationRedirect(size_t server_id, size_t location_id) const;
			std::vector<std::string>	getLocationIndexes(size_t server_id, size_t location_id) const;
			std::string					getLocationIndex(size_t server_id, size_t location_id, size_t index_id) const;
			bool						getLocationUploadEnabled(size_t server_id, size_t location_id) const;
			std::string					getLocationUploadDir(size_t server_id, size_t location_id) const;
			bool						getLocationCgiEnabled(size_t server_id, size_t location_id) const;
			std::string					getLocationCgiDir(size_t server_id, size_t location_id) const;

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

	static void	parsePort(std::string& port, const std::vector<std::string>& tokens, size_t& i);
	static void	parseServerNames(std::vector<std::string>& server_names, const std::vector<std::string>& tokens, size_t& i);
	static void	parseErrorPages(std::map<std::string, std::string>& error_pages, const std::vector<std::string>& tokens, size_t& i);

	static ft::t_location_config	parseLocations(const std::vector<std::string>& tokens, size_t& i);

	static void	parseRoot(std::string& root, const std::vector<std::string>& tokens, size_t& i);
	static void	parseRedirect(std::string& redirect, const std::vector<std::string>& tokens, size_t& i);
	static void	parseIndexes(std::vector<std::string>& indexes, const std::vector<std::string>& tokens, size_t& i);
	static void	parseUploadEnabled(bool& upload_enabled, const std::vector<std::string>& tokens, size_t& i);
	static void	parseUploadDir(std::string& upload_dir, const std::vector<std::string>& tokens, size_t& i);
	static void	parseCgiEnabled(bool& cgi_enabled, const std::vector<std::string>& tokens, size_t& i);
	static void	parseCgiDir(std::string& cgi_dir, const std::vector<std::string>& tokens, size_t& i);
}

std::ostream& operator <<(std::ostream& out, const ft::ConfigFile& config_file);

std::ostream& operator <<(std::ostream& out, const std::vector<ft::t_server_config>& servers);
std::ostream& operator <<(std::ostream& out, const ft::t_server_config& server);

std::ostream& operator <<(std::ostream& out, const std::vector<ft::t_location_config>& locations);
std::ostream& operator <<(std::ostream& out, const ft::t_location_config& location);

std::ostream& operator <<(std::ostream& out, const std::vector<std::string>& strs);
std::ostream& operator <<(std::ostream& out, const std::map<std::string, std::string>& strs);

# include <ConfigFile.ipp>

#endif //CONFIGFILE_HPP
