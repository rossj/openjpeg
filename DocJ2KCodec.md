

Note : as of v2.0, OpenJPEG executables for JPEG 2000 compression and decompression are named opj\_compress and opj\_decompress, respectively. In OpenJPEG v1.x, they were named image\_to\_j2k and j2k\_to\_image. Following documentation is still valid for those using OpenJPEG 1.x executables.

# opj\_compress #

## Description ##

This program reads in an image of a certain type and converts it to a JPEG 2000 file. It is part of the OpenJPEG library.

## Usage ##

```
opj_compress ... 
```

```
  -i <file>
```
> Input file. Either this argument or the -ImgDir argument described below is required. Valid input image extensions are BMP, PGM, PGX, PNG, PNM, PPM, RAW, TGA, TIF. For PNG  resp.  TIF, it needs libpng resp. libtiff. Concerning the BMP format, the coder accepts 24 bits color images and 8 bits (RLE or no-RLE) images. TIF files can have up to 16 bits per component. With RAW images, the -F parameter must be used (see below). In the case of raw images with a component depth comprised between 9 and 16 bits, each component data must be stored on two bytes, the first byte containing the MSBs and the second byte the LSBs. When using this option output file must be specified using -o.

```
  -o <file>
```
> Output file. Required when using -i option. Valid output image extensions are J2K, JP2, J2C.

```
  -ImgDir <directory_path>
```
> Path to the folder where the images to be compressed are stored. Either this argument or the -i argument described above is required. When Image files are in the same directory as the executable it can be indicated by a dot "." argument. When using this option, output format must be specified using -OutFor. The output codestreams are saved in the same folder.

```
  -OutFor <format>
```
> Output format used to compress the images read from the directory specified with -ImgDir. Required when -ImgDir option is used. Accepted formats are J2K, J2C, and JP2.

```
  -r <compression ratio>,<compression ratio>,...
```
> Compression ratio values. Each value is a factor of compression, thus 20 means 20 times compressed. Each value represents a quality layer. The order used to define the different levels of compression is important and must be from left to right in descending order. A final lossless quality layer will be signified by the value 1. Default: 1 single lossless quality layer.

```
  -q <quality in dB>,<quality in dB>,...
```
> Quality values. Each value is a psnr, to be given in dB, and represents a quality layer. The order used to define the different psnr-values is important and must be from left to right in ascending order. Default: 1 single lossless quality layer.

```
  -n <number of resolutions>
```
> Number of resolutions. It corresponds to the number of DWT decompositions +1. Default: 6.

```
  -b <cblk width>,<cblk height>
```
> Code-block size. The dimension must respect the constraint defined in the JPEG-2000 standard (no dimension smaller than 4 or greater than 1024, no code-block with more than 4096 coefficients). The maximum value authorized is 64x64. Default: 64x64.

```
  -c [<prec width>,<prec height>],[<prec width>,<prec height>],...
```
> Precinct size. Values specified must be power of 2. Multiple records may be supplied, in which case the first record refers to the highest resolution level and subsequent records to lower resolution levels. The last specified record is right-shifted for each remaining lower resolution levels. Default: 2<sup>15</sup>x2<sup>15</sup> at each resolution.

```
  -t <tile width>,<tile height>
```
> Tile size. Default: the dimension of the whole image, thus only one tile.

```
  -I
```
Irreversible compression (ICT + DWT 9-7). This option offers the possibility to work with the Irreversible Color Transformation (ICT) in place of the Reversible Color Transformation (RCT) and with the irreversible DWT 9-7 in place of the 5-3 filter. Default: off.

```
  -p <progression order>
```
> Progression order. The five progression orders are : LRCP, RLCP, RPCL, PCRL and CPRL. Default: LRCP.

```
  -cinema2K <24|48>
```
> Cinema2K profile.This option generates a codestream compliant to the Digital cinema specifications for a 2K resolution content. The value given is the frame rate which can be 24 or 48 fps. The main specifications of the JPEG Profile-3 (2K Digital Cinema Profile) are
    * Image size = 2048 x 1080 (at least one of the dimensions should match 2048 x 1080)
    * Single tile
    * Wavelet transform levels = Maximum of 5
    * Wavelet filter = 9-7 filter
    * Codeblock size = 32 x 32
    * Precinct size = 128 x 128 (Lowest frequency subband), 256 x 256 (other subbands)
    * Maximum Bit rate for entire frame = 1302083 bytes for 24 fps, 651041 bytes for 48fps
    * Maximum Bit rate for each color component= 1041666 bytes for 24 fps, 520833 bytes for 48fps
    * Tile parts = 3; Each tile part contains data necessary to decompress one 2K color component
    * 12 bits per component.

```
  -cinema4K
```
> Cinema4K profile. This option generates a codestream compliant to the Digital cinema specifications for a 4K resolution content. The value for frame rate should not be specified. Value is initialized to 24fps. The main specifications of the JPEG Profile-4 (4K Digital Cinema Profile) are
    * Image size = 4096 x 2160 (at least one of the dimensions must match 4096 x 2160)
    * Single tile
    * Wavelet transform levels = Maximum of 6 and mininum of 1
    * Wavelet filter = 9-7 filter
    * Codeblock size = 32 x 32
    * Precinct size = 128 x 128 (Lowest frequency subband), 256 x 256 (other subbands)
    * Maximum Bit rate for entire frame = 1302083 bytes for 24 fps
    * Maximum Bit rate for each color component= 1041666 bytes for 24 fps
    * Tile parts = 6; Each of first 3 tile parts contains data necessary to decompress one 2K color component, and each of last 3 tile parts contains data necessary to decompress one 4K color component.
    * 12 bits per component

```
  -POC T<tile number>=<res num start>,<comp num start>,<layer num end>,<res num end>,<comp num end>,<progression order> 
```
> Progression order change. This defines the bounds of resolution, color component, layer and progression order if a progression order change is desired.

> Example:
```
-POC T1=0,0,1,5,3,CPRL/T1=5,0,1,6,3,CPRL
```

```
  -s <subX,subY>
```
> Subsampling factor. The value are respectively for X and Y axis. Value higher than 2 can be a source of error ! Default: no subsampling.

```
  -SOP
```
> SOP marker before each packet. This option offers the possibility to add a specific marker before each packet. Default: no SOP.

```
  -EPH
```
> EPH marker after each packet header. This option offers the possibility to add a specific marker at the head of each packet header. Default: no EPH.

```
  -M <key value>
```
> Switch modes. This option offers the possibility to use a mode switch during the encoding process. There are 6 modes switches:
    * BYPASS(LAZY) `[`1`]`
    * RESET `[`2`]`
    * RESTART(TERMALL) `[`4`]`
    * VSC `[`8`]`
    * ERTERM(SEGTERM) `[`16`]`
    * SEGMARK(SEGSYM)] `[`32`]`
> For several mode switch you have to add the value between `[``]`. Default: no mode switch.

> Example : RESTART(4) + RESET(2) + SEGMARK(32) => -M 38

```
  -x <file>
```
`[`Index generation is currently broken in 2.x. See [issue #260](https://code.google.com/p/openjpeg/issues/detail?id=#260).`]`

Index file. This index is a text file that summarizes the codestream. This index is useful to create a navigation process.

> The index structure is the following
```
<image width> <image height>
<progression order>
<tile width> <tile height>
<# components>
<# layers>
<# decompositions N> (= # resolutions -1)
[<precinct width for rN>,<precinct height for rN>],[<precinct width for r0>,<precinct height for r0>]
<main header end position>
<codestream size>
Foreach tile
{
<tile index> <start pos> <tile header end pos> <end pos> <total disto> <# pixels> <max MSE>
Note : 
  'total disto' is the sum of the distortion reductions brought by each packet belonging to this tile
  'max MSE' (=total disto/#pixels)
}
Foreach packet
{
<packet index> <tile index> <layer index> <res index> <comp index> <prec index> <start pos> <end pos> <disto>
}
<max disto on the whole image>
<total disto on the whole image>
```

```
  -ROI c=<component index>,U=<upshifting value>
```
> Quantization indices upshifted for a component. Warning: This option does not implement the usual ROI (Region of Interest). It should be understood as a "Component of Interest". It offers the possibility to upshift the value of a component during quantization step. The value after c= is the component number [0, 1, 2, ...] and the value after U= is the value of upshifting. U must be in the range [0, 37].

```
  -d <off_X,off_Y>
```
> Offset of the image origin. The division in tile could be modified as the anchor point for tiling will be different than the image origin. However we must keep in mind that the offset of the image can not be higher than the tile dimension if the tile option is used. The 2 values are respectively for X and Y axis offset. Default: no offset.

```
  -T <off_X,off_Y>
```
> Offset of the tile origin. We must keep in mind that the tile anchor point can not be on the image area. The 2 values are respectively for X and Y axis offset. Default: no offset.

```
  -F <img width>,<img height>,<# components>,<bit-depth>,<s|u>
```
> Raw format specification. This option must be used when encoding an image stored under the RAW format. It defines the input image width, height, the number of components, the component bit depth and defines if the values are signed.

> Example of a 512x512 image with 3 unsigned components of 8 bits:
```
opj_compress -i lena.raw -o lena.j2k -F 512,512,3,8,u
```

> As explained above, in the case of raw images with a component depth comprised between 9 and 16 bits, each component data must be stored on two bytes, the first byte containing the MSBs and the second byte the LSBs.

```
  -mct {0,1,2}
```
> explicitely specifies if a Multiple Component Transform has to be used. 0: no MCT ; 1: RGB->YCC conversion ; 2: custom MCT. If custom MCT, "-m" option has to be used (see hereunder). By default, RGB->YCC conversion is used if there are 3 components or more, no conversion otherwise.

```
  -m <file>
```
> use array-based MCT, values are coma separated, line by line no specific separators between lines, no space allowed between values. If this option is used, it automatically sets "-mct" option to 2.

```
  -jpip
```
> write jpip codestream index box in JP2 output file. NOTICE: currently supports only RPCL order.

```
  -h 
```
> Print a help message and exit.

See JPWL OPTIONS for special options

## Default options ##

When only the input and output files are specified, the following default option values are used:
  * Lossless compression
  * 1 layer of quality
  * 1 tile
  * Size of precinct 2<sup>15</sup> x 2<sup>15</sup> (means 1 precinct)
  * Size of code-block 64 x 64
  * Number of resolution (i.e. DWT decomposition level) : 6
  * No SOP marker in the codestream
  * No EPH marker in the codestream
  * No sub-sampling in x and y direction
  * No mode switch activated
  * Progression order : LRCP
  * No index file
  * No ROI upshifted
  * No offset of the origin of the image
  * No offset of the origin of the tiles
  * Reversible DWT 5-3

## JPWL options ##

Following option is available only if the library has been compiled with the jpwl source files (located in './libopenjpeg/jpwl' and with the 'USE\_JPWL' flag).

```
  -W [h<tile><=type>,s<tile><=method>,a=<addr>,z=<size>,g=<range>,p<tile:pack><=type>]
```
> Adoption of JPWL (Part 11) capabilities. This option offers the possibility to work with the JPEG2000 for Wireless LANs (JPWL) extension, which is defined in Part 11 of the standard. The following parameters, separated by commas, can be written and repeated in any order:

  * h selects the header error protection (EPB): type can be
    * 0=none
    * 1,absent=predefined
    * 16=CRC-16
    * 32=CRC-32
    * 37-128=RS
> if tile is absent, it applies to main and tile headers;
> if tile is present, it applies from that tile onwards, up to the next h `<tile>` spec, or to the last tile in the codestream (max. 16 specs)
  * p selects the packet error protection (EEP/UEP with EPBs) to be applied to raw data: type can be
    * 0=none
    * 1,absent=predefined
    * 16=CRC-16
    * 32=CRC-32
    * 37-128=RS
> if tile:pack is absent, it starts from tile 0, packet 0;
> if tile:pack is present, it applies from that tile and that packet onwards, up to the next packet spec or to the last packet in the last tile in the codestream (max. 16 specs)
  * s enables sensitivity data insertion (ESD): method can be
    * -1=NO ESD
    * 0=RELATIVE ERROR
    * 1=MSE
    * 2=MSE REDUCTION
    * 3=PSNR
    * 4=PSNR INCREMENT
    * 5=MAXERR
    * 6=TSE
    * 7=RESERVED
> if tile is absent, it applies to main header only;
> if tile is present, it applies from that tile onwards, up to the next s`<tile>` spec, or to the last tile in the codestream (max. 16 specs)
  * g determines the addressing mode: range can be
    * 0=PACKET
    * 1=BYTE RANGE
    * 2=PACKET RANGE
  * a determines the size of data addressing: addr can be 2/4 bytes (small/large codestreams). If not set, auto-mode
  * z determines the size of sensitivity values: size can be 1/2 bytes, for the transformed pseudo-floating point value

### Examples ###

  * example 1:
```
-W h,h0=64,h3=16,h5=0,p0=78,p0:24=56,p1,p3:0=0,p3:20=32,s=0,s0=6,s3=-1,a=0,g=1,z=1
```
> means predefined EPB in MH, rs(64,32) from TPH 0 to TPH 2, CRC-16 in TPH 3 and TPH 4, no EPBs in remaining TPHs, UEP rs(78,32) for packets 0 to 23 of tile 0, UEP rs(56,32) for packets 24 to the last of tile 0, UEP rs default for packets of tile 1, no UEP for packets 0 to 19 of tile 3, UEP CRC-32 for packets 20 of tile 3 to last tile, relative sensitivity ESD for MH, TSE ESD from TPH 0 to TPH 2, byte range with automatic size of addresses and 1 byte for each sensitivity value

  * example 2:
```
-W h,s,p
```
> means default protection to headers (MH and TPHs) as well as data packets, one ESD in MH

# opj\_decompress #

## Description ##

This program reads in a jpeg2000 image and converts it to another image type. It is part of the OpenJPEG library.

> Valid input image extensions are .j2k, .jp2, .j2c, .jpt

> Valid output image extensions are .bmp, .pgm, .pgx, .png, .pnm, .ppm, .raw, .tga, .tif . For PNG resp.  TIF
> it needs libpng resp. libtiff .

## Usage ##

```
opj_decompress ... 
```

```
  -i <file>
```
> Input file. Either this argument or the -ImgDir argument described below is required. Valid input image extensions are J2K, JP2, JPC, JPT. When using this option output file must be specified using -o.

```
  -o <file>
```
> Output file. Required when using -i option. Currently accepts BMP, TIF, RAW, TGA, PGM, PPM, PNM and PGX files. Binary data is written to the file (not ascii). If a PGX filename is given, there will be as many output files as there are components: an indice starting from 0 will then be appended to the output filename, just before the "pgx" extension. If a PGM filename is given and there are more than one component, only the first component will be written to the file.

```
  -ImgDir <directory_path>
```
> Path to the folder where the compressed images are stored. Either this argument or the -i argument described above is required. When Image files are in the same directory as the executable it can be indicated by a dot "." argument. When using this option, output format must be specified using -OutFor. The output images are saved in the same folder.

```
  -OutFor <format>
```
> Output format used to decompress the codestreams read from the directory specified with -ImgDir. Required when -ImgDir option is used. Currently accepts TIF, RAW, TGA, PGM, PPM, PNM, PGX and BMP format.

```
  -r <reduce factor>
```
> Reduce factor. Set the number of highest resolution levels to be discarded. The image resolution is effectively divided by 2 to the power of the number of discarded levels. The reduce factor is limited by the smallest total number of decomposition levels among tiles.

```
  -l <layer number>
```
> Layer number. Set the maximum number of quality layers to decode. If there are less quality layers than the specified number, all the quality layers are decoded.

```
  -x <file>
```
`[`Index generation is currently broken in 2.x. See [issue #260](https://code.google.com/p/openjpeg/issues/detail?id=#260).`]`

> Index file. This index is a text file that summarizes the codestream. This index is useful to create a navigation process. It is identical to the one created at the encoder side, except that there is no distortion information.

```
  -h 
```
> Print a help message and exit.

See JPWL OPTIONS for special options

## JPWL options ##

Following option is available only if the library has been compiled with the jpwl source files (located in './libopenjpeg/jpwl' and with the 'USE\_JPWL' flag).

```
  -W [c,c=<numcomps>]
```
> Adoption of JPWL (Part 11) capabilities. Activates the JPEG2000 for Wireless LANs (Part 11) correction capabilities, if the codestream has been prepared accordingly (i.e. -W switch at the encoder). Options can be a comma separated list of <param=val> tokens:

  * c,c=`<numcomps>`
> numcomps is the number of expected components in the codestream (search of first EPB rely upon this, default is 3).

# Other implementations #
Open Source:
  * http://sourceforge.net/projects/kipa/
  * http://cuj2k.sourceforge.net/
  * http://www.cse.cuhk.edu.hk/~ttwong/demo/dwtgpu/dwtgpu.html
  * http://software.intel.com/en-us/articles/performance-tools-for-software-developers-application-notes-intel-ipp-jpeg2000-and-jasper-in-ksquirrel/
  * http://pirlwww.lpl.arizona.edu/software/PIRL_Java_Packages.shtml
  * http://homepage.mac.com/tmattox/publications/JP2K_OpenCL_full_DistA.pdf
**http://www.sitola.cz/wordpress/projects/multimedia-distribution-and-processing/gpu-acceleration-of-jpeg2000/en/**

PIRL contains an excellent JP2\_info cmd line tool


Other:
  * http://www.kakadusoftware.com
  * http://extras.springer.com/2002/978-0-7923-7519-7/ (kakadu 2.2.3 + test images)
  * http://dsplab.diei.unipg.it/software/c_quick_jpeg_2000_cqj2k