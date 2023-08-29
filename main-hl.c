#include <stdio.h>
#include <dlfcn.h>
#include "target-hl.h"

typedef struct {
    void *handle;
    Foo hot_foo;
} HotSO;

void loadFooFrom(HotSO *hso,char *libName)
{
    if(hso->handle != NULL) {
        if(dlclose(hso->handle)) {
            fprintf(stderr, "Error: %s\n",dlerror());
        }
        hso->handle = NULL;
        hso->hot_foo = NULL;
    }
    void *handle = dlopen (libName, RTLD_LAZY);
    if(handle != NULL) {
        Foo hot_foo = (Foo)dlsym (handle, "foo");
        if(hot_foo != NULL) {
            hso->handle = handle;
            hso->hot_foo = hot_foo;
            return;
        } else {
            fprintf(stderr, "Error: %s\n",dlerror());
        }
        dlclose(handle);
    } else {
        fprintf(stderr, "Error: %s\n",dlerror());
    }
}

int main()
{
    char buffer[4*1024];
    HotSO hso = {0};
    Foo hot_foo;

    loadFooFrom(&hso, "./build/libtarget-dec.so");
    hot_foo = hso.hot_foo;
    hot_foo(17, 0.123, buffer);
    printf("%s\n", buffer);

    loadFooFrom(&hso, "./build/libtarget-bin.so");
    hot_foo = hso.hot_foo;
    hot_foo(17, 0.123, buffer);
    printf("%s\n", buffer);

    return 0;
}