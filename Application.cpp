/* Copyright (c) 2018 Markus Uhlin <markus.uhlin@bredband.net>
   All rights reserved.

   Permission to use, copy, modify, and distribute this software for any
   purpose with or without fee is hereby granted, provided that the above
   copyright notice and this permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
   AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
   DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
   PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
   TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
   PERFORMANCE OF THIS SOFTWARE. */

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fstream>
#include <iostream>

#include "Application.hpp"
#include "Colors.hpp"
#include "Utils.hpp"

const std::string g_programVersion = "1.0";
const std::string g_programAuthor = "Markus Uhlin";

static void
usage(const char *exe)
{
    Colors colors;

    const std::string greeting = "dreconf "
	+ g_programVersion
	+ " by "
	+ g_programAuthor;
    const std::string border(greeting.size(), '-');

    std::cerr
	<< border << "\n"
	<< colors.getBoldCyan() << greeting << colors.getNormal() << "\n"
	<< border << "\n";

    std::cerr
	<< "Usage: "
	<< colors.getBoldWhite() << exe << colors.getNormal()
	<< " <File> <Priority Level>\n\n";

    std::cerr
	<< "<File> should contain a list of Debian packages which are\n"
	<< "installed on the system. Preferably one package per line. To\n"
	<< "generate a such file, try:\n"
	<< "\tdpkg --get-selections | awk '{print $1}' | less\n"
	<< "\t(Press 's' to save it)\n"
	<< "\n"
	<< "Leading and trailing whitespace characters are ignored in\n"
	<< "<File>, and lines preceded by '#' are interpreted as\n"
	<< "comments.\n"
	<< "\n"
	<< "<Priority Level> can be either:\n"
	<< "\t1) Low\n"
	<< "\t2) Medium\n"
	<< "\t3) High\n"
	<< "\t4) Critical\n"
	<< "(Use the numbers to refer to the levels.)\n";

    exit(1);
}

static bool
setCommand(char *buf, const size_t sz, const char *priority, const char *pkg)
{
    const int ret = snprintf(buf, sz, "%s --priority=%s %s",
	DPKG_RECONFIGURE, priority, pkg);

    return (ret == -1 || ((size_t) ret) >= sz ? false : true);
}

static void
debianReconfigurePackage(const char *pkg, priority_level_t lvl)
{
    char cmd[2048] = "";

    switch (lvl) {
    case LEVEL_LOW:
	if (!setCommand(cmd, sizeof cmd, "low", pkg))
	    std::cerr << "setCommand: error\n";
	break;
    case LEVEL_MEDIUM:
	if (!setCommand(cmd, sizeof cmd, "medium", pkg))
	    std::cerr << "setCommand: error\n";
	break;
    case LEVEL_HIGH:
	if (!setCommand(cmd, sizeof cmd, "high", pkg))
	    std::cerr << "setCommand: error\n";
	break;
    case LEVEL_CRITICAL:
	if (!setCommand(cmd, sizeof cmd, "critical", pkg))
	    std::cerr << "setCommand: error\n";
	break;
    }

    if (cmd[0] && system(cmd) == -1) {
	perror("system");
	abort();
    }
}

int
main(int argc, char *argv[])
{
    if (argc != 3) {
	usage(argv[0]);
	/* NOTREACHED */
    }

    char *file = NULL;
    long int pLev = -1;

    if (!Utils::isRegularFile(argv[1])) {
	std::cerr << "File doesn't exist or isn't a regular file\n";
	return 1;
    } else if (!Utils::isNumeric(argv[2])) {
	std::cerr << "Priority level not a number\n";
	return 1;
    } else if ((file = strdup(argv[1])) == NULL) {
	perror("strdup");
	return 1;
    }

    errno = 0;
    pLev = strtol(argv[2], NULL, 10);

    if (errno) {
	perror("strtol");
	return 1;
    } else if (pLev < LEVEL_LOW || pLev > LEVEL_CRITICAL) {
	std::cerr << "Priority level out of range\n";
	return 1;
    }

    std::ifstream pkgList;

    pkgList.open(file, std::ifstream::in);

    if (!pkgList.is_open()) {
	std::cerr << "Failed to open file\n";
	return 1;
    }

    free(file);
    file = NULL;

    char buf[2048] = { '\0' };
    char *bufptr = NULL;

    while (pkgList.getline(buf, sizeof buf)) {
	bufptr = &buf[0];
	Utils::advanceWhileIsspace(&bufptr);
	if (*bufptr == '\0' || *bufptr == '#')
	    continue;
	try {
	    Utils::trim(bufptr);
	} catch (...) {
	    std::cerr << "trim error\n";
	    return 1;
	}
	debianReconfigurePackage(bufptr, (priority_level_t) pLev);
    }

    if (pkgList.eof()) {
	/* good */
	pkgList.close();
    } else if (pkgList.bad()) {
	std::cerr << "Failed to read the package list: badbit set\n";
	return 1;
    } else {
	std::cerr << "Failed to read the package list: unknown error\n";
	return 1;
    }

    Colors colors;

    std::cout
	<< "- " << colors.getBoldGreen() << "Done" << colors.getNormal() << " -"
	<< std::endl;

    return 0;
}
