#ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP

# include <cctype>
# include <colors.hpp>
# include <iostream>
# include <fstream>
# include <sstream>
# include <map>
# include <string>
# include <vector>

# ifndef DEBUG
#  define DEBUG false
# endif // DEBUG

# define CONFIG_FILE_MSG "CONFIG"
# define DEFAULT_CONFIG_FILE_INPUT "serv.conf"

typedef struct s_location_config
{
  std::string dir;
  std::string root;
  std::string index;
  std::string redirect;
  std::string upload_enabled;
  std::string upload_dir;
  std::string cgi_enabled;
  std::string cgi_path;
} t_location_config;

typedef struct s_server_config
{
  std::string                         host;
  std::string                         port;
  std::string                         server_name;
  std::map<std::string, std::string>  error_page;
  std::vector<t_location_config>      locations;
} t_server_config;

class ConfigFile
{
  public:
    const size_t  size;

    ConfigFile(const std::string& file);
    ~ConfigFile(void);

    std::vector<t_server_config>    getServers(void) const;
    std::vector<t_location_config>  getLocations(size_t server_id) const;

    t_server_config   getServer(size_t server_id) const;
    t_location_config getLocation(size_t server_id, size_t location_id) const;

    std::string getHost(size_t server_id) const;
    std::string getPort(size_t server_id) const;
    std::string getServerName(size_t server_id) const;
    std::string getErrorPage(size_t server_id, unsigned short page) const;

    std::string getLocationDir(size_t server_id, size_t location_id) const;
    std::string getLocationRoot(size_t server_id, size_t location_id) const;
    std::string getLocationIndex(size_t server_id, size_t location_id) const;
    std::string getLocationRedirect(size_t server_id, size_t location_id) const;
    std::string getLocationUploadEnabled(size_t server_id, size_t location_id) const;
    std::string getLocationUploadDir(size_t server_id, size_t location_id) const;
    std::string getLocationCgiEnabled(size_t server_id, size_t location_id) const;
    std::string getLocationCgiPath(size_t server_id, size_t location_id) const;

    class CouldOpenConfigFileException;

  private:
    std::vector<t_server_config> _servers;
};

std::ostream& operator<<(std::ostream& out, const ConfigFile& config_file);
std::ostream& operator<<(std::ostream& out, const std::vector<t_server_config>& servers);
std::ostream& operator<<(std::ostream& out, const t_server_config& server);
std::ostream& operator<<(std::ostream& out, const t_location_config& location);

class ConfigFile::CouldOpenConfigFileException : public std::exception
{ public: const char* what() const throw(); };

# include <ConfigFile.ipp>

#endif //CONFIGFILE_HPP
