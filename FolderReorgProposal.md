

# New names for libraries and executables #

In order to make the openjpeg project libraries and executables more consistent, we plan to rename some of them. The current proposal is the following (italic indicate optional dependencies).

## Libraries ##

| **name** | **description** | **dependencies** | **remarks** |
|:---------|:----------------|:-----------------|:------------|
| libopenjpeg -> libopenjp2 | basic J2K/JP2 library | none             | Rename to "libopenjp2k" to disambiguate from JPEG format ? or is it too late ? MM: I do not like 'jp2k' since we either talk about j2k or jp2... |
| libopenjpwl (broken??) | basic J2K/JP2 library with JPWL capabilities | none             |             |
| libopenjpip | JPIP library    | libopenjpeg      |             |
| libopenjp3d | JP3D library    | none             |             |
| libopenjpegjni | OpenJPEG Java binding | libopenjpeg      |             |

### Library Symbols ###

Goals: When implementing the JPEG 2000 standard using OpenJPEG API, it should be possible to re-use as much code as possible.

Implementation details:
When implementing any parts after Part 2, it should be possible to link to openjp2. For instance in the case of JPIP, to prevent code duplication, we had to re-use all the cio`*` & function\_list`*` functionalities. Furthermore another low level change had to be done:

http://code.google.com/p/openjpeg/source/diff?spec=svn2067&r=2067&format=side&path=/trunk/src/lib/openjp2/jp2.h

> See line 211 ('Point location for split...') just
above 'jpip\_iptr\_offset'.

  1. It seems to me (MM) that this is a desirable goals to maintain a clean separation in between all the Parts of JPEG 2000. Multiples reasons: maintenance, clean design, separation...
  1. It seems for other dev (MSD) that it is potential harmful to expose low level functionalities such as cio`*` and as such it would be better to move back anything related to file writing (JPIP extention) back into the OPENJP2 folder.

How do we solve both (1) and (2) ? Possible solutions:

  1. We do not install cio.h. This means people would have to guess the types used by cio`*` functions. This would clearly indicate this is a private API.
  1. document them as being implementation details functions.
  1. Another more complex solution would be something like this:
```
$ cat CMakeLists.txt
add_library(libCore STATIC internal.c)
add_library(libA SHARED a.c)
target_link_libraries(libA LINK_PRIVATE libCore)
add_library(libB SHARED b.c)
target_link_libraries(libB LINK_PUBLIC libA LINK_PRIVATE libCore)
install(TARGETS libA libB
  EXPORT myexport
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
)
install(EXPORT myexport DESTINATION share)
#set_target_properties(libA PROPERTIES
#  PRIVATE_HEADER "internal.h"
#)
```

All the above possible solutions, are brute-force solutions. Another way at solving (1) & (2) would be to go over the **exact** API that poses issues and maybe extend openjp2 to provide a clean API that is easy to maintain while provide the same functionalities (or better) and help reduce code redundancy with openjpip.

## Executables ##

| **name** | **description** | **dependencies** | **remarks** |
|:---------|:----------------|:-----------------|:------------|
| opj\_compress | was: image\_to\_j2k | libopenjpeg, _libtiff_, _libpng_, _liblcms_ |             |
| opj\_decompress | was: j2k\_to\_image | libopenjpeg, _libtiff_, _libpng_, _liblcms_ |             |
| opj\_dump | was: j2k\_dump  | libopenjpeg, _libtiff_, _libpng_, _liblcms_ |             |
| opj\_jpwl\_compress | was: JPWL\_image\_to\_j2k | libopenjpwl, _libtiff_, _libpng_, _liblcms_ |             |
| opj\_jpwl\_decompress | was: JPWL\_j2k\_to\_image | libopenjpwl, _libtiff_, _libpng_, _liblcms_ |             |
| opj\_server | JPIP server     | libopenjpeg, libopenjpip\_server, libfastcgi |             |
| opj\_dec\_server | JPIP decoding server | libopenjpeg, libopenjpip\_local |             |
| opj\_jpip\_viewer | was: opj\_viewer ; JAVA JPIP viewer | none             | technically there are actually two viewers: opj\_viewer and opj\_xerces\_viewer, this is confusing for user, we should build one and only one depending whether or not user wants xerces (and found on system). |
| opj\_viewer | was: OPJviewer ; JAVA viewer | libopenjpeg      | should be merged with opj\_jpip\_viewer|
| opj\_mj2\_compress | was: frames\_to\_mj2 | libopenjpeg      | currently, it does not use the openjpeg API correctly |
| opj\_mj2\_decompress | was: mj2\_to\_frames | libopenjpeg      | currently, it does not use the openjpeg API correctly |
| opj\_mj2\_extract | was: extract\_j2k\_from\_mj2 | libopenjpeg      | currently, it does not use the openjpeg API correctly |
| opj\_mj2\_wrap | was: wrap\_j2k\_in\_mj2 | libopenjpeg      | currently, it does not use the openjpeg API correctly |
| opj\_jpip\_test\_jp2 | was: test\_index | libopenjpeg      |             |
| opj\_addxml?dont like the name! | was: addXMLinJP2 | libopenjpeg      |             |
| opj\_jpip\_transcode  | was: jpip\_to\_j2k | libopenjpeg      |             |
| opj\_jpip\_transcode | was: jpip\_to\_jp2 | libopenjpeg      |             |
| opj\_jp3d\_decompress | was: jp3d\_to\_volume | libopenjp3d      |             |
| opj\_jp3d\_compress | was:  volume\_to\_jp3d| libopenjp3d      |             |
| opj\_jpip\_compress | was: image\_to\_j2k -jpip | libopenjpip      |             |

## Java binding ##

The openjpeg.jar will remain called 'openjpeg.jar' it is meant to provide the full OpenJPEG API. This means that the openjpeg.jar will load the individual components (openjp2, openjp3d...).

## Single Build System ##

See:
  * http://groups.google.com/group/openjpeg/msg/9e83d9075ec07823

# New directory structure #

A new directory structure is also proposed for the svn repository. Based on Vincent Torri suggestion+Addition from Mathieu Malaterre, here is the current proposal :

  * openjpeg
    * src/  (where the code for the libraries are located)
      * lib/ (where the code of libraries are located)
        * openjp2/
        * openjpip/
        * openjpwl/
        * openjp3d/
      * bin/ (where the code of binaries are located)
        * common/ [opj\_dump, ...]
        * jp2/ [opj\_compress, opj\_decompress]
        * jpwl [opj\_jpwl\_compress, opj\_jpwl\_decompress]
        * mj2 [opj\_mj2\_compress, opj\_mj2\_decompress, opj\_mj2\_extract, opj\_mj2\_wrap]
        * jpip [opj\_server, opj\_dec\_server]
          * java/ [opj\_jpip\_viewer](opj_jpip_viewer.md)
        * wx
          * opj\_viewer/ [need C++ compiler](will.md)
        * jp3d
          * tcltk/ [need tcl/tk interpreter](will.md)
    * cmake/
    * doc/
    * tests/
      * apps/
      * src/
    * wrapping/
      * java/
    * thirdparty/

Remaining questions :
  * Where do we put the code of thirdparty libraries, as only executables depend on them ?
  * Another proposal is to create different projects : openjpeg, openjpip, openjp3d, each with its 'branches', 'trunk' and 'tags' folders. Good idea ?