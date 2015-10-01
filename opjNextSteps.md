# Version 1.X #
  1. Fix possible issues related to recent changes made on cmake and autotools. Ensure that both building methods are in sync.
  1. Update project files for XCode and VisualStudio.
  1. Provide Makefile.osx, in the same vein as Makefile.nix
  1. Test and apply remaining patches provided by contributors.
  1. Release openjpeg-1.4 binaries. I can provide OSX and Linux (Ubuntu32) binaries but would need help for win32 binaries. Maybe other binaries would be interesting to build, your thoughts are welcome.

Once 1.4 binaries are released, main development efforts should focus on v2 branch.

# Version 2.X #
  1. Add autotools support as in 1.X and ensure cmake and autotools are in sync
  1. Fix bugs and improve v2 until it gets same or higher robustness and efficiency as 1.X, except for JPWL support which is currently not envisioned to be brought to v2.
  1. Once v2 is mature enough, make v2 the main svn trunk and put 1.X as a branch.

# Testing #
Update and improve the tests being made through CTest. I still have to provide a list of relevant images and tests. A nice feature would be to be able to compare a hash of each (de)compressed image to a reference hash, so as to ensure that changes made to the library do not alter the image quality. This had been done by François Devaux (OPJvalidate tool) but would be great to have it integrated in the CDash system.

# Documentation / Website #
  1. Update the documentation:
    * Doxygen
    * Man pages
    * Online documentation
  1. Update www.openjpeg.org and move all relevant information to googlecode page