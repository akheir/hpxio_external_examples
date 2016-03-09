# hpxio_external_examples

hpxio must be installed at same address as hpx to be able to compile this repo.

####hello_world.cpp
Creates a localfile component and writes Hello World in it.

####hello_world_agas.cpp
Creates a localfile component, registers the gid of that component in agas, then retrives the gid from agas and creates a new client for that component then the and writes Hello World in it.

####hello_world_server.cpp and hello_world_cleint.cpp
This is the interesting part. First hello_world_server runs, it Creates a localfile component, registers the gid of that component in agas then opens the file and wait for the client process to connect. The wait time can be specified by --wait=n 

The client connects to the running hpx runtime and queries the agas for gid of localfile component, then creates a new client for that component and then writes on the file and disconnects.
