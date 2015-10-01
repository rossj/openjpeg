# Roadmap for OpenJPEG #

## Short Term (within next 6-12 months) ##

  * Reintegrate branch 1.5 + fixed current issues:
    * malloc() / free() used in jpip code
    * openjpeg is not fixed-type safe (assumes int is 32bits)
  * Release 2.0
    * Merge of the v2-branch with the trunk
    * New folder organization and naming convention (see FolderReorgProposal)
    * code reformatting (see http://openjpeg.googlecode.com/svn/dev-utils/scripts/opj.cfg)
  * MJ2
    * make it compliant with v2 API
  * More tests for JPIP, MJ2 et JPWL
  * Large file compression (chunk by chunk) ?
    * testing ?
  * Large file decompression
    * testing ? -> kakadu provide a tool to merge different codestream into one big mosaic. so it should be easy to generate at least a fake giant file by assembling several times the same small file. See http://openjpeg.googlecode.com/svn/dev-utils/scripts/generate_big_files.sh
  * optimization ? which platform/OS ?
    * Win 7 32/64
  * bugs ? needs priority ?
    * See: http://code.google.com/p/openjpeg/issues/list?q=label:Milestone-Release2.0
  * fuzzing ?
    * only core for now
  * Documentation
    * Update Doxygen
    * Update MAN pages
    * Update --help option
  * Solve problems detected by Valgrind
  * Add OpenJPEG to the coverity scan and fix problems detected by the scan
  * Integrate OpenCinemaTools to the OpenJPEG project (http://code.google.com/p/opencinematools/). Marc Vandenbosch is ok with that.

## Long Term (more than a year) ##

  * JP3D ? (currently based on release 1.3)
    * testing !!
  * Support for JPEG 2000 part 2
  * Plugin Firefox
  * JPSec implementation
  * jasper binding ? prepare a jasper compatible API which calls openjpeg
  * Move to Mercurial/Git for Version Control (option available in GCode)

## JPWL ##
  * Workload: current JPWL code loads a whole codestream and operates on it in RAM, so it needs a reasonable amount of work to make it compatible with v2.
  * Current status: JPWL specifications have remained stable for several years, but there has not been a recent activity in the ISO group to improve its standardization status.
  * Time: we are interested in keeping a collaboration with openjpeg.
Currently, I have not enough time to comply with the June deadline. We
have a Ph.D. student who could be interested, but I think he is not ready
to produce stable code in few months, and needs more time.

So, my idea is not dropping at all JPWL, but working again on it, maybe
starting right from version 2 when it's final. I didn't dig recently in
the v2 branch, but I remember that it was easily extensible via sort of
plugins or personalized actions, so this could be the easy way to re-add
JPWL.