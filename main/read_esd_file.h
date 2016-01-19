#ifndef READ_TEXT_FILE_H
#define READ_TEXT_FILE_H

#include <istream>
#include <memory>
#include <string>

std::unique_ptr<std::istream> read_esd_file(const std::string &rel_path);

#endif
