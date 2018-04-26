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

#ifndef COLORS_HPP
#define COLORS_HPP

#include <string>

class Colors {
private:
    std::string boldCyan;
    std::string boldGreen;
    std::string boldRed;
    std::string boldWhite;
    std::string cyan;
    std::string green;
    std::string normal;
    std::string red;
    std::string white;

public:
    Colors() {
	boldCyan  = "\033[1;36m";
	boldGreen = "\033[1;32m";
	boldRed   = "\033[1;31m";
	boldWhite = "\033[1;37m";
	cyan      = "\033[2m\033[36m";
	green     = "\033[2m\033[32m";
	normal    = "\033[0m";
	red       = "\033[2m\033[31m";
	white     = "\033[2m\033[37m";
    }

    const std::string getBoldCyan(void) {
	return boldCyan;
    }
    const std::string getBoldGreen(void) {
	return boldGreen;
    }
    const std::string getBoldRed(void) {
	return boldRed;
    }
    const std::string getBoldWhite(void) {
	return boldWhite;
    }
    const std::string getCyan(void) {
	return cyan;
    }
    const std::string getGreen(void) {
	return green;
    }
    const std::string getNormal(void) {
	return normal;
    }
    const std::string getRed(void) {
	return red;
    }
    const std::string getWhite(void) {
	return white;
    }
};

#endif
