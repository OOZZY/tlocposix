# tlocposix

A C library.

## Build Requirements

* CMake
* C11 development environment for which CMake can generate build files
* Unix-like environment (Linux, FreeBSD, Cygwin, etc.)

## Clone, Build, and Test

Clone into tlocposix directory.

```
$ git clone --branch develop --recursive <url/to/tlocposix.git>
```

Build.

```
$ mkdir tlocposixbuild
$ cd tlocposixbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tlocposix
$ make
```

Run tests with make.

```
$ make test
```

Run tests directly.

```
$ ./tlocposix_test
```
