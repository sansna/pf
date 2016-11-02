pf - print the buf we want!
=
Some times need to test open sources' structure by printing certain content to
screen, while some code are running in silent mode or as daemon... So here
comes the pf function..

Usage
-
Before doing anything, modifying pf.c: change the file destination..


In the source file include the pf.h file, and pf(identifier, buf); in the location we
want, and done..
