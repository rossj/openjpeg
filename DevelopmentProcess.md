## Versioning rules ##
_OpenJPEG version (MAJOR.MINOR.MICRO)_

  * MAJOR incremented in case of API break (MINOR and MICRO set to 0),
  * MINOR incremented in case of API addition (MAJOR unchanged, MICRO set to 0),
  * MICRO incremented in case of bugfixes not impacting the API (MAJOR, MINOR unchanged).


## Tags and branches ##
Based on the current development pace of OpenJPEG, the following use of branches and tags is proposed:

  * The trunk always corresponds to the version in development.
  * When an API break is scheduled (new major version) and is started being developed, a branch is created just before breaking the API. This newly created branch will host all subsequent bugfixes applying to the old major version.
  * When an API is added or bugfixes not impacting the API are made, no new branch is created.
  * When a new version (major, minor or micro) is released, a tag is created in the corresponding branch (or in the trunk if it concerns the version in development).

In summary, branching would be used only in case of a future major release.

Concerning the current state of the SVN, we are in the process of merging the v2 branch with the trunk. Just before committing the changes, we'll create a new branch to host release 1.5 and future 1.5.x releases. After the merge, the v2 branch will become obsolete and all development should be done in the trunk.

## Dev Process ##

### Bug Fix ###

Merge bug fix to say 1.5n then merge to trunk

### Dev (new funcs) ###

1.5 is frozen. No new code should be merged there.
Directly to trunk

Need to add new functions into 'CHANGES' file.

Need to find a way to present changes. svn2cl ?