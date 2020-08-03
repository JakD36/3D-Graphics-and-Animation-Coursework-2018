//
// Created by Jack Davidson on 14/06/2020.
//

#include <sys/stat.h>
#include "Resource.h"

Resource::Resource(std::string filepath)
{
    m_key = filepath;
    struct stat buf;
    stat(filepath.c_str(),&buf);
    m_lastModified = buf.st_mtime;
    m_count = 0;
}