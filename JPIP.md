
---

Written by:
Kaori Hagihara
UCL/SST/ICTM/ELEN
February 18 2011



---


# Introduction #

OpenJPIP software is an implementation of JPEG 2000 Part9: Interactivity tools, APIs and protocols (JPIP).
( For more info about JPIP, check the website: http://www.jpeg.org/jpeg2000/j2kpart9.html)
The current implementation uses some results from the 2KAN project (http://www.2kan.org).

First Version 2.0 covers:
  * JPT-stream (Tile based) and JPP-stream (Precinct based) media types
  * Session, channels, cache model managements
  * JPIP over HTTP
  * Indexing JPEG 2000 files
  * Embedding XML formatted metadata
  * Region Of Interest (ROI) requests

# License #

This software is released under the BSD license, anybody can use or modify the library, even for commercial applications.
The only restriction is to retain the copyright in the sources or the binaries documentation.
Neither the author, nor the university accept any responsibility for any kind of error or data loss which may occur during usage.

# System requirements #

  * OpenJPEG library (currently assumes it is installed on the system => will not use the one built higher in the directory structure)
  * FastCGI development kit (C libraries) at server (http://www.fastcgi.com)
  * Java application launcher at client
  * (Optional) Xerces2 java XML parser on the client for accessing embedded image metadata (http://xerces.apache.org/xerces2-j)

We tested this software with a virtual server running on the same Linux machine as the clients. Currently, it works only on linux or macosx platforms, windows version should come later.

# Building instructions #

JPIP utilities are built through cmake and autotools procedures described in the [Installation](http://code.google.com/p/openjpeg/wiki/Installation) page. Use '-DBUILD\_JPIP=on' and '--enable-jpip' respectively.

To build JPIP utilities apart from the openjpeg project, a Makefile.nix is available in the same directory as this README file. Simply type 'make -f Makefile.nix' and it will build all the required C-executables.
Concerning the java-based opj\_viewer, simply type 'ant' in the corresponding directory (requires 'ant' utility of course)

The documentation can be build this way (requires doxygen utility):
```
  cd doc
  doxygen Doxyfile
```

# Usage #

## Preliminary notes ##
  * HTML documentation is available at http://www.openjpeg.org/jpip/doc/html
  * Example image is available at http://www.openjpeg.org/jpip/data/copenhague1.zip (Gray), http://www.openjpeg.org/jpip/data/16.jp2 (Color)

## Webserver ##
> You need a webserver running with the fastcgi module enabled and correctly configured.
> For Apache, add the following line to your /etc/apache2/mods-available/fastcgi.conf configuration file:

```
  FastCGIExternalServer /var/www/myFCGI -host localhost:3000
```

> where /var/www is your DocumentRoot.
> Please refer to 'http://www.openjpeg.org/jpip/doc/ApacheFastCGITutorial.pdf' for more details.

## Server ##
  1. Store JP2 files in the same directory as opj\_server
  1. Launch opj\_server from the server terminal:
```
  % spawn-fcgi -f ./opj_server -p 3000 -n
```

> For shutting down JPIP server:
```
     %GET http://hostname/myFCGI?quitJPIP
```
    1. Notice, http://hostname/myFCGI is the HTTP server URI (myFCGI refers to opj\_server by the server setting)
    1. Request message "quitJPIP" can be changed in Makefile, modify ` -DQUIT_SIGNAL=\"quitJPIP\" `

## Client ##
  * Launch image decoding server, and keep it alive as long as image viewers are open
```
  % ./opj_dec_server
```
> You might prefer to implement this program from another directory since cache files are saved in the working directory.
```
  % mkdir cache
  % cd cache
  % ../opj_dec_server
```
  * Open image viewers (as many as needed)
```
  % java -jar opj_viewer.jar http://hostname/myFCGI JP2_filename.jp2 [stateless/session] [jptstream/jppstream]
```
> The arguments
    * http://hostname/myFCGI is the HTTP server URI (myFCGI refers to opj\_server by the server setting)
    * JP2\_filename.jp2 is the name of a JP2 file available on the server.
    * Request type, stateless for no caching, session (default) for caching
    * Return media type, JPT-stream tile based stream, or JPP-stream (default) precinct based stream
> Image viewer GUI instructions
    * Scale up request: Enlarge the window
    * ROI request:      Select a region by mouse click and drag, then click inside the red frame of the selected region
    * If Xerces2 is installed
      * Annotate image with ROI information in XML metadata: Click button "Region Of Interest"
      * Open a new window presenting an aligned image with a locally stored image: Click button "Image Registration" (Under Construction)
  * Quit the image decoding server through the telnet, be sure all image viewers are closed
```
  % telnet localhost 5000
  quit
```

# JP2 encoding instructions #

An example to encode a TIF image "copenhague1.tif" at resolution 4780x4050, 8bit/pixel, grayscale.
```
  % ./image_to_j2k -i copenhague1.tif -o copenhague1.jp2 -p RPCL -c [64,64] -t 640,480 -jpip -TP R
```
> Note:
    * -jpip Embed index table box into the output JP2 file (compulsory for JPIP)
    * -TP R  Partition a tile into tile parts of different resolution levels (compulsory for JPT-stream)

**Warning**: -jpip option is really important it adds the cidx/fidx superbox to the file. Without this information, openjpip server will simply crash on your input file. Make sure all file accessible from within openjpip server have cidx/fidx superbox. At the time of writing, kakadu does not support generating cidx/fidx superbox

  * [Annex I Indexing JPEG 2000 files for JPIP, p90](http://www.jpeg.org/public/fcd15444-9v2.pdf)


(Optional) Embed metadata into JP2 file
```
  % ./addXMLinJP2 copenhague1.jp2 copenhague1.xml
```
Input metadata file "copenhague1.xml" looks like:
```
    <xmlbox>
      <roi name="island" x="1890" y="1950" w="770" h="310"/>
      <roi name="ship" x="750" y="330" w="100" h="60"/>
      <roi name="airport" x="650" y="1800" w="650" h="800"/>
      <roi name="harbor" x="4200" y="1650" w="130" h="130"/>
      <irt refimg="name1.jp2" m1="0.50" m2="-0.50" m3="0" m4="0.80" m5="-0.80" m6="0" m7="500" m8="1000" m9="0"/>
    </xmlbox>
```

# Roadmap: JPIP todo's #
  * Implement DICOM integration: goal is to have the openjpeg JPIP capabilities usable by the GDCM library
  * ~~Merge Lucian's work from GSoC with current openjpip version~~
  * ~~Target-ID handling~~
  * ~~Enabling multiple quality layer support~~
  * ~~Enabling other progression orders than RPCL~~
  * ~~Update opj\_viewer to be able to use JPP-stream~~
  * ~~Replace current index creation with the one provided by he openjpeg library itself.~~
  * Develop a transcoder utility that processes existing JPEG 2000 code-streams to make them comply with the required options of the JPIP server. If the JPIP server requires JPEG 2000 code-streams to be formatted in a certain way, provide a tool that can convert any JPEG 2000 code-stream to comply with these requirements.
  * JPIP implementation over UDP protocol (ISO/IEC 15444-9 Annex H, H.2 Reliable Requests with Unreliable Data)
# Alternative implementations #
  * http://sourceforge.net/projects/cadi/
  * http://www.2kan.org/demonstrator.html
  * http://dltj.org/article/gsoc-jpip/
  * http://hirise.lpl.arizona.edu/jp2.php
  * http://sourceforge.net/apps/mediawiki/djatoka/index.php?title=Main_Page
  * http://www.gdal.org/frmt_jpipkak.html