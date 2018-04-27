#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#define DPKG_RECONFIGURE "/usr/sbin/dpkg-reconfigure"

typedef enum {
    LEVEL_LOW = 1,
    LEVEL_MEDIUM,
    LEVEL_HIGH,
    LEVEL_CRITICAL
} priority_level_t;

extern const std::string g_programVersion;
extern const std::string g_programAuthor;

#endif
