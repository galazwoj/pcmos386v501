# This is the initial release of PC-MOS/386 v5.01; the latest released version. 

This tree:

* includes sources
* includes the executables
* will not include any intermediate files
* will remove duplicate source files
* includes the cdrom driver from Rod Roark (sources)
* maybe more

* does atm NOT include the borland compiler/tools --  the only program it requires from Borland is make as
Microsoft make is hopellesly lame.

See also.....  https://en.wikipedia.org/wiki/PC-MOS/386

This i a branch from the master repository

In concert with Gary Robertson and Rod Roark it has been decided to place all under GPL v3.
This does only apply to the PC-MOS/386/The Software Link inc/CDROM code. Does not apply for helper files that 
are included and publically available.
The PC-MOS386 v5.01 API itself has been documented in Ralf Brown's interrupt list.

http://www.cs.cmu.edu/~ralf/files.html

(and yes Roeland's name is still in the book as well...)

Tools used
Microsoft MASM 5.1
Microsoft C 5.1
Borland make (tested with make from Borland C++ 4.5)

Goals
No dependence on Borland
Investigate rsa lib
Clean the repository a bit
Do not disturb the master repo (so it is why this is a branched repo)

