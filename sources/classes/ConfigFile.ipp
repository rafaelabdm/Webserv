/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigFile.ipp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapdos-s <rapdos-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 08:12:59 by rapdos-s          #+#    #+#             */
/*   Updated: 2023/08/05 08:12:59 by rapdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ConfigFile.hpp>

ft::ConfigFile::ConfigFile(void)
{
	return;
}

ft::ConfigFile::ConfigFile(const std::string &config_file)
{
	std::string fileContent = ft::readFileContents(config_file);
	std::vector<std::string> tokens = ft::tokenizer(fileContent);

	this->_servers = parseConfigTokens(tokens);
	std::cout << std::endl;
}

ft::ConfigFile::~ConfigFile()
{
	return;
}

size_t ft::ConfigFile::size(void) const
{
	return (_servers.size());
}

std::vector<ft::t_server_config> ft::ConfigFile::getServers(void) const
{
	return (this->_servers);
}

ft::t_server_config ft::ConfigFile::getServer(size_t server_id) const
{
	return (this->_servers[server_id]);
}

std::string ft::ConfigFile::getPort(size_t server_id) const
{
	return (this->_servers[server_id].port);
}

std::vector<std::string> ft::ConfigFile::getServerNames(size_t server_id) const
{
	return (this->_servers[server_id].server_names);
}

std::string ft::ConfigFile::getServerName(size_t server_id, size_t server_name_id) const
{
	return (this->_servers[server_id].server_names[server_name_id]);
}

std::map<std::string, std::string> ft::ConfigFile::getErrorPages(size_t server_id) const
{
	return (this->_servers[server_id].error_pages);
}

std::string ft::ConfigFile::getErrorPage(size_t server_id, std::string page) const
{
	std::map<std::string, std::string>::const_iterator it = this->_servers[server_id].error_pages.find(page);

	if (it != this->_servers[server_id].error_pages.end())
		return (it->second);

	return ("");
}

std::vector<ft::t_location_config> ft::ConfigFile::getLocations(size_t server_id) const
{
	return (this->_servers[server_id].locations);
}

ft::t_location_config ft::ConfigFile::getLocation(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id]);
}

std::string ft::ConfigFile::getLocationEndpoint(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].endpoint);
}

std::string ft::ConfigFile::getLocationRoot(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].root);
}

std::string ft::ConfigFile::getLocationRedirect(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].redirect);
}

std::vector<std::string> ft::ConfigFile::getLocationIndexes(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].indexes);
}

std::string ft::ConfigFile::getLocationIndex(size_t server_id, size_t location_id, size_t index_id) const
{
	return (this->_servers[server_id].locations[location_id].indexes[index_id]);
}

bool ft::ConfigFile::getLocationUploadEnabled(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].upload_enabled);
}

std::string ft::ConfigFile::getLocationUploadDir(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].upload_dir);
}

bool ft::ConfigFile::getLocationCgiEnabled(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].cgi_enabled);
}

std::string ft::ConfigFile::getLocationCgiDir(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].cgi_dir);
}

bool ft::ConfigFile::getLocationAutoindex(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].autoindex);
}

bool ft::ConfigFile::getLocationAllowedMethodsGet(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].allowed_methods_get);
}

bool ft::ConfigFile::getLocationAllowedMethodsPost(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].allowed_methods_post);
}

bool ft::ConfigFile::getLocationAllowedMethodsDelete(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].allowed_methods_delete);
}

std::string ft::ConfigFile::getLocationMaxBodySize(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].max_body_size);
}

const char *ft::ConfigFile::CouldNotOpenConfigFileException::what() const throw()
{
	return (FT_ERROR "Can't open config file.");
}

const char *ft::ConfigFile::BadTokenException::what() const throw()
{
	return (FT_ERROR "Can't parse configuration file.");
}

const char *ft::ConfigFile::EmptyfileContentException::what() const throw()
{
	return (FT_ERROR "Can't find content on configuration file.");
}

const char *ft::ConfigFile::GlobalLevelUnknownTokenException::what() const throw()
{
	return (FT_ERROR "Unknown token, expect server.");
}

const char *ft::ConfigFile::CantFindServerOpenBracketException::what() const throw()
{
	return (FT_ERROR "Can't find server's open bracket \"{\" token.");
}

const char *ft::ConfigFile::CantFindServerCloseBracketException::what() const throw()
{
	return (FT_ERROR "Can't find server's close bracket \"}\" token.");
}

const char *ft::ConfigFile::EmptyServerException::what() const throw()
{
	return (FT_ERROR "Server with no content.");
}

const char *ft::ConfigFile::ServerLevelUnknownTokenException::what() const throw()
{
	return (FT_ERROR "Unknown token inside server.");
}

const char *ft::ConfigFile::PortAlreadySetException::what() const throw()
{
	return (FT_ERROR "Port already set.");
}

const char *ft::ConfigFile::CantFindPortTokenException::what() const throw()
{
	return (FT_ERROR "Can't find port token.");
}

const char *ft::ConfigFile::ServerNamesAlreadySetException::what() const throw()
{
	return (FT_ERROR "Server's Names already set.");
}

const char *ft::ConfigFile::CantFindServerNamesTokenException::what() const throw()
{
	return (FT_ERROR "Can't find Server's Names token.");
}

const char *ft::ConfigFile::CantFindErrorPageTokenException::what() const throw()
{
	return (FT_ERROR "Can't find Error Page token.");
}

const char *ft::ConfigFile::ErrorPageAlreadySetException::what() const throw()
{
	return (FT_ERROR "Error Page already set.");
}

const char *ft::ConfigFile::CantFindLocationEndpointException::what() const throw()
{
	return (FT_ERROR "Can't find location's Endpoint token.");
}

const char *ft::ConfigFile::EmptyLocationException::what() const throw()
{
	return (FT_ERROR "Location with no content.");
}

const char *ft::ConfigFile::CantFindLocationOpenBracketException::what() const throw()
{
	return (FT_ERROR "Can't find location's open bracket \"{\" token.");
}

const char *ft::ConfigFile::UploadEnabledAlreadySetException::what() const throw()
{
	return (FT_ERROR "Upload Enabled already set.");
}

const char *ft::ConfigFile::CgiEnabledAlreadySetException::what() const throw()
{
	return (FT_ERROR "CGI Enabled already set.");
}

const char *ft::ConfigFile::LocationLevelUnknownTokenException::what() const throw()
{
	return (FT_ERROR "Unknown token inside location.");
}

const char *ft::ConfigFile::CantFindLocationCloseBracketException::what() const throw()
{
	return (FT_ERROR "Can't find location's close bracket \"}\" token.");
}

const char *ft::ConfigFile::RootAlreadySetException::what() const throw()
{
	return (FT_ERROR "Root already set.");
}

const char *ft::ConfigFile::CantFindRootTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Root token.");
}

const char *ft::ConfigFile::RedirectAlreadySetException::what() const throw()
{
	return (FT_ERROR "Redirect already set.");
}

const char *ft::ConfigFile::CantFindRedirectTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Redirect token.");
}

const char *ft::ConfigFile::IndexesAlreadySetException::what() const throw()
{
	return (FT_ERROR "Indexes already set.");
}

const char *ft::ConfigFile::CantFindIndexesTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Indexes token.");
}

const char *ft::ConfigFile::CantFindUploadEnabledTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Upload Enabled token.");
}

const char *ft::ConfigFile::BadUploadEnabledTokenException::what() const throw()
{
	return (FT_ERROR "Upload Enabled not recognized as \"true\" or \"false\".");
}

const char *ft::ConfigFile::UploadDirAlreadySetException::what() const throw()
{
	return (FT_ERROR "Upload Dir already set.");
}

const char *ft::ConfigFile::CantFindUploadDirTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Upload Dir token.");
}

const char *ft::ConfigFile::CantFindCgiEnabledTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's CGI Enabled token.");
}

const char *ft::ConfigFile::BadCgiEnabledTokenException::what() const throw()
{
	return (FT_ERROR "CGI Enabled not recognized as \"true\" or \"false\".");
}

const char *ft::ConfigFile::CgiDirAlreadySetException::what() const throw()
{
	return (FT_ERROR "CGI Dir already set.");
}

const char *ft::ConfigFile::CantFindCgiDirTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's CGI Dir token.");
}

const char *ft::ConfigFile::CantFindAutoindexTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Autoindex token.");
}

const char *ft::ConfigFile::BadAutoindexTokenException::what() const throw()
{
	return (FT_ERROR "Autoindex not recognized as \"true\" or \"false\".");
}

const char *ft::ConfigFile::AutoindexAlreadySetException::what() const throw()
{
	return (FT_ERROR "Autoindex already set.");
}

const char *ft::ConfigFile::CantFindAllowedMethodsTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Allowed Methods tokens.");
}

const char *ft::ConfigFile::BadAllowedMethodsTokenException::what() const throw()
{
	return (FT_ERROR "Allowed Methods not recognized as \"GET\", \"POST\", or \"DELETE\".");
}

const char *ft::ConfigFile::AllowedMethodsAlreadySetException::what() const throw()
{
	return (FT_ERROR "Allowed Methods already set.");
}

const char *ft::ConfigFile::MaxBodySizeAlreadySetException::what() const throw()
{
	return (FT_ERROR "Max Body Size already set.");
}

const char *ft::ConfigFile::CantFindMaxBodySizeTokenException::what() const throw()
{
	return (FT_ERROR "Can't find location's Max Body Size token.");
}

static std::string ft::readFileContents(const std::string &filename)
{
	std::cout << FT_SETUP << "Reading configuration file." << std::endl;

	std::string content = "";
	std::ifstream file(filename.c_str());

	if (!file)
		throw ft::ConfigFile::CouldNotOpenConfigFileException();

	std::string line = "";

	while (std::getline(file, line))
	{
		size_t carriage_return_pos = line.find('\r');

		while (carriage_return_pos != std::string::npos)
		{
			line.erase(carriage_return_pos, 1);
			carriage_return_pos = line.find('\r', carriage_return_pos);
		}

		size_t tab_pos = line.find('\t');

		while (tab_pos != std::string::npos)
		{
			line.replace(tab_pos, 1, " ");
			tab_pos = line.find('\t', tab_pos);
		}

		size_t commentPos = line.find('#');

		if (commentPos != std::string::npos)
			line.erase(commentPos);

		bool isWhitespaceLine = true;

		for (size_t i = 0; i < line.length(); ++i)
		{
			if (!std::isspace(line[i]))
			{
				isWhitespaceLine = false;

				break;
			}
		}
		if (!isWhitespaceLine)
			content += ft::trim_spaces(line) + " # ";
	}

	std::cout << FT_OK << "Configuration file is fine." << std::endl;

	return (content);
}

static std::vector<std::string> ft::tokenizer(const std::string &fileContent)
{
	std::cout << FT_SETUP << "Creating tokens." << std::endl;

	if (fileContent == "")
		throw ft::ConfigFile::EmptyfileContentException();

	std::vector<std::string> tokens;
	std::istringstream iss;
	std::string token;

	iss.str(fileContent);
	while (iss >> token)
		tokens.push_back(token);

	std::cout << FT_OK << "Tokens are fine too." << std::endl;

	return (tokens);
}

static std::vector<ft::t_server_config> ft::parseConfigTokens(const std::vector<std::string> &tokens)
{
	std::cout << FT_SETUP << "Parsing tokens." << std::endl;

	std::vector<ft::t_server_config> servers;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		while (tokens[i] == "#")
			i++;
		if (tokens[i++] == "server")
		{
			while (tokens[i] == "#")
				i++;
			if (tokens[i] != "{")
				throw ft::ConfigFile::CantFindServerOpenBracketException();

			while (tokens[i] == "#")
				i++;
			if (tokens[i++] != "{")
				throw ft::ConfigFile::CantFindServerOpenBracketException();

			while (tokens[i] == "#")
				i++;
			if (tokens[i] == "}")
				throw ft::ConfigFile::EmptyServerException();

			servers.push_back(parseServer(tokens, i));
		}
		else if (i < tokens.size())
			throw ft::ConfigFile::GlobalLevelUnknownTokenException();
	}

	std::cout << FT_OK << "Parsing is celebrating a successful day." << std::endl;

	return (servers);
}

static std::string ft::trim_spaces(const std::string &str)
{
	std::string trimmedStr = str;
	size_t start = 0;

	while (start < trimmedStr.length() && std::isspace(trimmedStr[start]))
		++start;
	trimmedStr.erase(0, start);

	size_t end = trimmedStr.length();
	while (end > 0 && std::isspace(trimmedStr[end - 1]))
		--end;
	trimmedStr.erase(end);

	return (trimmedStr);
}

static ft::t_server_config ft::parseServer(const std::vector<std::string> &tokens, size_t &i)
{
	ft::t_server_config server;

	while (tokens[i] == "#")
		i++;
	while (i < tokens.size() && tokens[i] != "}")
	{
		while (tokens[i] == "#")
			i++;

		if (tokens[i] == "}")
			continue;
		else if (tokens[i] == "port")
			parsePort(server.port, tokens, i);
		else if (tokens[i] == "server_names")
			parseServerNames(server.server_names, tokens, i);
		else if (tokens[i] == "error_page")
			parseErrorPages(server.error_pages, tokens, i);
		else if (tokens[i] == "location")
			server.locations.push_back(parseLocations(tokens, i));
		else if (i < tokens.size())
			throw ft::ConfigFile::ServerLevelUnknownTokenException();

		i++;
	}

	if (tokens[i] != "}")
		throw ft::ConfigFile::CantFindServerCloseBracketException();

	return (server);
}

static void ft::parsePort(std::string &port, const std::vector<std::string> &tokens, size_t &i)
{
	if (port != "")
		throw ft::ConfigFile::PortAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindPortTokenException();
	port = tokens[i++];
}

static void ft::parseServerNames(std::vector<std::string> &server_names, const std::vector<std::string> &tokens, size_t &i)
{
	if (!server_names.empty())
		throw ft::ConfigFile::ServerNamesAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindServerNamesTokenException();
	while (i < tokens.size() && tokens[i] != "#")
		server_names.push_back(tokens[i++]);
}

static void ft::parseErrorPages(std::map<std::string, std::string> &error_pages, const std::vector<std::string> &tokens, size_t &i)
{
	i++;
	if (i >= tokens.size() || tokens[i] == "#" || tokens[i + 1] == "#")
		throw ft::ConfigFile::CantFindErrorPageTokenException();

	std::map<std::string, std::string>::iterator it = error_pages.find(tokens[i]);

	if (it != error_pages.end())
		throw ft::ConfigFile::ErrorPageAlreadySetException();

	error_pages.insert(std::make_pair(tokens[i], tokens[i + 1]));
	i += 2;
}

static ft::t_location_config ft::parseLocations(const std::vector<std::string> &tokens, size_t &i)
{
	t_location_config location;
	bool upload_enabled_initialized = false;
	bool cgi_enabled_initialized = false;
	bool autoindex_initialized = false;
	bool allowed_methods_initialized = false;

	location.allowed_methods_get = true;
	location.allowed_methods_post = true;
	location.allowed_methods_delete = true;

	i++;

	while (tokens[i] == "#")
		i++;
	if (tokens[i] == "{")
		throw ft::ConfigFile::CantFindLocationEndpointException();
	location.endpoint = tokens[i++];

	while (tokens[i] == "#")
		i++;
	if (tokens[i++] != "{")
		throw ft::ConfigFile::CantFindLocationOpenBracketException();

	while (tokens[i] == "#")
		i++;
	if (tokens[i] == "}")
		throw ft::ConfigFile::EmptyLocationException();

	while (tokens[i] == "#")
		i++;
	while (i < tokens.size() && tokens[i] != "}")
	{
		if (tokens[i] == "root")
			parseRoot(location.root, tokens, i);
		else if (tokens[i] == "redirect")
			parseRedirect(location.redirect, tokens, i);
		else if (tokens[i] == "indexes")
			parseIndexes(location.indexes, tokens, i);
		else if (tokens[i] == "upload_enabled" && upload_enabled_initialized)
			throw ft::ConfigFile::UploadEnabledAlreadySetException();
		else if (tokens[i] == "upload_enabled" && !upload_enabled_initialized)
		{
			parseUploadEnabled(location.upload_enabled, tokens, i);
			upload_enabled_initialized = true;
		}
		else if (tokens[i] == "upload_dir")
			parseUploadDir(location.upload_dir, tokens, i);
		else if (tokens[i] == "cgi_enabled" && cgi_enabled_initialized)
			throw ft::ConfigFile::CgiEnabledAlreadySetException();
		else if (tokens[i] == "cgi_enabled" && !cgi_enabled_initialized)
		{
			parseCgiEnabled(location.cgi_enabled, tokens, i);
			cgi_enabled_initialized = true;
		}
		else if (tokens[i] == "cgi_dir")
			parseCgiDir(location.cgi_dir, tokens, i);
		else if (tokens[i] == "autoindex" && autoindex_initialized)
			throw ft::ConfigFile::AutoindexAlreadySetException();
		else if (tokens[i] == "autoindex" && !autoindex_initialized)
		{
			parseAutoindex(location.autoindex, tokens, i);
			autoindex_initialized = true;
		}
		else if (tokens[i] == "allowed_methods" && allowed_methods_initialized)
			throw ft::ConfigFile::AllowedMethodsAlreadySetException();
		else if (tokens[i] == "allowed_methods" && !allowed_methods_initialized)
		{
			parseAllowedMethods(location.allowed_methods_get, location.allowed_methods_post, location.allowed_methods_delete, tokens, i);
			allowed_methods_initialized = true;
		}
		else if (tokens[i] == "max_body_size")
			parseMaxBodySize(location.max_body_size, tokens, i);
		else if (tokens[i] == "location" || tokens[i] == "server")
			throw ft::ConfigFile::CantFindLocationCloseBracketException();
		else
			throw ft::ConfigFile::LocationLevelUnknownTokenException();
		i++;
	}
	if (tokens[i] != "}")
		throw ft::ConfigFile::CantFindLocationCloseBracketException();

	return (location);
}

static void ft::parseRoot(std::string &root, const std::vector<std::string> &tokens, size_t &i)
{
	if (root != "")
		throw ft::ConfigFile::RootAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindRootTokenException();
	root = tokens[i++];
}

static void ft::parseRedirect(std::string &redirect, const std::vector<std::string> &tokens, size_t &i)
{
	if (redirect != "")
		throw ft::ConfigFile::RedirectAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindRedirectTokenException();
	redirect = tokens[i++];
}

static void ft::parseIndexes(std::vector<std::string> &indexes, const std::vector<std::string> &tokens, size_t &i)
{
	if (!indexes.empty())
		throw ft::ConfigFile::IndexesAlreadySetException();

	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindIndexesTokenException();

	while (i < tokens.size() && tokens[i] != "#")
		indexes.push_back(tokens[i++]);
}

static void ft::parseUploadEnabled(bool &upload_enabled, const std::vector<std::string> &tokens, size_t &i)
{
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindUploadEnabledTokenException();
	if (tokens[i] == "true")
		upload_enabled = true;
	else if (tokens[i] == "false")
		upload_enabled = false;
	else
		throw ft::ConfigFile::BadUploadEnabledTokenException();
	i++;
}

static void ft::parseUploadDir(std::string &upload_dir, const std::vector<std::string> &tokens, size_t &i)
{
	if (upload_dir != "")
		throw ft::ConfigFile::UploadDirAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindUploadDirTokenException();
	upload_dir = tokens[i++];
}

static void ft::parseCgiEnabled(bool &cgi_enabled, const std::vector<std::string> &tokens, size_t &i)
{
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindCgiEnabledTokenException();
	if (tokens[i] == "true")
		cgi_enabled = true;
	else if (tokens[i] == "false")
		cgi_enabled = false;
	else
		throw ft::ConfigFile::BadCgiEnabledTokenException();
	i++;
}

static void ft::parseCgiDir(std::string &cgi_dir, const std::vector<std::string> &tokens, size_t &i)
{
	if (cgi_dir != "")
		throw ft::ConfigFile::CgiDirAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindCgiDirTokenException();
	cgi_dir = tokens[i++];
}

static void ft::parseAutoindex(bool &autoindex, const std::vector<std::string> &tokens, size_t &i)
{
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindAutoindexTokenException();
	if (tokens[i] == "true")
		autoindex = true;
	else if (tokens[i] == "false")
		autoindex = false;
	else
		throw ft::ConfigFile::BadAutoindexTokenException();
	i++;
}

static void ft::parseAllowedMethods(bool &allowed_methods_get, bool &allowed_methods_post, bool &allowed_methods_delete, const std::vector<std::string> &tokens, size_t &i)
{
	bool get_init = false;
	bool post_init = false;
	bool delete_init = false;

	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindAllowedMethodsTokenException();
	while (i < tokens.size() && tokens[i] != "#")
	{
		std::string token_upper = tokens[i];

		for (size_t j = 0; j < token_upper.size(); j++)
			token_upper[j] = std::toupper(token_upper[j]);

		if (token_upper == "GET" && get_init == false)
			get_init = true;
		else if (token_upper == "POST" && post_init == false)
			post_init = true;
		else if (token_upper == "DELETE" && delete_init == false)
			delete_init = true;
		else if (token_upper == "GET" || token_upper == "POST" || token_upper == "DELETE")
			throw ft::ConfigFile::AllowedMethodsAlreadySetException();
		else
			throw ft::ConfigFile::BadAllowedMethodsTokenException();

		i++;
	}

	if (get_init == true || post_init == true || delete_init == true)
	{
		if (get_init == false)
			allowed_methods_get = false;
		if (post_init == false)
			allowed_methods_post = false;
		if (delete_init == false)
			allowed_methods_delete = false;
	}
}

static void ft::parseMaxBodySize(std::string &max_body_size, const std::vector<std::string> &tokens, size_t &i)
{
	if (max_body_size != "")
		throw ft::ConfigFile::MaxBodySizeAlreadySetException();
	i++;
	if (i >= tokens.size() || tokens[i] == "#")
		throw ft::ConfigFile::CantFindMaxBodySizeTokenException();
	max_body_size = tokens[i++];
}

std::ostream &operator<<(std::ostream &out, const ft::ConfigFile &config_file)
{
	out
		<< YELLOW << "server counter: " << RESET_COLOR << config_file.size()
		<< std::endl;
	out << config_file.getServers();

	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<ft::t_server_config> &servers)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		out << GREEN << "id " << RESET_COLOR << i << '\n';
		out << servers[i];
	}

	return (out);
}

std::ostream &operator<<(std::ostream &out, const ft::t_server_config &server)
{
	out << GREEN << "server " << RESET_COLOR << "{\n";

	out << "\t" << GREEN << "port " << RESET_COLOR << "[" << server.port << "]"
		<< "\n";

	out << "\t" << GREEN << "server_names " << RESET_COLOR;
	for (size_t i = 0; i < server.server_names.size(); i++)
		out << "[" << server.server_names[i] << "] ";
	out << "\n";

	std::map<std::string, std::string>::const_iterator it;
	for (it = server.error_pages.begin(); it != server.error_pages.end(); it++)
		out << "\t" << GREEN << "error_page " << RESET_COLOR << "[" << it->first << "] [" << it->second << "]"
			<< "\n";

	out << server.locations;

	out << "}" << std::endl;

	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<ft::t_location_config> &locations)
{
	if (locations.empty())
		return (out);

	std::vector<ft::t_location_config>::const_iterator it = locations.begin();

	while (it != locations.end())
		out << *it++;

	return (out);
}

std::ostream &operator<<(std::ostream &out, const ft::t_location_config &location)
{
	out << "\t" << GREEN << "location " << RESET_COLOR << location.endpoint << " {\n";

	out << "\t\t" << GREEN << "root " << RESET_COLOR << "[" << location.root << "]"
		<< "\n";

	out << "\t\t" << GREEN << "redirect " << RESET_COLOR << "[" << location.redirect << "]"
		<< "\n";

	out << "\t\t" << GREEN << "indexes " << RESET_COLOR;
	for (size_t i = 0; i < location.indexes.size(); i++)
		out << "[" << location.indexes[i] << "] ";
	if (location.indexes.size() == 0)
		out << "[]";
	out << "\n";

	out << "\t\t" << GREEN << "upload_enabled " << RESET_COLOR << "[";
	out << ((location.upload_enabled == true) ? "true" : "false");
	out << "]"
		<< "\n";
	out << "\t\t" << GREEN << "upload_dir " << RESET_COLOR << "[" << location.upload_dir << "]"
		<< "\n";

	out << "\t\t" << GREEN << "cgi_enabled " << RESET_COLOR << "[";
	out << ((location.cgi_enabled == true) ? "true" : "false");
	out << "]"
		<< "\n";
	out << "\t\t" << GREEN << "cgi_dir " << RESET_COLOR << "[" << location.cgi_dir << "]"
		<< "\n";

	out << "\t\t" << GREEN << "autoindex " << RESET_COLOR;
	out << ((location.autoindex == true) ? "[true]\n" : "[false]\n");

	out << "\t\t" << GREEN << "allowed_methods: " << RESET_COLOR;
	out << ((location.allowed_methods_get == true) ? "[GET] " : "[] ");
	out << ((location.allowed_methods_post == true) ? "[POST] " : "[] ");
	out << ((location.allowed_methods_delete == true) ? "[DELETE]\n" : "[]\n");

	out << "\t\t" << GREEN << "max_body_size " << RESET_COLOR << "[" << location.max_body_size << "]"
		<< "\n";

	out << "\t}" << std::endl;

	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::vector<std::string> &strs)
{
	for (size_t i = 0; i < strs.size(); i++)
		out << "[" << strs[i] << "] ";

	return (out);
}

std::ostream &operator<<(std::ostream &out, const std::map<std::string, std::string> &strs)
{
	for (std::map<std::string, std::string>::const_iterator it = strs.begin(); it != strs.end(); it++)
		out << "[" << it->first << "] [" << it->second << "] " << std::endl;

	return (out);
}
