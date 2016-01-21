#include <fstream>
#include <istream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

#include "cc_init.h"
#include "read_esd_file.h"

unique_ptr<istream>
read_esd_file(const string& rel_path) {
  const string path{get_esd_path() + '/' + rel_path};
  unique_ptr<ifstream> ifs{new ifstream{path}};
  if (!ifs->is_open())
    throw runtime_error{string{"can't read file '"} + path + '\''};
  return ifs;
}
