# How do I build and run loop?
## Prerequisites
Make sure, you installed the requirements for clang and make.

### Debian:
```sh
sudo apt install build-essential clang
```
### Arch:
```sh
sudo pacman -Sy base-devel clang  
```

## Clone Repository
```sh
git clone https://github.com/loop-lang/loop && cd loop
```

## Build and Run Loop
```sh
make
./loop examples/exampleClass.loop
```