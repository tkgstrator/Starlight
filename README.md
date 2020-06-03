# Starlight

An enviroment for linking to Splatoon 2 executable and implementing hooks.

## Active contributors
[@shibbo](https://github.com/shibbo) - Repo based on his works on OdysseyReversed

[@Thog](https://github.com/Thog) - Expertise in how rtld is implemented

[@3096](https://github.com/3096) - Expertise in Splatoon 2's inner workings

[@khang06](https://github.com/khang06) - Expertise in Splatoon 2's inner workings

[@OatmealDome](https://github.com/OatmealDome) - Expertise in Splatoon 2's inner workings

[@Random0666](https://github.com/random0666) -  Expertise in Splatoon 2's inner workings

## Requirements
For Ubuntu 18.94 on WSL2(Windows Subsystem for Linux 2) or native like Linux operating system.

 - Ubuntu 18.04 (with Python3)
 - Windows 10 (above build id 18917)
 - Unpatched Nintendo Switch (enable FTP over port 5000)
 - Splatoon 2 v1441792(3.1.0) (Any region) 
   - Otherwise pseudo 3.1.0 using LFS(Layered File System) [Ref: below article]
   
> [How to get Starlight works for Splatoon 2 on any version.(Japanese)](https://tkgstrator.work/?p=27445)


# Installation for Windows

If you want to build Starlight on native Ubuntu 18.04, skip this section.

## Enable Windows Subsystem for Linux

First, you should check that Windows system meets the requirements. Run Command Prompt and type `ver`, press enter.

```
C:\Users\devonly>ver
Microsoft Windows [Version 10.0.19628.1]
```

In case, build is is 19628 which grater than 18917 (requirement).

Run Command Prompt as Administrator.

`dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart`

and restart Windows.

## Install Ubuntu 18.04

Click the link below and install Ubuntu 18.04 on Windows 10.

[Ubuntu 18.04 Microsoft Store](https://www.microsoft.com/store/apps/9N9TNGVNDL3Q)

## Convert WSL1 to WSL2

Run Command Prompt as Administrator.

```
C:\Users\devonly>wsl -l -v
  NAME                   STATE           VERSION
* docker-desktop-data    Running         2
  Ubuntu-18.04           Running         1 <=== WSL1
  docker-desktop         Running         2
```

Convert WSL1 to WSL2 (It'll take about 3-5 mins).

```
C:\Users\devonly>wsl --set-version Ubuntu-18.04 2
Conversion in progress, this may take a few minutes...
Conversion complete.
```

Type the command again to check it.

```
C:\Users\devonly>wsl -l -v
  NAME                   STATE           VERSION
* docker-desktop-data    Running         2
  Ubuntu-18.04           Running         2 <=== WSL2
  docker-desktop         Running         2
```

If you want, change the dafult version of WSL to 2 (for a better experience).

```
C:\Users\devonly>wsl --set-default-version 2
For information on key differences with WSL 2 please visit https://aka.ms/wsl2
```

## Install Docker Desktop for Windows

Click below link and download installer, install Docker Desktop for Windows.

[Docker Desktop for Windows](https://hub.docker.com/editions/community/docker-ce-desktop-windows)

To enable WSL2 integration, you'll need to turn on some features in Settings.

 - Settings->General
   - Check `Use the WSL2 based engine`
- Settings->Resources->WSL INTEGRATION
   - Check `Enable integration with my default WSL distro`
   - Enable `Ubuntu-18.04`

# Installation for Ubuntu 18.04

Install Python3 to be able to send IPS patch and subsdk0 to Nintendo Switch.

```bash
sudo apt update
sudo apt upgrade
sudo apt install -y python3 make
```

Clone Starlight.

```bash
git clone https://github.com/tkgstrator/Starlight.git
cd Starlight
make
```

## Configurations

To apply your environment, you should edit Makefile(i.e `vi Makefile`)

```makefile
# TODO (Khangaroo): Make this process a lot less hacky (no, export did not work)
# See MakefileNSO

.PHONY: all clean starlight install 

S2VER ?= 310 # Splatoon 2 version (Do not change)
S2VERSTR ?= 3.1.0 # Splatoon 2 version's strings (Do not change)
S2ROMTYPE ?= TrialUS20 # Splatoon 2 region
IP ?= 192.168.0.22 # IP address for Nintendo Switch 
```

|  Region  |  RomType |    Title ID    |
|   :--:   |   :--:   |      :--:      |
|    JP    |JP Product|01003C700009C000|
|    US    |US Product|01003BC0000A0000|
|    EU    |EU Product|0100F8F0000A2000|
|   EveJP  |JP Premiere|0100D070040F8000|
|   EveUS  |US Premiere|01003870040FA000|
|   EveEU  |EU Premiere|010086F0040FC000|
|TrialJP   |US Demo '19|Not supported|
|TrialUS   |US Demo '19|01006BB00D45A000|
|TrialEU   |US Demo '19|Not supported|
|TrialJP20 |JP Demo '20|0100998011330000|
|TrialUS20 |US Demo '20|01002120116C4000|
|TrialEU20 |EU Demo '20|01009240116CC000|
|ShowFloor |N/A|Not supported|
|ShowDL |Testfire|010000A00218E000|

## Commands

```bash
make # Build Starlight by Docker container
make clean # Only supported for Docker container
make starlight # Only supported for Docker container
make install # Build Starlight, send IPS patch and subsdk0 to Nintendo Switch (Recommend)
```

## Specail thanks

[@shadowninja108](https://twitter.com/shadowninja108) - Expertise in Splatoon 2's inner workings

[@container12345](https://twitter.com/container12345) - Reverse engineering for Game::Coop classes

# Credits
0CBH0 - nsnsotool

libnx - Makefile creation


