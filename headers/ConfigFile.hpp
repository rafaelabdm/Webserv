#ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP

# include <colors.hpp>

# ifndef DEBUG
#  define DEBUG false
# endif // DEBUG

# define CONFIG_FILE_MSG	"CONFIG"
# define DEFAULT_CONFIG_FILE_INPUT	"serv.conf"

class ConfigFile
{
  public:
    ConfigFile(void);
    ConfigFile(const std::string& file);
    ConfigFile(const ConfigFile& obj);
    ~ConfigFile(void);

    std::string getFile(void) const;
    void setFile(const std::string& file);

    ConfigFile& operator=(const ConfigFile& obj);

    class CantOpenConfigFileException;

  private:
    std::string _file;
};

std::ostream& operator<<(std::ostream& out, const ConfigFile& obj);

class ConfigFile::CantOpenConfigFileException : public std::exception
{ public: const char* what() const throw(); };

# include <ConfigFile.ipp>

#endif //CONFIGFILE_HPP
