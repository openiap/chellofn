## C hello world example on how to listen on a message queue and respond to messages

```
https://github.com/openiap/chellofn.git
```

# getting started
compile and run in debug mode

make will automaticly download clib_openiap.h and binary for current platform, if you cannot use make you need to, go to [rustapi](https://github.com/openiap/rustapi/releases) and download library for your platform and place them in the lib folder, and rename it to libopeniap_clib.so


```bash

setup default credentials
```bash
export apiurl=grpc://grpc.app.openiap.io:443
# username/password
export OPENIAP_USERNAME=username
export OPENIAP_PASSWORD=password
# or better, use a jwt token ( open https://app.openiap.io/jwtlong and copy the jwt value)
export OPENIAP_JWT=eyJhbGciOiJI....
```

```bash
make && ./hello_client
# or with gcc directly
gcc main.c -Llib -lopeniap-linux-x64 -Wl,-rpath=lib -o hello_client && ./hello_client

# to static linked, use
make STATIC=1 && ./hello_client

# using nixos? Then path will be break inside docker, so we can use patchelf to "fix" it
make dockerbuild
```
