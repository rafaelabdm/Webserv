# include <ConfigFile.hpp>

static void debugMessage
(
  const std::string& action,
  const std::string& message,
  const std::string& color
)
{
  if(DEBUG)
    std::cout
      << "[ " << color << action <<  RESET_COLOR " ] "
      << message << std::endl;

  return;
}

static void initData(ConfigFile& obj, const std::string& file)
{
  obj.setFile(file);

  return;
}

ConfigFile::ConfigFile(void)
{
  debugMessage(CONFIG_FILE_MSG, "ConfigFile's Default constructor called", BLUE);

  initData(*this, DEFAULT_CONFIG_FILE_INPUT);

  return;
}

ConfigFile::ConfigFile(const std::string& file)
{
  debugMessage(CONFIG_FILE_MSG, "ConfigFile's File constructor called", BLUE);

  initData(*this, file);

  return;
}

ConfigFile::ConfigFile(const ConfigFile& obj)
{
  debugMessage(CONFIG_FILE_MSG, "ConfigFile's Copy constructor called", BLUE);

  if(this != &obj)
    *this = obj;

  return;
}

ConfigFile::~ConfigFile(void)
{
  debugMessage(CONFIG_FILE_MSG, "ConfigFile's destructor called", BLUE);

  return;
}

std::string ConfigFile::getFile(void) const
{ return ( this->_file ); }

void ConfigFile::setFile(const std::string& file)
{
  this->_file = file;

  return;
}

ConfigFile& ConfigFile::operator=(const ConfigFile& obj)
{
  if (this != &obj)
    this->_file = obj.getFile ();

  return ( *this );
}

std::ostream& operator<<(std::ostream& out, const ConfigFile& obj)
{
  out << "config file: " << obj.getFile ();

  return ( out );
}

const char* ConfigFile::CantOpenConfigFileException::what () const throw ()
{ return ( "Error: Can't open config file." ); }