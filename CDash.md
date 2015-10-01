# Introduction #

Thanks to the use of CMake, OpenJPEG can be nightly tested. Simply configure, build and test OpenJPEG:
```
cmake . && make && make test
```
if you would like to submit the test to the dashboard:
```
make Experimental
```

# Details #

Configuration possibilities:

| Name | OpenJPEG Version | Description |
|:-----|:-----------------|:------------|
| Nightly Expected | trunk            | Registered machine only, see [ctest\_scripts](http://code.google.com/p/openjpeg/source/browse/#svn%2Fdev-utils%2Fctest_scripts) |
| Nightly Release 1.5 | 1.5              |Registered machine only, see [ctest\_scripts](http://code.google.com/p/openjpeg/source/browse/#svn%2Fdev-utils%2Fctest_scripts) |
| Nightly Release 2.0 | 2.0              | Registered machine only, see [ctest\_scripts](http://code.google.com/p/openjpeg/source/browse/#svn%2Fdev-utils%2Fctest_scripts) |
| Nightly | ??               | Default for `make Nightly`. Can be trunk, v2, v1.5 |
| Continuous | ??               | Compilation during the day on fixed time interval |
| Experimental | ??               | eg. new compiler, new arch, new OS |

## Current configuration tested ##

### 1.5 ###

### trunk ###

# Target Systems #

## OS ##

  * Windows 7 32bits and 64 bits intel
  * Linux 32 bits and 64 bits intel
  * Linux 32 bits PPC
  * MacOSX 10.4 and above

## Compilers ##

  * GNU GCC 4.x
  * clang 3.x
  * Visual Studio 2005, 2008, 2010 (x86 & x86\_64)

# Links #

Link is here:
