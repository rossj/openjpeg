# Introduction #

Operation Commando: It's alive !

Team:
  * Mathieu Malaterre
  * Antonin Descampe (?)

# Mission #

  1. Correct [issue #80](https://code.google.com/p/openjpeg/issues/detail?id=#80) & [issue #230](https://code.google.com/p/openjpeg/issues/detail?id=#230). (backport branch 1.5).
  1. ~~Import security patches (debian) :~~
    1. ~~http://patch-tracker.debian.org/package/openjpeg/1.3+dfsg-4.7~~
  1. ~~Import ghoscripts (sumatrapdf?) patch  (#235, #236, #237, #238 and al.). branch 1.5 backport ?~~
  1. ~~Finalize API openjpeg v2. Check FILE API.~~
  1. ~~New images for conformance tests~~
    1. ~~Add JP2 file~~
  1. ~~New images for non-regression tests :~~
    1. ~~Kakadu stress tests~~
    1. ~~Richter subsampling tests,~~
  1. ~~Add PEAK/MSE on TIFF images. (See JP2 files).~~
  1. ~~Deactivate tests conformance Class-0 for now,~~
  1. Update messages -help
  1. Suggest reference indentation.
  1. ~~bugs triaging.~~
  1. Dashboard Maintenance :
    1. ~~fix warnings/errors~~
    1. ~~Deactivate old (non working) config~~
    1. Checks tests output, in particular valgrind output
  1. Produce OpenJPEG 2.1.0
    1. New CPack options to generate `light` version of OpenJPEG (Part 1 only)

# Information #

How to track issues changes since 19/2/2014:

  * http://code.google.com/p/openjpeg/issues/list?can=2&q=modified-after%3A2014%2F2%2F19

How to track issues remaining before 2.1 release:

  * http://code.google.com/p/openjpeg/issues/list?q=milestone=Release2.1