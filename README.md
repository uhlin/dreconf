# README #

## About ##

A small program to reconfigure a selection of Debian packages. The
target packages are read from a file and each line in the file is
passed to `dpkg-reconfigure` with given priority level.

If `dpkg-reconfigure` fails to reconfigure a package Dreconf won't be
interrupted because of that. Dreconf will continue with the next line
in the file.

## Cloning ##

To clone the repository use [Git](https://git-scm.com).

    $ git clone https://github.com/uhlin/dreconf.git

## Building and installing ##

    $ cd /path/to/source
	$ make
	$ sudo make install
