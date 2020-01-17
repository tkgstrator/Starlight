# Starlight
An enviroment for linking to Splatoon 2 executable and implementing hooks.

# Active contributors
[@shibbo](https://github.com/shibbo) - Repo based on their work on OdysseyReversed

[@Thog](https://github.com/Thog) - Expertise in how rtld is implemented

[@3096](https://github.com/3096) - Expertise in Splatoon 2's inner workings

[@khang06](https://github.com/khang06) - Expertise in Splatoon 2's inner workings

[@OatmealDome](https://github.com/OatmealDome) - Expertise in Splatoon 2's inner workings

[@Random0666](https://github.com/random0666) -  Expertise in Splatoon 2's inner workings

# Installation

For Ubuntu 16.04 / 18.04 on WSL(Windows Subsystem for Linux)

## devkitpro

```bash
wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb
sudo dpkg -i devkitpro-pacman.deb
```

```bash
vi ~/.bash_profile
```
add system environment.
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=${DEVKITPRO}/devkitARM
export DEVKITPPC=${DEVKITPRO}/devkitPPC
export PATH=${DEVKITPRO}/tools/bin:$PATH
```
apply it.
```bash
source ~/.bash_profile
```
download database.
```bash
dkp-pacman -Sy switch-dev
```
and press enter.

## Python3.7

If you use ubuntu 16.04, you should add repository.

```bash
sudo apt update
sudo apt install software-properties-common
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt update
sudo apt install python3.7
```

## keystone

```bash
sudo apt install libssl-dev cmake g++ python3.7 python3-pip
pip install keystone
```
build keystone in about 3-5 minutes.

### keystone-engine

```bash
git clone https://github.com/keystone-engine/keystone.git
cd keystone
mkdir build
cd build
../make-share.sh
sudo make install
sudo ldconfig
cd ../bindings/python
sudo make install3
```

## libnx

```bash
git clone https://github.com/switchbrew/libnx
cd libnx
vi nx/source/runtime/switch_crt0.s
```
edit line 93.
```
// before
.word  0 // "offset to runtime-generated module object" (neither needed, used nor supported in homebrew)

// after
.word  __nx_module_runtime  - __nx_mod0
```
make & install.
```bash
make
sudo make install DEVKITPRO=/opt/devkitpro
```

## Starlight

```bash
git clone https://github.com/tkgstrator/Starlight.git
cd Starlight
git checkout wip-menu
make
```

# Credits
0CBH0 - nsnsotool

libnx - Makefile creation
