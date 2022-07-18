# Kheperon Server

gRPC server for libkhepera

## Supported features

- Config enumeration
  + section
  + device

## Build instructions

### gRPC Server

**Warning:** To build protobuf and gRPC, you will need GCC >= 6 which is more
recent than the official K-Team toolchain. Check out
[crosstool-ng](https://crosstool-ng.github.io) to build your toolchain with the
right options.

To compile the gRPC server for the Khepera IV robot, use a CMake toolchain file
with the paths to your ARM compiler. 

```
cmake -Bbuild_kheperaiv . -DCMAKE_TOOLCHAIN_FILE=my-toolchain.cmake
cmake --build build_kheperaiv --parallel
```

By default, only the gRPC server is built. To build a client that can run on
the Khepera, append `-DKHEPERON_ENABLE_CLIENT=ON` to your cmake invocation.

### gRPC Test client

To build the test client on your host machine, 

```
cmake -Bbuild_pc .
cmake --build build_pc
```

## Running Kheperon

First launch the server on the Khepera IV

```
scp build_kheperaiv/kheperon-server root@<your_robot_ip>:
ssh -L 50051:localhost:50051 root@<your_robot_ip>
./kheperon-server
```

Then you can use the test client on your PC and run requests against the server

```
./build_pc/kheperon-client
```
