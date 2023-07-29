#include <ConfigFile.hpp>

static void debugMessage(const std::string& action, const std::string& message, const std::string& color)
{
  if(DEBUG)
    std::cout << "[ " << color << action <<  RESET_COLOR " ] " << message << std::endl;

  return;
}

static std::string trim_spaces(const std::string& str)
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

static std::string readFileContents(const std::string& filename)
{
  std::string content = "";

  try
  {
    std::ifstream file(filename.c_str());

    if (!file)
      throw ConfigFile::CouldOpenConfigFileException ();

    std::string line = "";
    while (std::getline(file, line))
    {

      size_t pos = line.find('\r');
      while (pos != std::string::npos)
      {
        line.erase(pos, 1);
        pos = line.find('\r', pos);
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
        content += trim_spaces(line) + ' ';
    }
  }
  catch ( ConfigFile::CouldOpenConfigFileException& e )
  { std::cout << e.what (); }

  return (content);
}

static std::vector<std::string> tokenizer(const std::string& fileContent)
{
  std::vector<std::string> tokens;
  std::istringstream iss;
  std::string token;

  iss.str(fileContent);
  while (iss >> token)
    tokens.push_back(token);

  return (tokens);
}

static t_location_config parseLocation(const std::vector<std::string>& tokens, size_t* i)
{
  t_location_config location;

  if (tokens[*i] == "location")
  {
    location.dir = tokens[*i + 1];
    (*i)++;
  }

  while (*i < tokens.size() && tokens[*i] != "}")
  {
    if (tokens[*i] == "root")
      location.root = tokens[*i + 1];
    else if (tokens[*i] == "index")
      location.index = tokens[*i + 1];
    else if (tokens[*i] == "redirect")
      location.redirect = tokens[*i + 1];
    else if (tokens[*i] == "upload_enabled")
      location.upload_enabled = tokens[*i + 1];
    else if (tokens[*i] == "upload_dir")
      location.upload_dir = tokens[*i + 1];
    else if (tokens[*i] == "cgi_enabled")
      location.cgi_enabled = tokens[*i + 1];
    else if (tokens[*i] == "cgi_path")
      location.cgi_path = tokens[*i + 1];

    (*i)++;
  }

  return (location);
}

static t_server_config parseServer(const std::vector<std::string>& tokens, size_t* i)
{
  t_server_config server;

  while (*i < tokens.size() && tokens[*i] != "}")
  {
    if (tokens[*i] == "location")
      server.locations.push_back(parseLocation(tokens, i));
    else
    {
      if (tokens[*i] == "host")
        server.host = tokens[*i + 1];
      else if (tokens[*i] == "port")
        server.port = tokens[*i + 1];
      else if (tokens[*i] == "server_name")
        server.server_name = tokens[*i + 1];
      else if (tokens[*i] == "error_page")
      {
        server.error_page[tokens[*i + 1]] = tokens[*i + 2];
        (*i)++;
      }
    }
    (*i)++;
  }

  return (server);
}

ConfigFile::ConfigFile(const std::string& filename) : size(0)
{
  debugMessage(CONFIG_FILE_MSG, "ConfigFile's constructor called", BLUE);

  std::string                   fileContent = readFileContents(filename);
  std::vector<std::string>      tokens = tokenizer(fileContent);

  for (size_t i = 0; i < tokens.size(); i++)
  {
    if (tokens[i] == "server")
      this->_servers.push_back(parseServer(tokens, &i));
  }

  const_cast<size_t&>(this->size) = _servers.size();

  return;
}

ConfigFile::~ConfigFile(void)
{
  debugMessage(CONFIG_FILE_MSG, "ConfigFile's destructor called", BLUE);

  return;
}

std::vector<t_server_config> ConfigFile::getServers(void) const
{ return ( this->_servers ); }

std::vector<t_location_config> ConfigFile::getLocations(size_t server_id) const
{ return ( this->_servers[server_id].locations ); }

t_server_config ConfigFile::getServer(size_t server_id) const
{ return ( this->_servers[server_id] ); }

t_location_config ConfigFile::getLocation(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id] ); }

std::string ConfigFile::getHost(size_t server_id) const
{ return ( this->_servers[server_id].host ); }

std::string ConfigFile::getPort(size_t server_id) const
{ return ( this->_servers[server_id].port ); }

std::string ConfigFile::getServerName(size_t server_id) const
{ return ( this->_servers[server_id].server_name ); }

std::string ConfigFile::getLocationDir(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].dir ); }

std::string ConfigFile::getLocationRoot(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].root ); }

std::string ConfigFile::getLocationIndex(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].index ); }

std::string ConfigFile::getLocationRedirect(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].redirect ); }

std::string ConfigFile::getLocationUploadEnabled(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].upload_enabled ); }

std::string ConfigFile::getLocationUploadDir(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].upload_dir ); }

std::string ConfigFile::getLocationCgiEnabled(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].cgi_enabled ); }

std::string ConfigFile::getLocationCgiPath(size_t server_id, size_t location_id) const
{ return ( this->_servers[server_id].locations[location_id].cgi_path ); }

std::ostream& operator<<(std::ostream& out, const ConfigFile& config_file)
{
  out << config_file.getServers();

  return ( out );
}

std::ostream& operator<<(std::ostream& out, const std::vector<t_server_config>& servers)
{
  out << YELLOW << "server counter: " << RESET_COLOR << servers.size() << std::endl;

  for (size_t i = 0; i < servers.size(); i++)
  {
    out << GREEN << "id " << RESET_COLOR << i << '\n';
    out << servers[i];
  }
  out << std::endl;

  return ( out );
}

std::ostream& operator<<(std::ostream& out, const t_server_config& server)
{
  out << GREEN << "server " << RESET_COLOR << "{\n";
  out << "  " << GREEN << "host " << RESET_COLOR << server.host << '\n';
  out << "  " << GREEN << "port " << RESET_COLOR << server.port << '\n';
  out << "  " << GREEN << "server_name " << RESET_COLOR << server.server_name << '\n';
  for
  (
    std::map<std::string, std::string>::const_iterator it = server.error_page.begin();
    it != server.error_page.end();
    it++
  )
    out << "  " << GREEN << "error_page " << it->first << RESET_COLOR << ' ' << it->second << '\n';
  for (size_t i = 0; i < server.locations.size(); i++)
    out << MAGENTA << "  id " << RESET_COLOR << i << '\n' << server.locations[i];
  out << "}" << std::endl;

  return ( out );
}

std::ostream& operator<<(std::ostream& out, const t_location_config& location)
{
  out << "  " << MAGENTA << "location " << RESET_COLOR << location.dir << " {\n";
  out << "    " << MAGENTA << "root " << RESET_COLOR << location.root << '\n';
  out << "    " << MAGENTA << "index " << RESET_COLOR << location.index << '\n';
  out << "    " << MAGENTA << "redirect " << RESET_COLOR << location.redirect << '\n';
  out << "    " << MAGENTA << "upload_enabled " << RESET_COLOR << location.upload_enabled << '\n';
  out << "    " << MAGENTA << "upload_dir " << RESET_COLOR << location.upload_dir << '\n';
  out << "    " << MAGENTA << "cgi_enabled " << RESET_COLOR << location.cgi_enabled << '\n';
  out << "    " << MAGENTA << "cgi_path " << RESET_COLOR << location.cgi_path << '\n';
  out << "  }" << std::endl;

  return ( out );
}

const char* ConfigFile::CouldOpenConfigFileException::what () const throw ()
{ return ( "Error: Can't open config file." ); }
