#ifndef UTILS_HPP
#define UTILS_HPP

namespace Utils {
    bool isNumeric(const char *string);
    bool isRegularFile(const char *path);
    char *trim(char *buffer);
    void advanceWhileIsspace(char **ptr);
}

#endif
