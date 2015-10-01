The MJ2 part of OpenJPEG has five modules: an encoder, a decoder, a J2K wrapper (j2k frames to an mj2 file), a J2K extractor (mj2 file to j2k frames) and a XML generator extracting metadata from MJ2 files.



![http://www.openjpeg.org/images/mj2_modules.gif](http://www.openjpeg.org/images/mj2_modules.gif)

# MJ2 encoder #

The MJ2 encoder compresses YUV files to Motion JPEG 2000 standard file.

The minimum command line for the MJ2 encoder is:
```
frames_to_mj2 -i <yuv_file.yuv>  -o <mj2_file.mj2> -W <width>,<height>,<CbCrSubsampling_dx>,<CbCrSubsampling_dy>
```

Use the -F option to specify the frame-rate (the default frame-rate is 25)

Example: To encode the standard YUV CIF frames (352\*288) formeman.yuv at 30 frames per second, the command line should be:
```
frames_to_mj2 -i foreman.yuv -o foreman.mj2 -W 352,288,2,2 -F 30
```

In addition, all the [JPEG 2000 Encoder](DocJ2KCodec.md) options can be used in the command line.
The MJ2 library generates the MJ2 boxes specified in the mj2\_movie structure. This structure can be a standard one, like in  the frames\_to\_mj2 codec, or a more specific one created by the user.
The standard mj2\_movie structure has one video track containig the compressed codestream of the yuv, with a timescale of 1ms, with one sample per chunk.

# MJ2 decoder #

The MJ2 decoder decompresses Motion JPEG 2000 files to YUV files.

The command line for the MJ2 decoder is:
```
mj2_to_frames <mj2_file.mj2>  <yuv_file.yuv>  
```

# MJ2 wrapper #

The MJ2 wrapper wraps one or several j2k bitstreams into a mj2 file. This wrapping is done with standard parameters (25 frames per second, no sound or hint tracks, ...), but this can be modified in the setparams function.

The command line for the MJ2 wrapper is:
```
wrap_j2k_in_mj2 <infile_root> <outfile.mj2>
```

where `<infile_root>` contains the path and the name of the input files before its number (5 digits, starting from 00000) and extension. For example, if I want to create the MJ2 file video/foreman.mj2 with the input files:
  * image/foreman\_00000.j2k
  * image/foreman\_00001.j2k
  * image/foreman\_00002.j2k
The command line to use is
```
wrap_j2k_in_mj2 image/foreman video/foreman.mj2
```

# MJ2 extractor #

The MJ2 extractor extracts the j2k bitstreams contained in an MJ2 file.

The command line for the MJ2 extractor is:
```
extract_j2k_from_mj2 <infile.mj2> <outfile_root>
```

where `<outfile_root>` contains the path and the name of the output files before its number (5 digits, starting from 00000) and extension. For example, if the MJ2 file video/foreman.mj2 contains three frames, if I want to create the input files:
  * image/foreman\_00000.j2k
  * image/foreman\_00001.j2k
  * image/foreman\_00002.j2k
The command line to use is
```
extract_j2k_from_mj2 video/foreman.mj2 image/foreman
```

# Metadata Reader #

"Mj2\_to\_metadata", under development, is a Windows command-line function that reads metadata from a Motion JPEG 2000 video file and generates an XML file with a representation of that content.  So far, it is limited to reporting structural metadata, but descriptive metadata is planned.  It is run from the command-line by:
```
mj2_to_metadata -i <input.mj2> -o <output.xml>
```

Additional options are discussed [here](http://www.openjpeg.org/mj2_to_metadata.html).
Thanks to Glenn Pearson for his contributions to this project !!!

# MJ2 Sample file #

An MJ2 sample file is available [here](http://www.openjpeg.org/speedway_opj.mj2).
To decompress it, use the following command:
```
mj2_to_frames speedway_opj.mj2 speedway_decompressed.yuv 
```
To extract the j2k images, use the following command:
```
extract_j2k_from_mj2 speedway_opj.mj2 speedway_frame
```