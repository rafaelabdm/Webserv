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

ft::ConfigFile::ConfigFile(const std::string& config_file)
{
	std::string					fileContent = ft::readFileContents(config_file);
	std::vector<std::string>	tokens = ft::tokenizer(fileContent);

	std::cout
		<< FT_SETUP
		<< "Parsing "
		<< GREEN << config_file << RESET_COLOR
		<< " configuration file."
		<< std::endl;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens[i] == "server")
		{
			i++;
			while (tokens[i] == "#")
				i++;
			if (tokens[i] != "{")
				throw ft::ConfigFile::BadTokenException();
			i++;
			this->_servers.push_back(parseServer(tokens, i));
		}
	}

	return;
}

ft::ConfigFile::~ConfigFile()
{
	std::cout << FT_CLOSE << "Closing configuration file." << std::endl;

	return;
}

size_t	ft::ConfigFile::size(void) const
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

std::string	ft::ConfigFile::getPort(size_t server_id) const
{
	return (this->_servers[server_id].port);
}

std::vector<std::string>	ft::ConfigFile::getServerNames(size_t server_id) const
{
	return (this->_servers[server_id].server_names);
}

std::string	ft::ConfigFile::getServerName(size_t server_id, size_t server_name_id) const
{
	return (this->_servers[server_id].server_names[server_name_id]);
}

std::map<std::string, std::string>	ft::ConfigFile::getErrorPages(size_t server_id) const
{
	return(this->_servers[server_id].error_pages);
}

std::string	ft::ConfigFile::getErrorPage(size_t server_id, std::string page) const
{
	std::map<std::string, std::string>::const_iterator	it = this->_servers[server_id].error_pages.find(page);

	if (it != this->_servers[server_id].error_pages.end())
		return (it->second);

	return ("");
}

std::vector<ft::t_location_config>	ft::ConfigFile::getLocations(size_t server_id) const
{
	return (this->_servers[server_id].locations);
}

ft::t_location_config	ft::ConfigFile::getLocation(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id]);
}

std::string	ft::ConfigFile::getLocationEndpoint(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].endpoint);
}

std::string	ft::ConfigFile::getLocationRoot(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].root);
}

std::string	ft::ConfigFile::getLocationRedirect(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].redirect);
}

std::vector<std::string>	ft::ConfigFile::getLocationIndexes(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].indexes);
}

std::string	ft::ConfigFile::getLocationIndex(size_t server_id, size_t location_id, size_t index_id) const
{
	return (this->_servers[server_id].locations[location_id].indexes[index_id]);
}

bool	ft::ConfigFile::getLocationUploadEnabled(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].upload_enabled);
}

std::string	ft::ConfigFile::getLocationUploadDir(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].upload_dir);
}

bool	ft::ConfigFile::getLocationCgiEnabled(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].cgi_enabled);
}

std::string	ft::ConfigFile::getLocationCgiDir(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].cgi_dir);
}

bool	ft::ConfigFile::getLocationAutoindex(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].autoindex);
}

bool	ft::ConfigFile::getLocationAllowedMethodsGet(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].allowed_methods_get);
}

bool	ft::ConfigFile::getLocationAllowedMethodsPost(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].allowed_methods_post);
}

bool	ft::ConfigFile::getLocationAllowedMethodsDelete(size_t server_id, size_t location_id) const
{
	return (this->_servers[server_id].locations[location_id].allowed_methods_delete);
}

const char*	ft::ConfigFile::CouldNotOpenConfigFileException::what () const throw ()
{
	return (FT_FAIL "Error: Can't open config file.");
}

const char*	ft::ConfigFile::BadTokenException::what () const throw ()
{
	return (FT_FAIL "Error: Can't parse configuration file.");
}

static std::string	ft::readFileContents(const std::string& filename)
{
	std::cout << FT_SETUP << "Reading configuration file." << std::endl;

	std::string	content = "";

	try
	{
		std::ifstream	file(filename.c_str());

		if (!file)
			throw ft::ConfigFile::CouldNotOpenConfigFileException();

		std::string	line = "";

		while (std::getline(file, line))
		{
			size_t	carriage_return_pos = line.find('\r');

			while (carriage_return_pos != std::string::npos)
			{
				line.erase(carriage_return_pos, 1);
				carriage_return_pos = line.find('\r', carriage_return_pos);
			}

			size_t	tab_pos = line.find('\t');

			while (tab_pos != std::string::npos)
			{
				line.replace(tab_pos, 1, " ");
				tab_pos = line.find('\t', tab_pos);
			}

			size_t	commentPos = line.find('#');

			if (commentPos != std::string::npos)
				line.erase(commentPos);

			bool	isWhitespaceLine = true;

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
	}
	catch (ConfigFile::CouldNotOpenConfigFileException& e)
	{ std::cout << "ERROR 12: " << e.what() << std::endl; }


	return (content);
}

static std::vector<std::string>	ft::tokenizer(const std::string& fileContent)
{
	std::cout << FT_SETUP << "Creating tokens." << std::endl;

	std::vector<std::string>	tokens;
	std::istringstream			iss;
	std::string					token;

	iss.str(fileContent);
	while (iss >> token)
		tokens.push_back(token);

	std::cout << FT_OK << "Tokens are fine too." << std::endl;

	return (tokens);
}

static std::string	ft::trim_spaces(const std::string& str)
{
	std::string	trimmedStr = str;
	size_t		start = 0;

	while (start < trimmedStr.length() && std::isspace(trimmedStr[start]))
		++start;
	trimmedStr.erase(0, start);

	size_t	end = trimmedStr.length();
	while (end > 0 && std::isspace(trimmedStr[end - 1]))
		--end;
	trimmedStr.erase(end);

	return (trimmedStr);
}

static ft::t_server_config	ft::parseServer(const std::vector<std::string>& tokens, size_t& i)
{
	ft::t_server_config	server;

	while (tokens[i] == "#")
		i++;
	try
	{
		while (i < tokens.size() && tokens[i] != "}")
		{
			while (tokens[i] == "#")
				i++;
			if (tokens[i] == "}")
				continue;
			if (tokens[i] == "port")
				parsePort(server.port, tokens, i);
			else if (tokens[i] == "server_names")
				parseServerNames(server.server_names, tokens, i);
			else if (tokens[i] == "error_page")
				parseErrorPages(server.error_pages, tokens, i);
			else if (tokens[i] == "location")
				server.locations.push_back(parseLocations(tokens, i));
			else
			{
				std::cout << tokens[i] << std::endl;
				throw ft::ConfigFile::BadTokenException();
			}
			i++;
		}
		if (tokens[i] != "}")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 01: " << e.what() << std::endl; }

	return (server);
}

static void	ft::parsePort(std::string& port, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (port != "")
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		port = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 02: " << e.what() << std::endl; }
}

static void	ft::parseServerNames(std::vector<std::string>& server_names, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (!server_names.empty())
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		while (i < tokens.size() && tokens[i] != "#")
		{
			server_names.push_back(tokens[i++]);
		}
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 03: " << e.what() << std::endl; }
}

static void	ft::parseErrorPages(std::map<std::string, std::string>& error_pages, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		i++;
		if (i >= tokens.size() || tokens[i] == "#" || tokens[i + 1] == "#")
			throw ft::ConfigFile::BadTokenException();

		std::map<std::string, std::string>::iterator it = error_pages.find(tokens[i]);

		if (it != error_pages.end())
			throw ft::ConfigFile::BadTokenException();

		error_pages.insert(std::make_pair(tokens[i], tokens[i + 1]));
		i += 2;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 04: " << e.what() << std::endl; }
}

static ft::t_location_config	ft::parseLocations(const std::vector<std::string>& tokens, size_t& i)
{
	t_location_config	location;
	bool				upload_enabled_initialized = false;
	bool				cgi_enabled_initialized = false;

	try
	{
		while (tokens[i] == "#")
			i++;
		if (tokens[i] == "}")
			throw ft::ConfigFile::BadTokenException();
		i++;
		location.endpoint = tokens[i++];

		if (tokens[i] == "{")
			i++;
		else
			throw ft::ConfigFile::BadTokenException();

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
				throw ft::ConfigFile::BadTokenException();
			else if (tokens[i] == "upload_enabled" && !upload_enabled_initialized)
			{
				parseUploadEnabled(location.upload_enabled, tokens, i);
				upload_enabled_initialized = true;
			}
			else if (tokens[i] == "upload_dir")
				parseUploadDir(location.upload_dir, tokens, i);
			else if (tokens[i] == "cgi_enabled" && cgi_enabled_initialized)
				throw ft::ConfigFile::BadTokenException();
			else if (tokens[i] == "cgi_enabled" && !cgi_enabled_initialized)
			{
				parseCgiEnabled(location.cgi_enabled, tokens, i);
				cgi_enabled_initialized = true;
			}
			else if (tokens[i] == "cgi_dir")
				parseCgiDir(location.cgi_dir, tokens, i);
			else if (tokens[i] == "autoindex")
				parseAutoindex(location.autoindex, tokens, i);
			else if (tokens[i] == "allowed_methods")
				parseAllowedMethods(location.allowed_methods_get, location.allowed_methods_post, location.allowed_methods_delete, tokens, i);
			else
				throw ft::ConfigFile::BadTokenException();
			i++;
		}
		if (tokens[i] != "}")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 05: " << e.what() << std::endl; }

	return (location);
}

static void	ft::parseRoot(std::string& root, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (root != "")
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		root = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 06: " << e.what() << std::endl; }
}

static void	ft::parseRedirect(std::string& redirect, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (redirect != "")
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		redirect = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }
}

static void	ft::parseIndexes(std::vector<std::string>& indexes, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (!indexes.empty())
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		while (i < tokens.size() && tokens[i] != "#")
		{
			indexes.push_back(tokens[i++]);
		}
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 07: " << e.what() << std::endl; }
}

static void	ft::parseUploadEnabled(bool& upload_enabled, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		if (tokens[i] == "true")
			upload_enabled = true;
		else if (tokens[i] == "false")
			upload_enabled = false;
		else
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }
}

static void	ft::parseUploadDir(std::string& upload_dir, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (upload_dir != "")
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		upload_dir = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 08: " << e.what() << std::endl; }
}

static void	ft::parseCgiEnabled(bool& cgi_enabled, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		if (tokens[i] == "true")
			cgi_enabled = true;
		else if (tokens[i] == "false")
			cgi_enabled = false;
		else
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }
}

static void	ft::parseCgiDir(std::string& cgi_dir, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (cgi_dir != "")
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		cgi_dir = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 09: " << e.what() << std::endl; }
}
static void	ft::parseAutoindex(bool& autoindex, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		if (tokens[i] == "true")
			autoindex = true;
		else if (tokens[i] == "false")
			autoindex = false;
		else
			throw ft::ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 10: " << e.what() << std::endl; }
}

static void	ft::parseAllowedMethods(bool& allowed_methods_get, bool& allowed_methods_post, bool& allowed_methods_delete, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		bool	get_init = false;
		bool	post_init = false;
		bool	delete_init = false;

		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ft::ConfigFile::BadTokenException();
		while (i < tokens.size() && tokens[i] != "#")
		{
			std::string	token_upper = tokens[i];

			for (size_t j = 0; j < token_upper.size(); j++)
				token_upper[j] = std::toupper(token_upper[j]);

			if (token_upper == "GET" && get_init == false)
				allowed_methods_get = get_init = true;
			else if (token_upper == "POST" && post_init == false)
				allowed_methods_post = post_init = true;
			else if (token_upper == "DELETE" && delete_init == false)
				allowed_methods_delete = delete_init = true;
			else
				throw ft::ConfigFile::BadTokenException();

			i++;
		}
		if (i >= tokens.size() || tokens[i] != "#")
			throw ft::ConfigFile::BadTokenException();
	}
	catch (ft::ConfigFile::BadTokenException& e)
	{ std::cout << "ERROR 11: " << e.what() << std::endl; }
}

std::ostream&	operator <<(std::ostream& out, const ft::ConfigFile& config_file)
{
	out
		<< YELLOW << "server counter: " << RESET_COLOR << config_file.size()
		<< std::endl;
	out << config_file.getServers();

	return (out);
}

std::ostream&	operator <<(std::ostream& out, const std::vector<ft::t_server_config>& servers)
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		out << GREEN << "id " << RESET_COLOR << i << '\n';
		out << servers[i];
	}

	return (out);
}

std::ostream&	operator <<(std::ostream& out, const ft::t_server_config& server)
{
	out << GREEN << "server " << RESET_COLOR << "{\n";

	out << "\t" << GREEN << "port " << RESET_COLOR << "[" << server.port << "]" << "\n";

	out << "\t" << GREEN << "server_names " << RESET_COLOR;
	for (size_t i = 0; i < server.server_names.size(); i++)
		out << "[" << server.server_names[i] << "] ";
	out << "\n";

	std::map<std::string, std::string>::const_iterator	it;
	for (it = server.error_pages.begin(); it != server.error_pages.end(); it++)
		out << "\t" << GREEN << "error_page " << RESET_COLOR << "[" << it->first << "] [" << it->second << "]" << "\n";

	out << server.locations;

	out << "}" << std::endl;

	return (out);
}

std::ostream&	operator <<(std::ostream& out, const std::vector<ft::t_location_config>& locations)
{
	if (locations.empty())
		return (out);

	std::vector<ft::t_location_config>::const_iterator	it = locations.begin();

	while (it != locations.end())
		out << *it++;

	return (out);
}

std::ostream&	operator <<(std::ostream& out, const ft::t_location_config& location)
{
		out << "\t" << GREEN << "location " << RESET_COLOR << location.endpoint << " {\n";

		out << "\t\t" << GREEN << "root " << RESET_COLOR << "[" << location.root << "]" << "\n";

		out << "\t\t" << GREEN << "redirect " << RESET_COLOR << "[" << location.redirect << "]" << "\n";

		out << "\t\t" << GREEN << "indexes " << RESET_COLOR;
		for (size_t i = 0; i < location.indexes.size(); i++)
			out << "[" << location.indexes[i] << "] ";
		if (location.indexes.size() == 0)
			out << "[]";
		out << "\n";

		out << "\t\t" << GREEN << "upload_enabled " << RESET_COLOR << "[";
		out << ((location.upload_enabled == true)? "true": "false");
		out << "]" << "\n";
		out << "\t\t" << GREEN << "upload_dir " << RESET_COLOR << "[" << location.upload_dir << "]" << "\n";

		out << "\t\t" << GREEN << "cgi_enabled " << RESET_COLOR << "[";
		out << ((location.cgi_enabled == true)? "true": "false");
		out << "]" << "\n";
		out << "\t\t" << GREEN << "cgi_dir " << RESET_COLOR << "[" << location.cgi_dir << "]" << "\n";

		out << "\t\t" << GREEN << "autoindex " << RESET_COLOR;
		out << ((location.autoindex == true)? "[true]\n": "[false]\n");

		out << "\t\t" << GREEN << "allowed_methods: " << RESET_COLOR;
		out << ((location.allowed_methods_get == true)? "[GET] ": "[]");
		out << ((location.allowed_methods_post == true)? "[POST] ": "[]");
		out << ((location.allowed_methods_delete == true)? "[DELETE]\n": "[]\n");

		out << "\t}" << std::endl;

	return (out);
}

std::ostream&	operator <<(std::ostream& out, const std::vector<std::string>& strs)
{
	for (size_t i = 0; i < strs.size(); i++)
		out << "[" << strs[i] << "] ";

	return (out);
}

std::ostream&	operator <<(std::ostream& out, const std::map<std::string, std::string>& strs)
{
	for (std::map<std::string, std::string>::const_iterator it = strs.begin(); it != strs.end(); it++)
		out << "[" << it->first << "] [" << it->second << "] " << std::endl;

	return (out);
}
