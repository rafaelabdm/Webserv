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
#define CONFIGFILE_HPP

#include <cctype>
#include <colors.hpp>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <messages.hpp>
#include <vector>

#define DEFAULT_PORT ""
#define DEFAULT_ENDPOINT ""
#define DEFAULT_ROOT ""
#define DEFAULT_REDIRECT ""
#define DEFAULT_INDEXES ""
// #define DEFAULT_UPLOAD_ENABLED false
// #define DEFAULT_UPLOAD_DIR ""
#define DEFAULT_CGI_ENABLED false
#define DEFAULT_CGI_DIR ""
#define DEFAULT_AUTOINDEX false
#define DEFAULT_ALLOWED_METHODS_GET true
#define DEFAULT_ALLOWED_METHODS_POST true
#define DEFAULT_ALLOWED_METHODS_DELETE true

namespace ft
{
	typedef struct s_location_config
	{
		std::string endpoint;
		std::string root;
		std::string redirect;
		std::vector<std::string> indexes;
		bool upload_enabled;
		std::string upload_dir;
		bool cgi_enabled;
		std::string cgi_dir;
		bool autoindex;
		bool allowed_methods_get;
		bool allowed_methods_post;
		bool allowed_methods_delete;
		std::string max_body_size;

	} t_location_config;

	typedef struct s_server_config
	{
		std::string port;
		std::vector<std::string> server_names;
		std::map<std::string, std::string> error_pages;
		std::vector<ft::t_location_config> locations;
	} t_server_config;

	class ConfigFile
	{
	public:
		ConfigFile(void);
		ConfigFile(const std::string &file);
		~ConfigFile(void);

		size_t size(void) const;

		std::vector<ft::t_server_config> getServers(void) const;
		ft::t_server_config getServer(size_t server_id) const;

		std::string getPort(size_t server_id) const;
		std::vector<std::string> getServerNames(size_t server_id) const;
		std::string getServerName(size_t server_id, size_t server_name_id) const;
		std::map<std::string, std::string> getErrorPages(size_t server_id) const;
		std::string getErrorPage(size_t server_id, std::string page) const;

		std::vector<ft::t_location_config> getLocations(size_t server_id) const;
		ft::t_location_config getLocation(size_t server_id, size_t location_id) const;

		std::string getLocationEndpoint(size_t server_id, size_t location_id) const;
		std::string getLocationRoot(size_t server_id, size_t location_id) const;
		std::string getLocationRedirect(size_t server_id, size_t location_id) const;
		std::vector<std::string> getLocationIndexes(size_t server_id, size_t location_id) const;
		std::string getLocationIndex(size_t server_id, size_t location_id, size_t index_id) const;
		bool getLocationUploadEnabled(size_t server_id, size_t location_id) const;
		std::string getLocationUploadDir(size_t server_id, size_t location_id) const;
		bool getLocationCgiEnabled(size_t server_id, size_t location_id) const;
		std::string getLocationCgiDir(size_t server_id, size_t location_id) const;
		bool getLocationAutoindex(size_t server_id, size_t location_id) const;
		bool getLocationAllowedMethodsGet(size_t server_id, size_t location_id) const;
		bool getLocationAllowedMethodsPost(size_t server_id, size_t location_id) const;
		bool getLocationAllowedMethodsDelete(size_t server_id, size_t location_id) const;
		std::string getLocationMaxBodySize(size_t server_id, size_t location_id) const;

		class CouldNotOpenConfigFileException;
		class BadTokenException;
		class EmptyfileContentException;
		class GlobalLevelUnknownTokenException;
		class CantFindServerOpenBracketException;
		class CantFindServerCloseBracketException;
		class EmptyServerException;
		class ServerLevelUnknownTokenException;
		class PortAlreadySetException;
		class CantFindPortTokenException;
		class ServerNamesAlreadySetException;
		class CantFindServerNamesTokenException;
		class CantFindErrorPageTokenException;
		class ErrorPageAlreadySetException;
		class CantFindLocationEndpointException;
		class EmptyLocationException;
		class CantFindLocationOpenBracketException;
		class UploadEnabledAlreadySetException;
		class CgiEnabledAlreadySetException;
		class LocationLevelUnknownTokenException;
		class CantFindLocationCloseBracketException;
		class RootAlreadySetException;
		class CantFindRootTokenException;
		class RedirectAlreadySetException;
		class CantFindRedirectTokenException;
		class IndexesAlreadySetException;
		class CantFindIndexesTokenException;
		class BadUploadEnabledTokenException;
		class CantFindUploadEnabledTokenException;
		class UploadDirAlreadySetException;
		class CantFindUploadDirTokenException;
		class CantFindCgiEnabledTokenException;
		class BadCgiEnabledTokenException;
		class CgiDirAlreadySetException;
		class CantFindCgiDirTokenException;
		class CantFindAutoindexTokenException;
		class BadAutoindexTokenException;
		class AutoindexAlreadySetException;
		class CantFindAllowedMethodsTokenException;
		class AllowedMethodsAlreadySetException;
		class BadAllowedMethodsTokenException;
		class MaxBodySizeAlreadySetException;
		class CantFindMaxBodySizeTokenException;

	private:
		std::vector<ft::t_server_config> _servers;
	};

	class ConfigFile::CouldNotOpenConfigFileException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::BadTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::EmptyfileContentException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::GlobalLevelUnknownTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindServerOpenBracketException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindServerCloseBracketException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::EmptyServerException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::ServerLevelUnknownTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::PortAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindPortTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::ServerNamesAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindServerNamesTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindErrorPageTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::ErrorPageAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindLocationEndpointException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::EmptyLocationException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindLocationOpenBracketException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::UploadEnabledAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CgiEnabledAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::LocationLevelUnknownTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindLocationCloseBracketException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::RootAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindRootTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::RedirectAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindRedirectTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::IndexesAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindIndexesTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::BadUploadEnabledTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindUploadEnabledTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::UploadDirAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindUploadDirTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindCgiEnabledTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::BadCgiEnabledTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CgiDirAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindCgiDirTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindAutoindexTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::BadAutoindexTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::AutoindexAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindAllowedMethodsTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::AllowedMethodsAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::BadAllowedMethodsTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::MaxBodySizeAlreadySetException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	class ConfigFile::CantFindMaxBodySizeTokenException : public std::exception
	{
	public:
		const char *what() const throw();
	};

	static std::string readFileContents(const std::string &filename);
	static std::vector<std::string> tokenizer(const std::string &fileContent);
	static std::vector<ft::t_server_config> parseConfigTokens(const std::vector<std::string> &tokens);

	static std::string trim_spaces(const std::string &str);

	static ft::t_server_config parseServer(const std::vector<std::string> &tokens, size_t &i);

	static void parsePort(std::string &port, const std::vector<std::string> &tokens, size_t &i);
	static void parseServerNames(std::vector<std::string> &server_names, const std::vector<std::string> &tokens, size_t &i);
	static void parseErrorPages(std::map<std::string, std::string> &error_pages, const std::vector<std::string> &tokens, size_t &i);

	static ft::t_location_config parseLocations(const std::vector<std::string> &tokens, size_t &i);

	static void parseRoot(std::string &root, const std::vector<std::string> &tokens, size_t &i);
	static void parseRedirect(std::string &redirect, const std::vector<std::string> &tokens, size_t &i);
	static void parseIndexes(std::vector<std::string> &indexes, const std::vector<std::string> &tokens, size_t &i);
	static void parseUploadEnabled(bool &upload_enabled, const std::vector<std::string> &tokens, size_t &i);
	static void parseUploadDir(std::string &upload_dir, const std::vector<std::string> &tokens, size_t &i);
	static void parseCgiEnabled(bool &cgi_enabled, const std::vector<std::string> &tokens, size_t &i);
	static void parseCgiDir(std::string &cgi_dir, const std::vector<std::string> &tokens, size_t &i);
	static void parseAutoindex(bool &autoindex, const std::vector<std::string> &tokens, size_t &i);
	static void parseAllowedMethods(bool &allowed_methods_get, bool &allowed_methods_post, bool &allowed_methods_delete, const std::vector<std::string> &tokens, size_t &i);
	static void parseMaxBodySize(std::string &max_body_size, const std::vector<std::string> &tokens, size_t &i);
}

std::ostream &operator<<(std::ostream &out, const ft::ConfigFile &config_file);

std::ostream &operator<<(std::ostream &out, const std::vector<ft::t_server_config> &servers);
std::ostream &operator<<(std::ostream &out, const ft::t_server_config &server);

std::ostream &operator<<(std::ostream &out, const std::vector<ft::t_location_config> &locations);
std::ostream &operator<<(std::ostream &out, const ft::t_location_config &location);

std::ostream &operator<<(std::ostream &out, const std::vector<std::string> &strs);
std::ostream &operator<<(std::ostream &out, const std::map<std::string, std::string> &strs);

#include <ConfigFile.ipp>

#endif // CONFIGFILE_HPP
