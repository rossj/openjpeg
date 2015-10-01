# Introduction #

OpenJPEG is maintained using SVN

## SVN ##

### svn commit message ###

Commit message should contains the branch it is commited to. Eg, on branch openjpeg-1.5 the commit message should read:
```
[1.5] fix invalid write access in j2k_foo
```
svn commit message are very important. They will be used to generate automatically the CHANGES file. See [genchanges.sh](http://openjpeg.googlecode.com/svn/dev-utils/scripts/genchange.sh).

when doing a svn merge from say branch 1.5 onto trunk, svn will create a new message. It will not contains the original commit log, therefore you will still need to prefix your message with

```
[trunk] merge from stable branch to fix invalid write access
```

### Integration with version control ###

  * http://code.google.com/p/support/wiki/IssueTracker#Integration_with_version_control

## GIT-SVN ##

Because DVCS are easier to work with when it comes to merging/branching. Some people might enjoy the benefits of GIT over the OpenJPEG SVN:

### cloning ###

```
$ git svn clone https://openjpeg.googlecode.com/svn/ -T trunk -b branches -t tags
$ git svn show-ignore >> .git/info/exclude
```

### workflow ###

As per documentation of git-svn one should avoir git merge. Some people have documented ways to use git merging still:
**http://www.pauldeden.com/2009/09/merging-branch-with-git-svn-and-still.html?showComment=1313021208783#c3713765550508885198**

In our case we will use something simple. Let's pretend we want to merge some stuff from 1.5 branch onto master (trunk)

Check what are the diff for say doc subir:
```
$ git diff openjpeg1.5..master doc | less
```
Create
```
$ git checkout master
$ git checkout -b my_merge_branch_doc
$ git mv ...
$ git commit
HACK HACK
$ git commit
$ git checkout master
$ git merge --squash my_merge_branch_doc
# squash message will contains all your commit log. Simplify it to a single -future- svn commit log:
$ git commit
```
Make sure we are up to date with trunk
```
$ git svn rebase
$ git svn dcommit
```

## Some experimental tips about Mercurial-SVN ##
For the same main reason, some people might enjoy the benefits of Mercurial over the OpenJPEG SVN. A mercurial extension do the job perfectly : [HgSubversion](http://mercurial.selenic.com/wiki/HgSubversion).

You can clone trunk repository from the svn with:
```
$ hg clone svn+https://openjpeg.googlecode.com/svn/trunk
```
and enjoy the possibility the make local commit before push your modifications. Take care to use the following command before all push action:
```
$ hg pull --rebase
```
It will be rebase locally your local modifications on the top of the current server version.

An another interesting extension available with mercurial is the [Histedit](http://mercurial.selenic.com/wiki/HisteditExtension) extension which enable to modify your local history after commit operation. It is useful when you don't want keep some commits in your local history before pushing to the svn repository.

## svnsync ##

Sometimes it is useful to have a local copy of OpenJPEG SVN. In which case you could follow steps from: https://www.coderesort.com/about/wiki/HowTo/Subversion/SvnSync.

In summary:
# $ cd /tmp
# $ svnadmin create openjpeg\_local
# $ echo '#!/bin/sh' > ./openjpeg\_local/hooks/pre-revprop-change
# $ chmod +x ./openjpeg\_local/hooks/pre-revprop-change
# $ svnsync initialize [file:///tmp/openjpeg_local/](file:///tmp/openjpeg_local/) http://openjpeg.googlecode.com/svn/trunk/
# $ svnsync sync [file:///tmp/openjpeg_local/](file:///tmp/openjpeg_local/)