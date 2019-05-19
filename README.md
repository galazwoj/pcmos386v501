# This is the modified release of PC-MOS/386 v5.01; the latest released version. 

This tree:

* includes sources
* includes the executables
* will not include any intermediate files
* will remove duplicate source files
* includes the cdrom driver from Rod Roark (sources)
* maybe more

* does NOT include the borland compiler/tools --  the only program it requires from Borland is make as
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
* Microsoft MASM 5.1
* Microsoft C 5.1
* Borland make (tested with make from Borland C++ 4.5)
* Borland tlib as some versions of Microsoft lib does not work under Windows Vista or later versions of Windows

Goals
* No dependence on Borland C                 		(now exists only because make and tlib are used in some places)
* No dependence on Turbo Pascal 3.x 			(dependency removed)
* No dependence on Aztec C 5.2  			(this is for modem.exe, not sure if anyone still uses that)
* Reverse engineer source code of the rsa lib 		(done)
* Clean the source tree from duplicate or unused files
 