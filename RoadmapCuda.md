# Introduction #

GSoC 2012 did produce some nice optimized CUDA code for OpenJPEG:
https://gitorious.org/~aditya12agd5/openjpeg-optimization/aditya12agd5s-openjpeg-optimization

This page will describe the steps to integrate this branch into svn/trunk

# Participants #

  * Mathieu Malaterre
  * ?

# Details #

  1. Create cuda subdirectory in src/lib/openjp2
  1. Move all cuda-related code within this directory
  1. add new compile time CUDA option (cmake)
  1. rename cuda wrapper function to have `opj_` prefix (just in case)
  1. start compiling as compile time option
  1. add new runtime option to select in between CPU based alg and GPU based
  1. Ship OpenJPEG 2.2 !

We should try to minimize any API break !

# Bugs #

  1. On hold because of: http://cmake.org/Bug/view.php?id=13824