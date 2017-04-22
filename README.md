# Clone, Build, and Test

```
$ git clone --recursive <url/to/tlocposix.git> # clone into tlocposix directory
$ mkdir tlocposixbuild
$ cd tlocposixbuild
$ cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Debug ../tlocposix
$ make
$ make test # run tests with make
$ ./tlocposix_test # run tests directly
```