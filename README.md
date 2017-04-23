# tlocposix

A C library.

## Build Requirements

* CMake
* C11 development environment for which CMake can generate build files
* Unix-like environment (Linux, FreeBSD, Cygwin, etc.)

## Clone, Build, and Test

```
$ git clone --branch develop --recursive <url/to/tlocposix.git> # clone into tlocposix directory
$ mkdir tlocposixbuild
$ cd tlocposixbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tlocposix
$ make
$ make test # run tests with make
$ ./tlocposix_test # run tests directly
```
