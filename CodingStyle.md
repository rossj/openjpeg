# C #

## FAQ ##

```
  Q: Does OpenJPEG requires C99 compiler ?
  A: No
```
```
  Q: Are you sure OpenJPEG does not requires C99 compiler, because I see stdint.h in the source code
  A: Yes !
```
## Description ##
OpenJPEG is meant to be portable. OpenJPEG should only requires ANSI C (C89) compilers.

## Exceptions ##

Instead of re-inventing the wheel, OpenJPEG will use C99 notations in two occasions:
  * fixed-type notation
  * large file support

OpenJPEG uses a single build-system: cmake. It support system inspection and compiler detection. What happen is that:
  * iff compiler provide a stdint.h we will use it
  * iff compiler provide large file support we will use it

So in summary:
  * if your compiler does not provide a stdint.h we will emulate it using compiler private extension
  * if your compiler does not support Large File Support, you will not have support for LFS in OpenJPEG

Note: since we use type from stdint.h we will use the C99 notation PRIi64, PRIu64 & PRIx64 for printing the fixed 64 bits type. Again this is not a requirement on your compiler, we will use your compiler private extension as replacement if PRI?64 is not present.

# Code Formating #

## Portability ##

File should be pushed to server with UNIX eol

## Tabs ##

You should not use tab char, but instead use two white space. See uncrustify example:
  * http://code.google.com/p/openjpeg/source/browse/dev-utils/scripts/opj.cfg

To see it in action:

  * http://code.google.com/p/openjpeg/source/browse/dev-utils/scripts/j2k.c
  * http://code.google.com/p/openjpeg/source/browse/dev-utils/scripts/tcd.c

## Comment ##

Because OpenJPEG is written in C. One should use C style comment: `/*` and `*/`

For doxygen, one should use `/**` and `*/`

## Charset ##

  * What charset to use for unicode ? None !
  * C does not support anything other than ASCII
  * Eg: "Università" in comment should be "Universita'"
  * and "Université" in comment should be "Universite"

# Open Questions #

  * tab spaces ? indent ? uncrutify rule ?
  * file type (UNIX eol would be nice)


# Useful commands to clean style of cmake part #
## Convert CMake-language commands to lower case (Thanks to Hans Johnson) ##
NOTE: MUST USE GNU compliant version of sed
Run the following shell code (Modified from Brad King, and used on CMake source code):
\#!/bin/bash
cmake --help-command-list \
| grep -v "cmake version" \
| while read c; do
> echo 's/\b'"$(echo $c | tr '[:lower:]' '[:upper:]')"'\(\s**\)(/'"$c"'\1(/g'
> done >convert.sed \
&& git ls-files -z -- bootstrap '**.cmake' '**.cmake.in' '**CMakeLists.txt' \
> > | fgrep -v thirdparty \
> > | xargs -0 gsed -i -f convert.sed \
&& rm convert.sed

## Remove CMake-language block-end command arguments  (Thanks to Hans Johnson) ##
NOTE: MUST USE GNU compliant version of sed
Run the following shell code:

for c in else endif endforeach endfunction endmacro endwhile; do

> echo 's/\b'"$c"'\(\s**\)(.\+)/'"$c"'\1()/'
done >convert.sed \
&& git ls-files -z -- bootstrap '**.cmake' '**.cmake.in' '**CMakeLists.txt' \
> | xargs -0 gsed -i -f convert.sed \
&& rm convert.sed