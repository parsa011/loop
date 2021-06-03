# How do I build and run loop?
### Debian:
```sh
$ sudo apt install build-essential clang
```
### Arch:
```sh
$ sudo pacman -Sy base-devel clang  
```

## Clone Repository
```sh
$ git clone https://github.com/loop-lang/loop && cd loop
```

## Build and Run Loop
```sh
$ cmake . -B build 
$ cd build && make 
$ ./loopi <file>
# building tests
$ cmake . -B build -Dtests=on
```
