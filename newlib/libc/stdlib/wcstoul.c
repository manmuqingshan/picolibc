/*
FUNCTION
	<<wcstoul>>, <<wcstoul_l>>---wide string to unsigned long

INDEX
	wcstoul

INDEX
	wcstoul_l

INDEX
	_wcstoul_r

SYNOPSIS
	#include <wchar.h>
        unsigned long wcstoul(const wchar_t *__restrict <[s]>,
			      wchar_t **__restrict <[ptr]>, int <[base]>);

	#include <wchar.h>
        unsigned long wcstoul_l(const wchar_t *__restrict <[s]>,
				wchar_t **__restrict <[ptr]>, int <[base]>,
				locale_t <[locale]>);

        unsigned long _wcstoul_r(void *<[reent]>, const wchar_t *<[s]>,
				 wchar_t **<[ptr]>, int <[base]>);

DESCRIPTION
The function <<wcstoul>> converts the wide string <<*<[s]>>> to
an <<unsigned long>>. First, it breaks down the string into three parts:
leading whitespace, which is ignored; a subject string consisting
of the digits meaningful in the radix specified by <[base]>
(for example, <<0>> through <<7>> if the value of <[base]> is 8);
and a trailing portion consisting of one or more unparseable characters,
which always includes the terminating null character. Then, it attempts
to convert the subject string into an unsigned long integer, and returns the
result.

If the value of <[base]> is zero, the subject string is expected to look
like a normal C integer constant (save that no optional sign is permitted):
a possible <<0x>> indicating hexadecimal radix, and a number.
If <[base]> is between 2 and 36, the expected form of the subject is a
sequence of digits (which may include letters, depending on the
base) representing an integer in the radix specified by <[base]>.
The letters <<a>>--<<z>> (or <<A>>--<<Z>>) are used as digits valued from
10 to 35. If <[base]> is 16, a leading <<0x>> is permitted.

The subject sequence is the longest initial sequence of the input
string that has the expected form, starting with the first
non-whitespace character.  If the string is empty or consists entirely
of whitespace, or if the first non-whitespace character is not a
permissible digit, the subject string is empty.

If the subject string is acceptable, and the value of <[base]> is zero,
<<wcstoul>> attempts to determine the radix from the input string. A
string with a leading <<0x>> is treated as a hexadecimal value; a string with
a leading <<0>> and no <<x>> is treated as octal; all other strings are
treated as decimal. If <[base]> is between 2 and 36, it is used as the
conversion radix, as described above. Finally, a pointer to the first
character past the converted subject string is stored in <[ptr]>, if
<[ptr]> is not <<NULL>>.

If the subject string is empty (that is, if <<*>><[s]> does not start
with a substring in acceptable form), no conversion
is performed and the value of <[s]> is stored in <[ptr]> (if <[ptr]> is
not <<NULL>>).

The alternate function <<_wcstoul_r>> is a reentrant version.  The
extra argument <[reent]> is a pointer to a reentrancy structure.


<<wcstoul_l>> is like <<wcstoul>> but performs the conversion based on the
locale specified by the locale object locale.  If <[locale]> is
LC_GLOBAL_LOCALE or not a valid locale object, the behaviour is undefined.

RETURNS
<<wcstoul>>, <<wcstoul_l>> return the converted value, if any. If no
conversion was made, <<0>> is returned.

<<wcstoul>>, <<wcstoul_l>> return <<ULONG_MAX>> if the magnitude of the
converted value is too large, and sets <<errno>> to <<ERANGE>>.

PORTABILITY
<<wcstoul>> is ANSI.
<<wcstoul_l>> is a GNU extension.

<<wcstoul>> requires no supporting OS subroutines.
*/

/*
 * Copyright (c) 1990 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#define _GNU_SOURCE
#include <limits.h>
#include <wctype.h>
#include <wchar.h>
#include <errno.h>
#include <stdlib.h>
#include "local.h"

/*
 * Convert a wide string to an unsigned long integer.
 */

unsigned long
wcstoul_l (const wchar_t *nptr, wchar_t **endptr,
	    int base, locale_t loc)
{
	register const wchar_t *s = nptr;
	register unsigned long acc;
	register wchar_t c;
	register unsigned long cutoff;
	register int neg = 0, any, cutlim;

        /* Check for invalid base value */
        if ((unsigned) base > 36 || base == 1) {
                errno = EINVAL;
                if (endptr)
                        *endptr = (wchar_t *) nptr;
                return 0;
        }
	/*
	 * See strtol for comments as to the logic used.
	 */
	do {
		c = *s++;
	} while (iswspace_l(c, loc));
	if (c == L'-') {
		neg = 1;
		c = *s++;
	} else if (c == L'+')
		c = *s++;
	if ((base == 0 || base == 16) &&
	    c == L'0' && (*s == L'x' || *s == L'X')) {
		c = s[1];
                nptr = s;
		s += 2;
		base = 16;
	}
	if (base == 0)
		base = c == L'0' ? 8 : 10;
	cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
	cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
	for (acc = 0, any = 0;; c = *s++) {
		if (c >= L'0' && c <= L'9')
			c -= L'0';
		else if (c >= L'A' && c <= L'Z')
			c -= L'A' - 10;
		else if (c >= L'a' && c <= L'z')
			c -= L'a' - 10;
		else
			break;
		if ((int) c >= base)
			break;
                if (any < 0 || acc > cutoff || (acc == cutoff && (int) c > cutlim))
			any = -1;
		else {
			any = 1;
			acc *= base;
			acc += (unsigned long) c;
		}
	}
	if (any < 0) {
		acc = ULONG_MAX;
		errno = ERANGE;
	} else if (neg)
		acc = -acc;
	if (endptr != 0)
		*endptr = (wchar_t *) (any ? s - 1 : nptr);
	return (acc);
}

unsigned long
wcstoul (const wchar_t *__restrict s,
	wchar_t **__restrict ptr,
	int base)
{
	return wcstoul_l (s, ptr, base, __get_current_locale ());
}
