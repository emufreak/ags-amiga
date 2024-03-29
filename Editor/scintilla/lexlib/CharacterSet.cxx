// Scintilla source code edit control
/** @file CharacterSet.cxx
 ** Simple case functions for ASCII.
 ** Lexer infrastructure.
 **/
// Copyright 1998-2010 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <cstdlib>
#include <cassert>

#include "CharacterSet.h"

using namespace Scintilla;

namespace Scintilla {

int CompareCaseInsensitive(const char *a, const char *b) noexcept {
	while (*a && *b) {
		if (*a != *b) {
			const char lowerA = MakeLowerCase(*a);
			const char lowerB = MakeLowerCase(*b);
			if (lowerA != lowerB)
				return lowerA - lowerB;
		}
		a++;
		b++;
	}
	// Either *a or *b is nul
	return *a - *b;
}

int CompareNCaseInsensitive(const char *a, const char *b, size_t len) noexcept {
	while (*a && *b && len) {
		if (*a != *b) {
			const char lowerA = MakeLowerCase(*a);
			const char lowerB = MakeLowerCase(*b);
			if (lowerA != lowerB)
				return lowerA - lowerB;
		}
		a++;
		b++;
		len--;
	}
	if (len == 0)
		return 0;
	else
		// Either *a or *b is nul
		return *a - *b;
}

}
