# Introduction #

**LEGACY** This page document the state of openjpeg before release 1.5. And thus does not apply to openjpeg 2.0 and up.

This page describe the situation with build systems in OpenJPEG.

# Details #

Currently OpenJPEG provides two build systems
  * autotools
  * CMake

| | **autotools** | **CMake** |
|:|:--------------|:----------|
| static/shared libs | yes           | yes       |
| build documentation | yes           | yes       |
| build JPIP | yes           | yes       |
| build JPWL | yes           | yes       |
| build MJ2 | yes           | yes       |
| build tests | yes           | yes       |
| system lcms1 | ??            | yes       |
| system lcms2 | ??            | yes       |
| system png | yes           | yes       |
| system tiff | yes           | yes       |
| system zlib | yes           | yes       |
| [regression testing](http://my.cdash.org/index.php?project=OPENJPEG) | no            | yes       |
| export build settings | yes: openjpeg.pc | yes:openjpeg.cmake |