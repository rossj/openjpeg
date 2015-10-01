

# UNIX/LINUX similar systems #

## Using cmake (see www.cmake.org) ##

Type:
```
cmake .
make
```

If you are root:
```
make install
make clean
```
else:
```
sudo make install
make clean
```

To build doc (requires 'doxygen' to be found on your system):
(this will create an html directory in TOP\_LEVEL/doc)
```
make doc
```

Binaries are located in the 'bin' directory.

Main available cmake flags:
  * To specify the install path: '-DCMAKE\_INSTALL\_PREFIX=/path'
  * To build the shared libraries and links the executables against it: '-DBUILD\_SHARED\_LIBS:bool=on' (default: 'ON')
> Note: when using this option, static libraries are not built and executables are dynamically linked.
  * To build the CODEC executables: '-DBUILD\_CODEC:bool=on' (default: 'ON')
  * To build the MJ2 executables: '-DBUILD\_MJ2:bool=on' (default: 'OFF')
  * To build the JPWL executables and JPWL library: '-DBUILD\_JPWL:bool=on' (default: 'OFF')
  * To build the JPIP client (java compiler recommended) library and executables: '-DBUILD\_JPIP:bool=on' (default: 'OFF')
  * To build the JPIP server (need fcgi) library and executables: '-DBUILD\_JPIP\_SERVER:bool=on' (default: 'OFF')
  * To enable testing (and automatic result upload to http://my.cdash.org/index.php?project=OPENJPEG):
```
cmake . -DBUILD_TESTING:BOOL=ON -DOPJ_DATA_ROOT:PATH='path/to/the/data/directory' -DBUILDNAME:STRING='name_of_the_build'
make
make Experimental
```
Note : JPEG2000 test files are available with
```
svn checkout http://openjpeg.googlecode.com/svn/data
```
If '-DOPJ\_DATA\_ROOT:PATH' option is omitted, test files will be automatically searched in '${CMAKE\_SOURCE\_DIR}/../data',
corresponding to the location of the data directory when compiling from the trunk (and assuming the data directory has
been checked out of course).

Note 2 : to execute the encoding test suite, kakadu binaries are needed to decode encoded image and compare it to the baseline. Kakadu binaries are freely available for non-commercial purposes at http://www.kakadusoftware.com. kdu\_expand will need to be in your PATH for cmake to find it.

Note 3 : OpenJPEG can be build with BUILD\_THIRDPARTY:BOOL=ON, in which case you need to install some system libraries. On a Debian-like system you can simply do:
```
sudo apt-get install liblcms2-dev  libtiff-dev libpng-dev libz-dev
```
### Using ctest script to perform dashboard submission ###
You can used ctest command to build the openjepg lib and submit to the dashboard.
```
ctest -S mymachine_openjpeg.cmake -V
```

Openjpeg ctest scripts are available with
```
svn checkout http://openjpeg.googlecode.com/svn/dev-utils
```
However you need to specify some variables inside the script, so explore the mymachine\_openjpeg.cmake file and read the comments. Other files expose the way to perform a nightly submission with different platforms and can provide some tips to create a specific script.

# MACOSX #

The same building procedures as above (autotools and cmake) work for MACOSX.
The xcode project file can also be used.

If it does not work, try adding the following flag to the cmake command :
```
-DCMAKE_OSX_ARCHITECTURES:STRING=i386
```

# WINDOWS #

If you're using cygwin or MinGW+MSYS, the same procedures as for Unix can be used.

Otherwise you can use cmake to generate project files for the IDE you are using (VC2010, etc).
Type 'cmake --help' for available generators on your platform.

# Using OpenJPEG #

To use openjpeg exported cmake file, simply create your application doing:

```
$ cat CMakeLists.txt
find_package(OpenJPEG REQUIRED)
include_directories(${OPENJPEG_INCLUDE_DIRS})
add_executable(myapp myapp.c)
target_link_libraries(myapp ${OPENJPEG_LIBRARIES})
```