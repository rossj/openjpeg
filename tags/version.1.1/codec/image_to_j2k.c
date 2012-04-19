/*
 * Copyright (c) 2002-2007, Communications and Remote Sensing Laboratory, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2007, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux and Antonin Descampe
 * Copyright (c) 2005, Herve Drolon, FreeImage Team 
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
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "openjpeg.h"
#include "compat/getopt.h"
#include "convert.h"

#ifndef WIN32
#define stricmp strcasecmp
#define strnicmp strncasecmp
#endif

/* ----------------------------------------------------------------------- */

#define J2K_CFMT 0
#define JP2_CFMT 1
#define JPT_CFMT 2
#define MJ2_CFMT 3
#define PXM_DFMT 0
#define PGX_DFMT 1
#define BMP_DFMT 2
#define YUV_DFMT 3

/* ----------------------------------------------------------------------- */

void encode_help_display() {
	fprintf(stdout,"HELP\n----\n\n");
	fprintf(stdout,"- the -h option displays this help information on screen\n\n");

/* UniPG>> */
	fprintf(stdout,"List of parameters for the JPEG 2000 "
#ifdef USE_JPWL
		"+ JPWL "
#endif /* USE_JPWL */
		"encoder:\n");
/* <<UniPG */
	fprintf(stdout,"\n");
	fprintf(stdout,"REMARKS:\n");
	fprintf(stdout,"---------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"The markers written to the main_header are : SOC SIZ COD QCD COM.\n");
	fprintf(stdout,"COD and QCD never appear in the tile_header.\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"- This coder can encode a mega image, a test was made on a 24000x24000 pixels \n");
	fprintf(stdout,"color image.  You need enough disk space memory (twice the original) to encode \n");
	fprintf(stdout,"the image,i.e. for a 1.5 GB image you need a minimum of 3GB of disk memory)\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"By default:\n");
	fprintf(stdout,"------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout," * Lossless\n");
	fprintf(stdout," * 1 tile\n");
	fprintf(stdout," * Size of precinct : 2^15 x 2^15 (means 1 precinct)\n");
	fprintf(stdout," * Size of code-block : 64 x 64\n");
	fprintf(stdout," * Number of resolutions: 6\n");
	fprintf(stdout," * No SOP marker in the codestream\n");
	fprintf(stdout," * No EPH marker in the codestream\n");
	fprintf(stdout," * No sub-sampling in x or y direction\n");
	fprintf(stdout," * No mode switch activated\n");
	fprintf(stdout," * Progression order: LRCP\n");
	fprintf(stdout," * No index file\n");
	fprintf(stdout," * No ROI upshifted\n");
	fprintf(stdout," * No offset of the origin of the image\n");
	fprintf(stdout," * No offset of the origin of the tiles\n");
	fprintf(stdout," * Reversible DWT 5-3\n");
/* UniPG>> */
#ifdef USE_JPWL
	fprintf(stdout," * No JPWL protection\n");
#endif /* USE_JPWL */
/* <<UniPG */
	fprintf(stdout,"\n");
	fprintf(stdout,"Parameters:\n");
	fprintf(stdout,"------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Required Parameters (except with -h):\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-i           : source file  (-i source.pnm also *.pgm, *.ppm) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-o           : destination file (-o dest.j2k or .jp2) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Optional Parameters:\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-h           : display the help information \n ");
	fprintf(stdout,"\n");
	fprintf(stdout,"-r           : different compression ratios for successive layers (-r 20,10,5)\n ");
	fprintf(stdout,"	         - The rate specified for each quality level is the desired \n");
	fprintf(stdout,"	           compression factor.\n");
	fprintf(stdout,"		   Example: -r 20,10,1 means quality 1: compress 20x, \n");
	fprintf(stdout,"		     quality 2: compress 10x and quality 3: compress lossless\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"               (options -r and -q cannot be used together)\n ");
	fprintf(stdout,"\n");

	fprintf(stdout,"-q           : different psnr for successive layers (-q 30,40,50) \n ");

	fprintf(stdout,"               (options -r and -q cannot be used together)\n ");

	fprintf(stdout,"\n");
	fprintf(stdout,"-n           : number of resolutions (-n 3) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-b           : size of code block (-b 32,32) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-c           : size of precinct (-c 128,128) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-t           : size of tile (-t 512,512) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-p           : progression order (-p LRCP) [LRCP, RLCP, RPCL, PCRL, CPRL] \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-s           : subsampling factor (-s 2,2) [-s X,Y] \n");
	fprintf(stdout,"	     Remark: subsampling bigger than 2 can produce error\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-SOP         : write SOP marker before each packet \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-EPH         : write EPH marker after each header packet \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-M           : mode switch (-M 3) [1=BYPASS(LAZY) 2=RESET 4=RESTART(TERMALL)\n");
	fprintf(stdout,"                 8=VSC 16=ERTERM(SEGTERM) 32=SEGMARK(SEGSYM)] \n");
	fprintf(stdout,"                 Indicate multiple modes by adding their values. \n");
	fprintf(stdout,"                 ex: RESTART(4) + RESET(2) + SEGMARK(32) = -M 38\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-x           : create an index file *.Idx (-x index_name.Idx) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-ROI         : c=%%d,U=%%d : quantization indices upshifted \n");
	fprintf(stdout,"               for component c=%%d [%%d = 0,1,2]\n");
	fprintf(stdout,"               with a value of U=%%d [0 <= %%d <= 37] (i.e. -ROI:c=0,U=25) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-d           : offset of the origin of the image (-d 150,300) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-T           : offset of the origin of the tiles (-T 100,75) \n");
	fprintf(stdout,"\n");
	fprintf(stdout,"-I           : use the irreversible DWT 9-7 (-I) \n");
	fprintf(stdout,"\n");
/* UniPG>> */
#ifdef USE_JPWL
	fprintf(stdout,"-W           : adoption of JPWL (Part 11) capabilities (-W params)\n");
	fprintf(stdout,"               The parameters can be written and repeated in any order:\n");
	fprintf(stdout,"               [h<tile><=type>,s<tile><=method>,a=<addr>,z=<size>,g=<range>,...\n");
	fprintf(stdout,"                ...,p<tile:pack><=type>]\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 h selects the header error protection (EPB): 'type' can be\n");
	fprintf(stdout,"                   [0=none 1,absent=predefined 16=CRC-16 32=CRC-32 37-128=RS]\n");
	fprintf(stdout,"                   if 'tile' is absent, it applies to main and tile headers\n");
	fprintf(stdout,"                   if 'tile' is present, it applies from that tile\n");
	fprintf(stdout,"                     onwards, up to the next h<tile> spec, or to the last tile\n");
	fprintf(stdout,"                     in the codestream (max. %d specs)\n", JPWL_MAX_NO_TILESPECS);
	fprintf(stdout,"\n");
	fprintf(stdout,"                 p selects the packet error protection (EEP/UEP with EPBs)\n");
	fprintf(stdout,"                  to be applied to raw data: 'type' can be\n");
	fprintf(stdout,"                   [0=none 1,absent=predefined 16=CRC-16 32=CRC-32 37-128=RS]\n");
	fprintf(stdout,"                   if 'tile:pack' is absent, it starts from tile 0, packet 0\n");
	fprintf(stdout,"                   if 'tile:pack' is present, it applies from that tile\n");
	fprintf(stdout,"                     and that packet onwards, up to the next packet spec\n");
	fprintf(stdout,"                     or to the last packet in the last tile in the codestream\n");
	fprintf(stdout,"                     (max. %d specs)\n", JPWL_MAX_NO_PACKSPECS);
	fprintf(stdout,"\n");
	fprintf(stdout,"                 s enables sensitivity data insertion (ESD): 'method' can be\n");
	fprintf(stdout,"                   [-1=NO ESD 0=RELATIVE ERROR 1=MSE 2=MSE REDUCTION 3=PSNR\n");
	fprintf(stdout,"                    4=PSNR INCREMENT 5=MAXERR 6=TSE 7=RESERVED]\n");
	fprintf(stdout,"                   if 'tile' is absent, it applies to main header only\n");
	fprintf(stdout,"                   if 'tile' is present, it applies from that tile\n");
	fprintf(stdout,"                     onwards, up to the next s<tile> spec, or to the last tile\n");
	fprintf(stdout,"                     in the codestream (max. %d specs)\n", JPWL_MAX_NO_TILESPECS);
	fprintf(stdout,"\n");
	fprintf(stdout,"                 g determines the addressing mode: <range> can be\n");
	fprintf(stdout,"                   [0=PACKET 1=BYTE RANGE 2=PACKET RANGE]\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 a determines the size of data addressing: <addr> can be\n");
	fprintf(stdout,"                   2/4 bytes (small/large codestreams). If not set, auto-mode\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 z determines the size of sensitivity values: <size> can be\n");
	fprintf(stdout,"                   1/2 bytes, for the transformed pseudo-floating point value\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 ex.:\n");
	fprintf(stdout," h,h0=64,h3=16,h5=32,p0=78,p0:24=56,p1,p3:0=0,p3:20=32,s=0,s0=6,s3=-1,a=0,g=1,z=1\n");
	fprintf(stdout,"                 means\n");
	fprintf(stdout,"                   predefined EPB in MH, rs(64,32) from TPH 0 to TPH 2,\n");
	fprintf(stdout,"                   CRC-16 in TPH 3 and TPH 4, CRC-32 in remaining TPHs,\n");
	fprintf(stdout,"                   UEP rs(78,32) for packets 0 to 23 of tile 0,\n");
	fprintf(stdout,"                   UEP rs(56,32) for packets 24 to the last of tile 0,\n");
	fprintf(stdout,"                   UEP rs default for packets of tile 1,\n");
	fprintf(stdout,"                   no UEP for packets 0 to 19 of tile 3,\n");
	fprintf(stdout,"                   UEP CRC-32 for packets 20 of tile 3 to last tile,\n");
	fprintf(stdout,"                   relative sensitivity ESD for MH,\n");
	fprintf(stdout,"                   TSE ESD from TPH 0 to TPH 2, byte range with automatic\n");
	fprintf(stdout,"                   size of addresses and 1 byte for each sensitivity value\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 ex.:\n");
	fprintf(stdout,"                       h,s,p\n");
	fprintf(stdout,"                 means\n");
	fprintf(stdout,"                   default protection to headers (MH and TPHs) as well as\n");
	fprintf(stdout,"                   data packets, one ESD in MH\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"                 N.B.: use the following recommendations when specifying\n");
	fprintf(stdout,"                       the JPWL parameters list\n");
	fprintf(stdout,"                   - when you use UEP, always pair the 'p' option with 'h'\n");
	fprintf(stdout,"                 \n");
#endif /* USE_JPWL */
/* <<UniPG */
	fprintf(stdout,"IMPORTANT:\n");
	fprintf(stdout,"-----------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"The index file has the structure below:\n");
	fprintf(stdout,"---------------------------------------\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"Image_height Image_width\n");
	fprintf(stdout,"progression order\n");
	fprintf(stdout,"Tiles_size_X Tiles_size_Y\n");
/* UniPG>> */
	fprintf(stdout,"Tiles_nb_X Tiles_nb_Y\n");
/* <<UniPG */
	fprintf(stdout,"Components_nb\n");
	fprintf(stdout,"Layers_nb\n");
	fprintf(stdout,"decomposition_levels\n");
	fprintf(stdout,"[Precincts_size_X_res_Nr Precincts_size_Y_res_Nr]...\n");
	fprintf(stdout,"   [Precincts_size_X_res_0 Precincts_size_Y_res_0]\n");
	fprintf(stdout,"Main_header_end_position\n");
	fprintf(stdout,"Codestream_size\n");
	fprintf(stdout,"Tile_0 start_pos end_Theader end_pos TotalDisto NumPix MaxMSE\n");
	fprintf(stdout,"Tile_1   ''           ''        ''        ''       ''    ''\n");
	fprintf(stdout,"...\n");
	fprintf(stdout,"Tile_Nt   ''           ''        ''        ''       ''    ''\n");
	fprintf(stdout,"Tpacket_0 Tile layer res. comp. prec. start_pos end_pos disto\n");
	fprintf(stdout,"...\n");
	fprintf(stdout,"Tpacket_Np ''   ''    ''   ''    ''       ''       ''     ''\n");

	fprintf(stdout,"MaxDisto\n");

	fprintf(stdout,"TotalDisto\n\n");
}

OPJ_PROG_ORDER give_progression(char progression[4]) {
	if(strncmp(progression, "LRCP", 4) == 0) {
		return LRCP;
	}
	if(strncmp(progression, "RLCP", 4) == 0) {
		return RLCP;
	}
	if(strncmp(progression, "RPCL", 4) == 0) {
		return RPCL;
	}
	if(strncmp(progression, "PCRL", 4) == 0) {
		return PCRL;
	}
	if(strncmp(progression, "CPRL", 4) == 0) {
		return CPRL;
	}

	return PROG_UNKNOWN;
}

int get_file_format(char *filename) {
	unsigned int i;
	static const char *extension[] = {
    "pgx", "pnm", "pgm", "ppm", "bmp", "j2k", "jp2"
    };
	static const int format[] = {
    PGX_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, BMP_DFMT, J2K_CFMT, JP2_CFMT
    };
	char * ext = strrchr(filename, '.') + 1;
	for(i = 0; i < sizeof(format)/sizeof(*format); i++) {
		if(strnicmp(ext, extension[i], 3) == 0) {
			return format[i];
		}
	}

	return -1;
}

/* -------------------------------------------------------------------------*/

int parse_cmdline_encoder(int argc, char **argv, opj_cparameters_t *parameters) {
	int i, j;

	/* parse the command line */
/* UniPG>> */
	const char optlist[] = "i:o:hr:q:n:b:c:t:p:s:SEM:x:R:d:T:If:P:C:"
#ifdef USE_JPWL
		"W:"
#endif /* USE_JPWL */
		;

	while (1) {
		int c = getopt(argc, argv, optlist);
/* <<UniPG */
		if (c == -1)
			break;
		switch (c) {
			case 'i':			/* input file */
			{
				char *infile = optarg;
				parameters->decod_format = get_file_format(infile);
				switch(parameters->decod_format) {
					case PGX_DFMT:
					case PXM_DFMT:
					case BMP_DFMT:
						break;
					default:
						fprintf(stderr,
							"!! Unrecognized format for infile : %s "
              "[accept only *.pnm, *.pgm, *.ppm, *.pgx or *.bmp] !!\n\n", 
							infile);
						return 1;
				}
				strncpy(parameters->infile, infile, OPJ_PATH_LEN);
			}
			break;

				/* ----------------------------------------------------- */

			case 'o':			/* output file */
			{
				char *outfile = optarg;
				parameters->cod_format = get_file_format(outfile);
				switch(parameters->cod_format) {
					case J2K_CFMT:
					case JP2_CFMT:
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.j2k, *.jp2]!! \n", outfile);
						return 1;
				}
				strncpy(parameters->outfile, outfile, OPJ_PATH_LEN);
			}
			break;

				/* ----------------------------------------------------- */

			case 'r':			/* rates rates/distorsion */
			{
				char *s = optarg;
				while (sscanf(s, "%f", &parameters->tcp_rates[parameters->tcp_numlayers]) == 1) {
					parameters->tcp_numlayers++;
					while (*s && *s != ',') {
						s++;
					}
					if (!*s)
						break;
					s++;
				}
				parameters->cp_disto_alloc = 1;
			}
			break;

				/* ----------------------------------------------------- */

			case 'q':			/* add fixed_quality */
			{
				char *s = optarg;
				while (sscanf(s, "%f", &parameters->tcp_distoratio[parameters->tcp_numlayers]) == 1) {
					parameters->tcp_numlayers++;
					while (*s && *s != ',') {
						s++;
					}
					if (!*s)
						break;
					s++;
				}
				parameters->cp_fixed_quality = 1;
			}
			break;

				/* dda */
				/* ----------------------------------------------------- */

			case 'f':			/* mod fixed_quality (before : -q) */
			{
				int *row = NULL, *col = NULL;
				int numlayers = 0, numresolution = 0, matrix_width = 0;

				char *s = optarg;
				sscanf(s, "%d", &numlayers);
				s++;
				if (numlayers > 9)
					s++;

				parameters->tcp_numlayers = numlayers;
				numresolution = parameters->numresolution;
				matrix_width = numresolution * 3;
				parameters->cp_matrice = (int *) malloc(numlayers * matrix_width * sizeof(int));
				s = s + 2;

				for (i = 0; i < numlayers; i++) {
					row = &parameters->cp_matrice[i * matrix_width];
					col = row;
					parameters->tcp_rates[i] = 1;
					sscanf(s, "%d,", &col[0]);
					s += 2;
					if (col[0] > 9)
						s++;
					col[1] = 0;
					col[2] = 0;
					for (j = 1; j < numresolution; j++) {
						col += 3;
						sscanf(s, "%d,%d,%d", &col[0], &col[1], &col[2]);
						s += 6;
						if (col[0] > 9)
							s++;
						if (col[1] > 9)
							s++;
						if (col[2] > 9)
							s++;
					}
					if (i < numlayers - 1)
						s++;
				}
				parameters->cp_fixed_alloc = 1;
			}
			break;

				/* ----------------------------------------------------- */

			case 't':			/* tiles */
			{
				sscanf(optarg, "%d,%d", &parameters->cp_tdx, &parameters->cp_tdy);
				parameters->tile_size_on = true;
			}
			break;

				/* ----------------------------------------------------- */

			case 'n':			/* resolution */
			{
				sscanf(optarg, "%d", &parameters->numresolution);
			}
			break;

				/* ----------------------------------------------------- */
			case 'c':			/* precinct dimension */
			{
				char sep;
				int res_spec = 0;

				char *s = optarg;
				do {
					sep = 0;
					sscanf(s, "[%d,%d]%c", &parameters->prcw_init[res_spec],
                                 &parameters->prch_init[res_spec], &sep);
					parameters->csty |= 0x01;
					res_spec++;
					s = strpbrk(s, "]") + 2;
				}
				while (sep == ',');
				parameters->res_spec = res_spec;
			}
			break;

				/* ----------------------------------------------------- */

			case 'b':			/* code-block dimension */
			{
				int cblockw_init = 0, cblockh_init = 0;
				sscanf(optarg, "%d,%d", &cblockw_init, &cblockh_init);
				if (cblockw_init * cblockh_init > 4096 || cblockw_init > 1024
					|| cblockw_init < 4 || cblockh_init > 1024 || cblockh_init < 4) {
					fprintf(stderr,
						"!! Size of code_block error (option -b) !!\n\nRestriction :\n"
            "    * width*height<=4096\n    * 4<=width,height<= 1024\n\n");
					return 1;
				}
				parameters->cblockw_init = cblockw_init;
				parameters->cblockh_init = cblockh_init;
			}
			break;

				/* ----------------------------------------------------- */

			case 'x':			/* creation of index file */
			{
				char *index = optarg;
				strncpy(parameters->index, index, OPJ_PATH_LEN);
				parameters->index_on = 1;
			}
			break;

				/* ----------------------------------------------------- */

			case 'p':			/* progression order */
			{
				char progression[4];

				strncpy(progression, optarg, 4);
				parameters->prog_order = give_progression(progression);
				if (parameters->prog_order == -1) {
					fprintf(stderr, "Unrecognized progression order "
            "[LRCP, RLCP, RPCL, PCRL, CPRL] !!\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 's':			/* subsampling factor */
			{
				if (sscanf(optarg, "%d,%d", &parameters->subsampling_dx,
                                    &parameters->subsampling_dy) != 2) {
					fprintf(stderr,	"'-s' sub-sampling argument error !  [-s dx,dy]\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 'd':			/* coordonnate of the reference grid */
			{
				if (sscanf(optarg, "%d,%d", &parameters->image_offset_x0,
                                    &parameters->image_offset_y0) != 2) {
					fprintf(stderr,	"-d 'coordonnate of the reference grid' argument "
            "error !! [-d x0,y0]\n");
					return 1;
				}
			}
			break;

				/* ----------------------------------------------------- */

			case 'h':			/* display an help description */
				encode_help_display();
				return 1;

				/* ----------------------------------------------------- */

			case 'P':			/* POC */
			{
				int numpocs = 0;		/* number of progression order change (POC) default 0 */
				opj_poc_t *POC = NULL;	/* POC : used in case of Progression order change */

				char *s = optarg;
				POC = parameters->POC;

				fprintf(stderr, "/----------------------------------\\\n");
				fprintf(stderr, "|  POC option not fully tested !!  |\n");
				fprintf(stderr, "\\----------------------------------/\n");

				while (sscanf(s, "T%d=%d,%d,%d,%d,%d,%s", &POC[numpocs].tile,
					&POC[numpocs].resno0, &POC[numpocs].compno0,
					&POC[numpocs].layno1, &POC[numpocs].resno1,
					&POC[numpocs].compno1, POC[numpocs].progorder) == 7) {
					POC[numpocs].prg = give_progression(POC[numpocs].progorder);
					/* POC[numpocs].tile; */
					numpocs++;
					while (*s && *s != '/') {
						s++;
					}
					if (!*s) {
						break;
					}
					s++;
				}
				parameters->numpocs = numpocs;
			}
			break;

				/* ------------------------------------------------------ */

			case 'S':			/* SOP marker */
			{
				parameters->csty |= 0x02;
			}
			break;

				/* ------------------------------------------------------ */

			case 'E':			/* EPH marker */
			{
				parameters->csty |= 0x04;
			}
			break;

				/* ------------------------------------------------------ */

			case 'M':			/* Mode switch pas tous au point !! */
			{
				int value = 0;
				if (sscanf(optarg, "%d", &value) == 1) {
					for (i = 0; i <= 5; i++) {
						int cache = value & (1 << i);
						if (cache)
							parameters->mode |= (1 << i);
					}
				}
			}
			break;

				/* ------------------------------------------------------ */

			case 'R':			/* ROI */
			{
				if (sscanf(optarg, "OI:c=%d,U=%d", &parameters->roi_compno,
                                           &parameters->roi_shift) != 2) {
					fprintf(stderr, "ROI error !! [-ROI:c='compno',U='shift']\n");
					return 1;
				}
			}
			break;

				/* ------------------------------------------------------ */

			case 'T':			/* Tile offset */
			{
				if (sscanf(optarg, "%d,%d", &parameters->cp_tx0, &parameters->cp_ty0) != 2) {
					fprintf(stderr, "-T 'tile offset' argument error !! [-T X0,Y0]");
					return 1;
				}
			}
			break;

				/* ------------------------------------------------------ */

			case 'C':			/* add a comment */
			{
				parameters->cp_comment = (char*)malloc(strlen(optarg) + 1);
				if(parameters->cp_comment) {
					strcpy(parameters->cp_comment, optarg);
				}
			}
			break;


				/* ------------------------------------------------------ */

			case 'I':			/* reversible or not */
			{
				parameters->irreversible = 1;
			}
			break;

/* UniPG>> */
#ifdef USE_JPWL
				/* ------------------------------------------------------ */
			
			case 'W':			/* JPWL capabilities switched on */
			{
				char *token = NULL;
				int hprot, pprot, sens, addr, size, range;

				/* we need to enable indexing */
				if (!parameters->index_on) {
					strncpy(parameters->index, JPWL_PRIVATEINDEX_NAME, OPJ_PATH_LEN);
					parameters->index_on = 1;
				}

				/* search for different protection methods */

				/* break the option in comma points and parse the result */
				token = strtok(optarg, ",");
				while(token != NULL) {

					/* search header error protection method */
					if (*token == 'h') {

						static int tile = 0, tilespec = 0, lasttileno = 0;

						hprot = 1; /* predefined method */

						if(sscanf(token, "h=%d", &hprot) == 1) {
							/* Main header, specified */
							if (!((hprot == 0) || (hprot == 1) || (hprot == 16) || (hprot == 32) ||
								((hprot >= 37) && (hprot <= 128)))) {
								fprintf(stderr, "ERROR -> invalid main header protection method h = %d\n", hprot);
								return 1;
							}
							parameters->jpwl_hprot_MH = hprot;

						} else if(sscanf(token, "h%d=%d", &tile, &hprot) == 2) {
							/* Tile part header, specified */
							if (!((hprot == 0) || (hprot == 1) || (hprot == 16) || (hprot == 32) ||
								((hprot >= 37) && (hprot <= 128)))) {
								fprintf(stderr, "ERROR -> invalid tile header protection method h = %d\n", hprot);
								return 1;
							}
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on protection method t = %d\n", tile);
								return 1;
							}
							if (tilespec < JPWL_MAX_NO_TILESPECS) {
								parameters->jpwl_hprot_TPH_tileno[tilespec] = lasttileno = tile;
								parameters->jpwl_hprot_TPH[tilespec++] = hprot;
							}

						} else if(sscanf(token, "h%d", &tile) == 1) {
							/* Tile part header, unspecified */
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on protection method t = %d\n", tile);
								return 1;
							}
							if (tilespec < JPWL_MAX_NO_TILESPECS) {
								parameters->jpwl_hprot_TPH_tileno[tilespec] = lasttileno = tile;
								parameters->jpwl_hprot_TPH[tilespec++] = hprot;
							}


						} else if (!strcmp(token, "h")) {
							/* Main header, unspecified */
							parameters->jpwl_hprot_MH = hprot;

						} else {
							fprintf(stderr, "ERROR -> invalid protection method selection = %s\n", token);
							return 1;
						};

					}

					/* search packet error protection method */
					if (*token == 'p') {

						static int pack = 0, tile = 0, packspec = 0, lastpackno = 0;

						pprot = 1; /* predefined method */

						if (sscanf(token, "p=%d", &pprot) == 1) {
							/* Method for all tiles and all packets */
							if (!((pprot == 0) || (pprot == 1) || (pprot == 16) || (pprot == 32) ||
								((pprot >= 37) && (pprot <= 128)))) {
								fprintf(stderr, "ERROR -> invalid default packet protection method p = %d\n", pprot);
								return 1;
							}
							parameters->jpwl_pprot_tileno[0] = 0;
							parameters->jpwl_pprot_packno[0] = 0;
							parameters->jpwl_pprot[0] = pprot;

						} else if (sscanf(token, "p%d=%d", &tile, &pprot) == 2) {
							/* method specified from that tile on */
							if (!((pprot == 0) || (pprot == 1) || (pprot == 16) || (pprot == 32) ||
								((pprot >= 37) && (pprot <= 128)))) {
								fprintf(stderr, "ERROR -> invalid packet protection method p = %d\n", pprot);
								return 1;
							}
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on protection method p = %d\n", tile);
								return 1;
							}
							if (packspec < JPWL_MAX_NO_PACKSPECS) {
								parameters->jpwl_pprot_tileno[packspec] = tile;
								parameters->jpwl_pprot_packno[packspec] = 0;
								parameters->jpwl_pprot[packspec++] = pprot;
							}

						} else if (sscanf(token, "p%d:%d=%d", &tile, &pack, &pprot) == 3) {
							/* method fully specified from that tile and that packet on */
							if (!((pprot == 0) || (pprot == 1) || (pprot == 16) || (pprot == 32) ||
								((pprot >= 37) && (pprot <= 128)))) {
								fprintf(stderr, "ERROR -> invalid packet protection method p = %d\n", pprot);
								return 1;
							}
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on protection method p = %d\n", tile);
								return 1;
							}
							if (pack < 0) {
								fprintf(stderr, "ERROR -> invalid packet number on protection method p = %d\n", pack);
								return 1;
							}
							if (packspec < JPWL_MAX_NO_PACKSPECS) {
								parameters->jpwl_pprot_tileno[packspec] = tile;
								parameters->jpwl_pprot_packno[packspec] = pack;
								parameters->jpwl_pprot[packspec++] = pprot;
							}

						} else if (sscanf(token, "p%d:%d", &tile, &pack) == 2) {
							/* default method from that tile and that packet on */
							if (!((pprot == 0) || (pprot == 1) || (pprot == 16) || (pprot == 32) ||
								((pprot >= 37) && (pprot <= 128)))) {
								fprintf(stderr, "ERROR -> invalid packet protection method p = %d\n", pprot);
								return 1;
							}
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on protection method p = %d\n", tile);
								return 1;
							}
							if (pack < 0) {
								fprintf(stderr, "ERROR -> invalid packet number on protection method p = %d\n", pack);
								return 1;
							}
							if (packspec < JPWL_MAX_NO_PACKSPECS) {
								parameters->jpwl_pprot_tileno[packspec] = tile;
								parameters->jpwl_pprot_packno[packspec] = pack;
								parameters->jpwl_pprot[packspec++] = pprot;
							}

						} else if (sscanf(token, "p%d", &tile) == 1) {
							/* default from a tile on */
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on protection method p = %d\n", tile);
								return 1;
							}
							if (packspec < JPWL_MAX_NO_PACKSPECS) {
								parameters->jpwl_pprot_tileno[packspec] = tile;
								parameters->jpwl_pprot_packno[packspec] = 0;
								parameters->jpwl_pprot[packspec++] = pprot;
							}


						} else if (!strcmp(token, "p")) {
							/* all default */
							parameters->jpwl_pprot_tileno[0] = 0;
							parameters->jpwl_pprot_packno[0] = 0;
							parameters->jpwl_pprot[0] = pprot;

						} else {
							fprintf(stderr, "ERROR -> invalid protection method selection = %s\n", token);
							return 1;
						};

					}

					/* search sensitivity method */
					if (*token == 's') {

						static int tile = 0, tilespec = 0, lasttileno = 0;

						sens = 0; /* predefined: relative error */

						if(sscanf(token, "s=%d", &sens) == 1) {
							/* Main header, specified */
							if ((sens < -1) || (sens > 7)) {
								fprintf(stderr, "ERROR -> invalid main header sensitivity method s = %d\n", sens);
								return 1;
							}
							parameters->jpwl_sens_MH = sens;

						} else if(sscanf(token, "s%d=%d", &tile, &sens) == 2) {
							/* Tile part header, specified */
							if ((sens < -1) || (sens > 7)) {
								fprintf(stderr, "ERROR -> invalid tile header sensitivity method s = %d\n", sens);
								return 1;
							}
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on sensitivity method t = %d\n", tile);
								return 1;
							}
							if (tilespec < JPWL_MAX_NO_TILESPECS) {
								parameters->jpwl_sens_TPH_tileno[tilespec] = lasttileno = tile;
								parameters->jpwl_sens_TPH[tilespec++] = sens;
							}

						} else if(sscanf(token, "s%d", &tile) == 1) {
							/* Tile part header, unspecified */
							if (tile < 0) {
								fprintf(stderr, "ERROR -> invalid tile number on sensitivity method t = %d\n", tile);
								return 1;
							}
							if (tilespec < JPWL_MAX_NO_TILESPECS) {
								parameters->jpwl_sens_TPH_tileno[tilespec] = lasttileno = tile;
								parameters->jpwl_sens_TPH[tilespec++] = hprot;
							}

						} else if (!strcmp(token, "s")) {
							/* Main header, unspecified */
							parameters->jpwl_sens_MH = sens;

						} else {
							fprintf(stderr, "ERROR -> invalid sensitivity method selection = %s\n", token);
							return 1;
						};
						
						parameters->jpwl_sens_size = 2; /* 2 bytes for default size */
					}

					/* search addressing size */
					if (*token == 'a') {

						static int tile = 0, tilespec = 0, lasttileno = 0;

						addr = 0; /* predefined: auto */

						if(sscanf(token, "a=%d", &addr) == 1) {
							/* Specified */
							if ((addr != 0) && (addr != 2) && (addr != 4)) {
								fprintf(stderr, "ERROR -> invalid addressing size a = %d\n", addr);
								return 1;
							}
							parameters->jpwl_sens_addr = addr;

						} else if (!strcmp(token, "a")) {
							/* default */
							parameters->jpwl_sens_addr = addr; /* auto for default size */

						} else {
							fprintf(stderr, "ERROR -> invalid addressing selection = %s\n", token);
							return 1;
						};
						
					}

					/* search sensitivity size */
					if (*token == 'z') {

						static int tile = 0, tilespec = 0, lasttileno = 0;

						size = 1; /* predefined: 1 byte */

						if(sscanf(token, "z=%d", &size) == 1) {
							/* Specified */
							if ((size != 0) && (size != 1) && (size != 2)) {
								fprintf(stderr, "ERROR -> invalid sensitivity size z = %d\n", size);
								return 1;
							}
							parameters->jpwl_sens_size = size;

						} else if (!strcmp(token, "a")) {
							/* default */
							parameters->jpwl_sens_size = size; /* 1 for default size */

						} else {
							fprintf(stderr, "ERROR -> invalid size selection = %s\n", token);
							return 1;
						};
						
					}

					/* search range method */
					if (*token == 'g') {

						static int tile = 0, tilespec = 0, lasttileno = 0;

						range = 0; /* predefined: 0 (packet) */

						if(sscanf(token, "g=%d", &range) == 1) {
							/* Specified */
							if ((range < 0) || (range > 3)) {
								fprintf(stderr, "ERROR -> invalid sensitivity range method g = %d\n", range);
								return 1;
							}
							parameters->jpwl_sens_range = range;

						} else if (!strcmp(token, "g")) {
							/* default */
							parameters->jpwl_sens_range = range;

						} else {
							fprintf(stderr, "ERROR -> invalid range selection = %s\n", token);
							return 1;
						};
						
					}

					/* next token or bust */
					token = strtok(NULL, ",");
				};


				/* some info */
				fprintf(stdout, "Info: JPWL capabilities enabled\n");
				parameters->jpwl_epc_on = true;

			}
			break;
#endif USE_JPWL
/* <<UniPG */

				/* ------------------------------------------------------ */

			default:
				fprintf(stderr, "ERROR -> this option is not valid \"-%c %s\"\n", c, optarg);
				return 1;
		}
	}

	/* check for possible errors */

	if((parameters->infile[0] == 0) || (parameters->outfile[0] == 0)) {
		fprintf(stderr, "usage: image_to_j2k -i image-file -o j2k/jp2-file (+ options)\n");
		return 1;
	}

	if ((parameters->cp_disto_alloc || parameters->cp_fixed_alloc || parameters->cp_fixed_quality)
		&& (!(parameters->cp_disto_alloc ^ parameters->cp_fixed_alloc ^ parameters->cp_fixed_quality))) {
		fprintf(stderr, "Error: options -r -q and -f cannot be used together !!\n");
		return 1;
	}				/* mod fixed_quality */

	/* if no rate entered, lossless by default */
	if (parameters->tcp_numlayers == 0) {
		parameters->tcp_rates[0] = 0;	/* MOD antonin : losslessbug */
		parameters->tcp_numlayers++;
		parameters->cp_disto_alloc = 1;
	}

	if((parameters->cp_tx0 > parameters->image_offset_x0) || (parameters->cp_ty0 > parameters->image_offset_y0)) {
		fprintf(stderr,
			"Error: Tile offset dimension is unnappropriate --> TX0(%d)<=IMG_X0(%d) TYO(%d)<=IMG_Y0(%d) \n",
			parameters->cp_tx0, parameters->image_offset_x0, parameters->cp_ty0, parameters->image_offset_y0);
		return 1;
	}

	for (i = 0; i < parameters->numpocs; i++) {
		if (parameters->POC[i].prg == -1) {
			fprintf(stderr,
				"Unrecognized progression order in option -P (POC n %d) [LRCP, RLCP, RPCL, PCRL, CPRL] !!\n",
				i + 1);
		}
	}

	return 0;
}

/* -------------------------------------------------------------------------- */

/**
sample error callback expecting a FILE* client object
*/
void error_callback(const char *msg, void *client_data) {
	FILE *stream = (FILE*)client_data;
	fprintf(stream, "[ERROR] %s", msg);
}
/**
sample warning callback expecting a FILE* client object
*/
void warning_callback(const char *msg, void *client_data) {
	FILE *stream = (FILE*)client_data;
	fprintf(stream, "[WARNING] %s", msg);
}
/**
sample debug callback expecting a FILE* client object
*/
void info_callback(const char *msg, void *client_data) {
	FILE *stream = (FILE*)client_data;
	fprintf(stream, "[INFO] %s", msg);
}

/* -------------------------------------------------------------------------- */

int main(int argc, char **argv) {
	bool bSuccess;
	opj_cparameters_t parameters;	/* compression parameters */
	opj_event_mgr_t event_mgr;		/* event manager */
	opj_image_t *image = NULL;

	/*
	configure the event callbacks (not required)
	setting of each callback is optionnal
	*/
	memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
	event_mgr.error_handler = error_callback;
	event_mgr.warning_handler = warning_callback;
	event_mgr.info_handler = info_callback;

	/* set encoding parameters to default values */
	opj_set_default_encoder_parameters(&parameters);

	/* parse input and get user encoding parameters */
	if(parse_cmdline_encoder(argc, argv, &parameters) == 1) {
		return 0;
	}

	if(parameters.cp_comment == NULL) {
    const char comment[] = "Created by OpenJPEG version ";
		const size_t clen = strlen(comment);
    const char *version = opj_version();
/* UniPG>> */
#ifdef USE_JPWL
		parameters.cp_comment = (char*)malloc(clen+strlen(version)+11);
		sprintf(parameters.cp_comment,"%s%s with JPWL", comment, version);
#else
		parameters.cp_comment = (char*)malloc(clen+strlen(version)+1);
		sprintf(parameters.cp_comment,"%s%s", comment, version);
#endif
/* <<UniPG */

	}

	/* decode the source image */
	/* ----------------------- */

	switch (parameters.decod_format) {
		case PGX_DFMT:
			image = pgxtoimage(parameters.infile, &parameters);
			if (!image) {
				fprintf(stderr, " unable to load pgx file\n");
				return 1;
			}
			break;

		case PXM_DFMT:
			image = pnmtoimage(parameters.infile, &parameters);
			if (!image) {
				fprintf(stderr, " not a pnm file\n");
				return 1;
			}
			break;

		case BMP_DFMT:
			image = bmptoimage(parameters.infile, &parameters);
			if (!image) {
				fprintf(stderr, " not a bmp file\n");
				return 1;
			}
			break;
	}

	/* encode the destination image */
	/* ---------------------------- */

	if (parameters.cod_format == J2K_CFMT) {	/* J2K format output */
		int codestream_length;
		opj_cio_t *cio = NULL;
		FILE *f = NULL;

		/* get a J2K compressor handle */
		opj_cinfo_t* cinfo = opj_create_compress(CODEC_J2K);

		/* catch events using our callbacks and give a local context */
		opj_set_event_mgr((opj_common_ptr)cinfo, &event_mgr, stderr);

		/* setup the encoder parameters using the current image and user parameters */
		opj_setup_encoder(cinfo, &parameters, image);

		/* open a byte stream for writing */
		/* allocate memory for all tiles */
		cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0);

		/* encode the image */
		bSuccess = opj_encode(cinfo, cio, image, parameters.index);
		if (!bSuccess) {
			opj_cio_close(cio);
			fprintf(stderr, "failed to encode image\n");
			return 1;
		}
		codestream_length = cio_tell(cio);

		/* write the buffer to disk */
		f = fopen(parameters.outfile, "wb");
		if (!f) {
			fprintf(stderr, "failed to open %s for writing\n", parameters.outfile);
			return 1;
		}
		fwrite(cio->buffer, 1, codestream_length, f);
		fclose(f);

		/* close and free the byte stream */
		opj_cio_close(cio);

		/* free remaining compression structures */
		opj_destroy_compress(cinfo);

	} else {			/* JP2 format output */
		int codestream_length;
		opj_cio_t *cio = NULL;
		FILE *f = NULL;

		/* get a JP2 compressor handle */
		opj_cinfo_t* cinfo = opj_create_compress(CODEC_JP2);

		/* catch events using our callbacks and give a local context */
		opj_set_event_mgr((opj_common_ptr)cinfo, &event_mgr, stderr);			

		/* setup the encoder parameters using the current image and using user parameters */
		opj_setup_encoder(cinfo, &parameters, image);

		/* open a byte stream for writing */
		/* allocate memory for all tiles */
		cio = opj_cio_open((opj_common_ptr)cinfo, NULL, 0);

		/* encode the image */
		bSuccess = opj_encode(cinfo, cio, image, parameters.index);
		if (!bSuccess) {
			opj_cio_close(cio);
			fprintf(stderr, "failed to encode image\n");
			return 1;
		}
		codestream_length = cio_tell(cio);

		/* write the buffer to disk */
		f = fopen(parameters.outfile, "wb");
		if (!f) {
			fprintf(stderr, "failed to open %s for writing\n", parameters.outfile);
			return 1;
		}
		fwrite(cio->buffer, 1, codestream_length, f);
		fclose(f);

		/* close and free the byte stream */
		opj_cio_close(cio);

		/* free remaining compression structures */
		opj_destroy_compress(cinfo);

	}

	/* free user parameters structure */
  if(parameters.cp_comment) free(parameters.cp_comment);
	if(parameters.cp_matrice) free(parameters.cp_matrice);

	/* free image data */
	opj_image_destroy(image);

	return 0;
}
