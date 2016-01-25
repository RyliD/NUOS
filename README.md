# NUOS
CSC390 Operating Systems


- Installation Instructions for build on windows

[Installers Blake Used](https://onedrive.live.com/redir?resid=C9BED2494B9702A!63762&authkey=!ABqKlNe5m71Tu2A&ithint=file%2czip)
https://onedrive.live.com/redir?resid=C9BED2494B9702A!63762&authkey=!ABqKlNe5m71Tu2A&ithint=file%2czip

1. Install MinGW
    1. The version I used and included in the zip file is 0.6.2-beta-20131004-1 (mingw-get-setup.exe)

2. Run the MinGW Installation Manager

![Installation manager](https://github.com/RyliD/NUOS/blob/master/install.png)

3. Install the needed pieces
    1. I have no idea what is needed, but this is what I have:
    * mingw32-base              bin   2013072200
    * mingw32-binutils          bin   2.25.1-1
    * mingw32-gcc               bin   4.8.1-4
    * mingw32-gcc               dev   4.8.1-4
    * mingw32-gcc               lic   4.8.1-4
    * mingw32-gcc-g++           bin   4.8.1-4
    * mingw32-gcc-g++           dev   4.8.1-4
    * mingw32-gdb               bin   7.6.1-1
    * mingw32-libgcc            dll   4.8.1-4
    * mingw32-libgmp            dll   5.1.2-1
    * mingw32-libgomp           dll   4.8.1-4
    * mingw32-libiconv          dll   1.14-3
    * mingw32-libintl           dll   0.18.3.2-2
    * mingw32-libmpc            dll   1.0.2
    * mingw32-libmpfr           dll   3.1.2-2
    * mingw32-libpthread-old    dll   2.9.1-1
    * mingw32-libthreadgc       dll   2.9.1-1
    * mingw32-libquadmath       dll   4.8.1-4
    * mingw32-libssp            dll   4.8.1-4
    * mingw32-libstdc++         dll   4.8.1-4
    * mingw32-libz              dll   1.2.8-1
    * mingw32-make              bin   3.82.90-2-cvs-20120902
    * mingw32-mingw-get         bin   0.6.2-beta-20131004-1
    * mingw32-mingw-get         gui   0.6.2-beta-20131004-1
    * mingw32-mingw-get         lic   0.6.2-beta-20131004-1
    * mingw32-mingwrt           dev   3.21
    * mingw32-mingwrt           dll   3.21
    * mingw32-w32api            dev   3.17-2
    * msys-base                 bin   2013072300
    * msys-bash                 bin   3.1.23-1-msys-1.0.18
    * msys-bzip2                bin   1.0.6-1-msys-1.0.17
    * msys-core                 bin   1.0.18-1-msys-1.0.18
    * msys-core                 doc   1.0.18-1-msys-1.0.18
    * msys-core                 ext   1.0.18-1-msys-1.0.18
    * msys-core                 lic   1.0.18-1-msys-1.0.18
    * msys-coreutils            bin   5.97-3-msys-1.0.13
    * msys-diffutils            bin   2.8.7.20071206cvs-3-msys-1.0.13
    * msys-dos2unix             bin   7.3.2-1-msys-1.0.18
    * msys-file                 bin   5.04-1-msys-1.0.13
    * msys-findutils            bin   4.4.2-2-msys-1.0.13
    * msys-gawk                 bin   3.1.7-2-msys-1.0.13
    * msys-grep                 bin   2.5.4-2-msys-1.0.13
    * msys-gzip                 bin   1.3.12-2-msys-1.0.13
    * msys-libbz2               dll   1.0.6-1-msys-1.0.17
    * msys-libiconv             dll   1.14-1-msys-1.0.17
    * msys-libintl              dll   0.18.1.1-1-msys-1.0.17
    * msys-liblzma              dll   5.0.3-1-msys-1.0.17
    * msys-libmagic             dll   5.04-1-msys-1.0.13
    * msys-libminires           dll   1.02_1-2-msys-1.0.13
    * msys-libopenssl           dll   1.0.0-1-msys-1.0.13
    * msys-libpopt              dll   1.15-2-msys-1.0.13
    * msus-libregex             dll   1.20090805-2-msys-1.0.13
    * msys-libtermcap           dll   0.20050421_1-2-msys-1.0.13
    * msys-make                 bin   3.81-3-msys-1.0.13
    * msys-mintty               bin   1.0.3-1-msys-1.0.17
    * msys-openssh              bin   5.4p1-1-msys-1.0.13
    * msys-patch                bin   2.6.1-1-msys-1.0.13
    * msys-rsync                bin   3.0.8-1-msys-1.0.17
    * msys-sed                  bin   4.3.1-2-msys-1.0.13
    * msys-tar                  bin   1.23.-1-msys-1.0.13
    * msys-termcap              bin   0.20050421_1-2-msys-1.0.13
    * msys-texinfo              bin   4.13a-2-msys-1.0.13
    * msys-vim                  bin   7.3-2-msys-1.0.16
    * msys-wget                 bin   1.12-1-msys-1.0.13
    * msys-xz                   bin   5.0.3-1-msys-1.0.17
    * msys-zlib                 dll   1.2.7-1-msys-1.0.17
4. Wait for everything to download and install
    1. Everything will go into a forlder "C:\MinGW"
5. Install the ARM Compiler
    1. I included the installer I used in the zip file. (gcc-arm-none-eabi-4_7-2013q3-20130916-win32.exe)
    2. The arm stuff will install into “C:\Program Files (x86)\GNU Tools ARM Embedded\4.7 2013q3”
6. Update PATH variable
    1. I added 3 things:
        1. "C:\MinGW\msys\1.0\bin"
        2. "C:\MinGW\bin"
        3. "C:\Program Files (x86)\GNU Tools ARM Embedded\4.7 2013q3\bin"
     2.  PLEASE DONT BREAK YOUR PATH.  It is important for windows..
7. Pull the code.
8. Run make from the command line
