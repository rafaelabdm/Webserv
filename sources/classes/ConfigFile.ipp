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

	try
	{
		for (size_t i = 0; ft::keep() && i < tokens.size(); i++)
		{
			if (tokens[i] == "server")
			{
				i++;
				while (ft::keep() && tokens[i] == "#")
					i++;
				if (tokens[i] != "{")
					throw ConfigFile::BadTokenException();
				i++;
				this->_servers.push_back(parseServer(tokens, i));
			}
		}
	}
	catch (ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }

	return;
}

ft::ConfigFile::~ConfigFile()
{
	std::cout << FT_CLOSE << "Closing configuration file." << std::endl;

	return;
}

size_t	ft::ConfigFile::size(void) const
{ return ( _servers.size() ); }

ft::t_server_config ft::ConfigFile::getServer(size_t server_id) const
{ return ( this->_servers[server_id] ); }

std::string	ft::ConfigFile::getHost(size_t server_id) const
{ return ( this->_servers[server_id].host ); }

std::string	ft::ConfigFile::getPort(size_t server_id) const
{ return ( this->_servers[server_id].port ); }

const char*	ft::ConfigFile::CouldNotOpenConfigFileException::what () const throw ()
{ return (FT_FAIL "Error: Can't open config file."); }

const char*	ft::ConfigFile::BadTokenException::what () const throw ()
{ return (FT_FAIL "Error: Can't parse configuration file."); }

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
	}
	catch (ConfigFile::CouldNotOpenConfigFileException& e)
	{ std::cout << e.what() << std::endl; }

	std::cout << FT_OK << "Configuration file is fine." << std::endl;

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

	size_t start = 0;
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
	t_server_config	server;

	while (ft::keep() && tokens[i] == "#")
		i++;
	try
	{
		while (ft::keep() && i < tokens.size() && tokens[i] != "}")
		{
			if (tokens[i] == "host")
				parseHost(server.host, tokens, i);
			else if (tokens[i] == "port")
				parsePort(server.port, tokens, i);
			i++;
		}
		if (tokens[i] != "}")
			throw ConfigFile::BadTokenException();
	}
	catch (ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }
	return (server);
}

static void	ft::parseHost(std::string& host, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (host != "")
			throw ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ConfigFile::BadTokenException();
		host = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ConfigFile::BadTokenException();
	}
	catch (ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }
}

static void	ft::parsePort(std::string& port, const std::vector<std::string>& tokens, size_t& i)
{
	try
	{
		if (port != "")
			throw ConfigFile::BadTokenException();
		i++;
		if (i >= tokens.size() || tokens[i] == "#")
			throw ConfigFile::BadTokenException();
		port = tokens[i];
		i++;
		if (i >= tokens.size() || tokens[i] != "#")
			throw ConfigFile::BadTokenException();
	}
	catch (ConfigFile::BadTokenException& e)
	{ std::cout << e.what() << std::endl; }
}
