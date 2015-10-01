# Introduction #

Operation Commando: ceinture & bretelle

Team:
  * Mickael Savinaud
  * Julien Malik
  * Julien Michel
  * Nicolas BERTRAND Avail june( end of ) / July
  * Manuel Grizonnet
  * Mathieu Malaterre. Avail.: July / ~4days
  * Antonin Descampe

Equipement
  * emacs or vi
  * night vision google (optional)

# Mission #

  1. ~~Fix remaining test tile decoders (ctest -R ttd)~~
  1. ~~Add several encoding tests to verify class-1 compliance~~
  1. incorporate diff into convert.c (j2k codecs)
  1. fix cinema test with extra byte
  1. ~~fix MJ2 to use new API ?~~
    * ~~copy/paste opj 1.5 branch~~
  1. ~~move JPIP code within openjpip / jpip directories~~
    * ~~move back jpip file level into openjp2~~
  1. ~~reorder libs/directory see [[FolderReorgProposal](FolderReorgProposal.md)]. cmake reorder/cleanup.~~
  1. ~~add ABI handling (gcc hidden stuff, dllexport for win32).~~ (need CFLAGS=-fvisibility=hidden)
  1. remove tabs (emacs/vi/sed). Use hjonshon uncrustify
  1. remove old v1 symbols
  1. rename symbols (remove `_v2` if any), preprend `opj_` to **everything**
  1. fix compilation with -Wsign-conversion -Wconversion
  1. ~~rename int.h/fix.h & j2k\_lib.h~~
  1. ~~openjpwl: need to use opj 1.5~~
  1. ~~fix callconv and function pointer~~
  1. what is the minimum cmake version required for openjpeg ? 2.8.2 or earlier ?
  1. release v2.0.0 !
  1. remove svn/branches/v2 !

## Sub-missions ##

| **filename** | **tasks** |
|:-------------|:----------|
| bio.h/.c     | why include stddef only in bio.h and not in opj\_include directly : For the moment we will keep as it |
| cio.c/.h	    | _remove cio~~(marked as deprecated)~~_|
|              | ~~**remove opj\_cio struct from openjpeg.h**~~|
| dwt.c/.h	    | clean comments and reorganize local/exported functions (style so later) -> ok|
| event./h 	   | ~~remove the old opj\_event\_msg~~ + **move the op\_event\_mgr struct t from openjpeg.h to event.h**|
| funtion\_list.c/.h	| ~~remove OPJ\_CALLCONV~~|
| image.h/.c	  | status of opj\_image\_create0. We can keep it until full opaque pointer is realized. see http://en.wikipedia.org/wiki/Opaque_pointer#C|
|              | rename opj\_image\_tile\_create /merge with opj\_image\_create|
| j2k.c	       | **2 TODO LH** + ~~TODO add invert.c~~ + clean/remove/adapt the dump fonctions ? + **TODO index management**|
| j2k.h	       | ~~remove opj\_tcp; opj\_cp; opj\_j2k and rename all v2 to the right name~~ + remove dump functions ?|
| jp2.c/.h	    | clean/remove/adapt the dump fonctions ? + ~~remove/rename opj\_jp2/opj\_jp2\_v2~~|
| jpt.c/.h	    | ~~remove non compatible with v2 style~~|
| mct.h/c	     | ok        |
| mqc.c/.h	    | ~~MQC\_PERF\_OPT~~ See [issue #182](https://code.google.com/p/openjpeg/issues/detail?id=#182) ? + opj\_mqc\_init\_enc why a difference in branch v2 (see [issue #183](https://code.google.com/p/openjpeg/issues/detail?id=#183))|
| openjpeg.c	  |           |
| opj\_clock.c/.h| 	ok       |
| pi.h	        | **change the opj\_pi\_iterator.first to opj\_bool**|
| pi.c 	       | ok        |
| raw.h/.c	    | ok        |
| t1.h	        | **clean opj\_t1 (remove opj\_common\_ptr)**|
| t1.c	        | ~~manage t1\_dec\_clnpass; t1\_dec\_clnpass\_step; t1\_dec\_clnpass\_step\_vsc;  t1\_dec\_clnpass\_step\_partial~~ + ~~compare t1\_getwmsedec and v2 version~~ + ~~remove warnings~~|
| t2.c/.h	     | **clean opj\_t2 (remove opj\_common\_ptr)**|
| tcd.c/.h	    | remove tcd dump ? Or adapt it|
| tgt.c	       | manage the frpintf ([issue #184](https://code.google.com/p/openjpeg/issues/detail?id=#184))|