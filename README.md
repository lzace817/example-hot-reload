# Hot Reloading Example in C
Simple example for hot reloading libraries in C.

## Quick start

``` Shell
$ ./build.sh
```

## Static library

```Shell
# compile
$ gcc -c target.c

# archive
$ ar rs libtarget.a target.o

# static link
$ gcc -L . main.c  -o main -static -ltarget
```

Note: `-static` will make all dependencies static.

## dynamic library

``` Shell
# compile
$ gcc -fPIC -c ../target.c

# generate shared object
$ gcc -shared target.o -o libtarget.so

# dynamic link
$ gcc -L . main.o -o main -ltarget
```

helper script can be used to run:
``` Shell
#!/bin/sh
export LD_LIBRARY_PATH=.
./main
```
Note: use
`nm -D libtarget.so`
 to inspect symbols.

# Hot (re)loading

1. create a function pointer the same as the desired function
2. load the library and import the symbol
3. close before reload.

``` C
void foo(int times);

// define Foo
typedef void (*Foo) (int times);

// open the shared object
void *handle = dlopen ("./libtarget.so", RTLD_LAZY);

// import the symbol
Foo hot_foo = (Foo) dlsym(handle, "foo");

// use
hot_foo(5);

// cleanup
dlclose(handle);
```

Don't link with the target library
``` Shell
# compile for hot reloading `libtarget.so`
$ gcc main.c -o main -ldl
```

`man dlopen`

# TOOLS

- ldd: print shared object dependencies.
- nm: list symbols: object files, archive library and shared library

---
# TODOS

- [ ] how to control which, static or dinamic linking will be done? Looks like both are linked with the same command.
	- from `Manual page gcc(1) line 13614/27615 54%`:                                                    Static libraries are archives of object files, and have file names
           like liblibrary.a.  Some targets also support shared libraries,
           which typically have names like liblibrary.so.  If both static and
           shared libraries are found, the linker gives preference to linking
           with the shared library unless the -static option is used.

- [ ]  discover how to search the .so file from curent path.
	-  quick dirty trick: `LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./main`
		-  add to the environment library path

---
# References

http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html

#compile #linking #c-programing #compiler-switches #gcc