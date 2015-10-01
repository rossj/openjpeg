# Introduction #

Based on the work done by Jerome Fines in 2008, the OpenJPEG team has decided in June 2011 to merge the V2 branch in the trunk. The goal of this operation is to release an official version of this work which will become the reference for the future development. Here we will describe and discuss about the evolution of structures in OpenJPEG.

# Main public structures #
Structures found in openjpeg.h

## opj\_stream\_t ##
Abstract JPEG2000 stream:
  * created from file or external stream
  * linked to opj\_stream\_private\_t structure inside the lib

## opj\_codec\_t ##
Abstract JPEG2000 codec (handle on the compressor or decompressor):
  * created from the codec format selected
  * linked to opj\_codec\_private\_t structure inside the lib

## opj\_dparameters\_t / opj\_cparameters\_t ##
Structure provide for the users to give respectively decompression and compression parameters to the lib.

## opj\_image ##
Structure where are stored image information and image component structure

## opj\_image\_comp\_t ##
Structure where are stored image component information and data

## opj\_codestream\_info\_v2\_t ##
Structure which give to the user the main information about the codestream included in the JPEG2000 file/stream:
  * Tile size and origin
  * Number of tile
  * Default information about tile compression -> opj\_tile\_info\_v2\_t structure
  * For each tile the compression parameters (NOT USED for the moment) -> opj\_tile\_info\_v2\_t structure

### opj\_tile\_info\_v2\_t ###
Structure which give visibility about the main tile compression parameters for one specific tile. The first part of this structure is common to all tile-component included in the tile:
  * tile index
  * coding style
  * progression order
  * number of layers
  * MCT identifier
  * Structure which store compression parameters for one tile component -> opj\_tccp\_info\_t

#### opj\_tccp\_info\_t ####
Structure which give visibility about low-level compression parameters for one tile component

## opj\_codestream\_index\_t ##
Structure which give to the user the main information about the position of main elements in the codestream included in the JPEG2000 file/stream:
  * main header positions (start and end)
  * codestream size
  * structure which store the position of the main marker (SOC, SOT, SOD, EOC and main header markers) -> opj\_marker\_info\_t
  * structure which store the information about position of markers inside each tile independently -> opj\_tile\_index\_t

### opj\_marker\_info\_t ###
Structure which store markers type and position and length in the codestream.

### opj\_tile\_index\_t ###
Structure which store the information about the index of elements in the tile:
  * tile index
  * structure which store the position of the markers in the tile header -> opj\_marker\_info\_t
  * structure which store information about tile part position of this tile -> opj\_tp\_index\_t
  * structure which store information about packet position of this tile -> opj\_packet\_info\_t


#### opj\_tp\_index\_t ####
Structure which store position of a tile-part and its header in the codestream

#### opj\_packet\_info\_t ####
Structure which store information concerning a packet inside tile

# Some private structures #
We will described here the main structures used in openjpeg.c, cio.h, j2k.h and jp2.h

## opj\_stream\_private\_t ##
It is the main internal structure to manage the byte input/output on the stream. It give access to the user data (file or external stream) and the main functions to handle the stream (read, write, move in the stream). Its give access to the buffer.

## opj\_codec\_private\_t ##
It is the main codec handler used for compression or decompression. Its contains:
  * an union which manage decompression and compression handlers -> opj\_compression\_t or opj\_decompression\_t
  * the flag which indicate if the codec is a decompressor or compressor
  * the event manager structure -> opj\_event\_mgr\_t
  * the internal codestream information structure -> opj\_codestream\_info\_v2\_t
  * the internal codestream index structure -> opj\_codestream\_index\_t
  * the internal codec which depends the JPEG2000 codec used (J2K or JP2 or (JPT)) -> opj\_j2k\_v2\_t / opj\_jp2\_v2\_t

### opj\_compression\_t ###
Move during the first part of merge but not used for the moment. It is the compression handlers generic to j2k or jp2 codec

### opj\_decompression\_t ###
Structure which give access to all generic decompression handlers.

## opj\_event\_mgr\_t ##
Message handler object used to manage the messages (error, warning and info) to the lib user.

## opj\_j2k\_v2\_t ##
Internal J2K codestream reader/writer. It is the main place where we can find the elements used in the J2K compression/decompresion process. Here we will now describe the structures used in the decompression process :
  * some parameters about decompression process -> opj\_j2k\_dec\_t
  * a private image structure which is used to store only the information about the whole output image (no data store in) -> opj\_image\_t
  * an output image to store the decoded image or sub part.
  * the coding parameters which describe how the codestream is encoded -> opj\_cp\_v2\_t
  * Two lists of procedure used to provide a more generic framework to the functions used in j2k codec
  * the internal codestream index -> opj\_codestream\_index\_t
  * the internal structure which manage the tile coding/decoding operation  -> opj\_tcd\_v2

## opj\_jp2\_v2\_t ##
Internal JP2 reader/writer structure. The JP2 codec must be considered as a set of boxes which enclose the J2K codestream. The goal of these boxes is to give clue to interpret the raw codestream. This structure follow this scheme and embedded a opj\_j2k\_v2\_t structure. Moreover it is composed of:
  * some parameters
  * a structure to handle the color interpretation -> opj\_jp2\_color\_t
  * Two lists of procedure used to provide a more generic framework to the functions used in jp2 codec