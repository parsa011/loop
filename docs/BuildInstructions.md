# How do I build and run loop?
## Prerequisites
Make sure, you installed the requirements for clang and make.

### Debian:
```shell
sudo apt install build-essential clang
```
### Arch:
```shell
sudo pacman -Sy base-devel clang  
```

## Clone Repository
```shell
git clone https://github.com/loop-lang/loop && cd loop
```

## Build and Run Loop
```shell
make
./loop examples/exampleClass.loop
```