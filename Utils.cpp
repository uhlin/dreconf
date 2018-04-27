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

#include <sys/stat.h>

#include <cctype>
#include <cstring>
#include <stdexcept>

#include "Utils.hpp"

bool
Utils::isNumeric(const char *string)
{
    if (string == NULL || *string == '\0')
	return false;

    for (const char *p = &string[0]; *p != '\0'; p++) {
	if (!isdigit(*p))
	    return false;
    }

    return true;
}

bool
Utils::isRegularFile(const char *path)
{
    struct stat sb;

    if (path == NULL || *path == '\0')
	return false;

    return (stat(path, &sb) == 0 && (sb.st_mode & S_IFMT) == S_IFREG);
}

char *
Utils::trim(char *buffer)
{
    char *p = NULL;
    size_t size = 0;

    if (buffer == NULL)
	throw std::invalid_argument("null buffer");
    else if (*buffer == '\0')
	return buffer;
    else
	size = strlen(buffer);
    for (p = &buffer[size - 1]; p >= &buffer[0]; p--) {
	if (!isspace(*p))
	    break;
    }
    *(p + 1) = '\0';
    return buffer;
}

void
Utils::advanceWhileIsspace(char **ptr)
{
    while (isspace(**ptr))
	(*ptr)++;
}
