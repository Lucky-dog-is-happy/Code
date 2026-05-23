gcc extern1.c -o libfunc.so -shared -fPIC
g++ extern2.c -o extern -lfunc -L. -Wl,-R,.
