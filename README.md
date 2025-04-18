# Magisk-Module-with-clang20
This repository contains a Magisk Module with **clang 20** for **arm64** CPUs

This Magisk module contains the binaries from **clang version 20**, **GNU make**, **pkg-config**, **pkgconf**, and the files from the Android **NDK r29-beta1** necessary to compile libraries and binaries for arm64 CPUs.


To create the ZIP file with the Magisk Module, clone or download the repository and execute the script
```
./create_zip.sh 
```
from the repository


**Short documentation for the Magisk Module with clang 20**

After installing the Magisk Module, the **clang20** files are located in the directory 

**/system/usr/clang20**

The **clang20**, **make**, **pkg-config**, and **pkg-conf** binaries are in the directory

**/system/usr/clang20/bin**

The files from the NDK are in the directory

**/system/usr/ndk/r29-beta1**

The sysroot from the NDK is in the directory

**/system/usr/ndk/r29-beta1/sysroot**


Use 
```
. /system/bin/init_clang20_env
```
to init the environment for the **clang20**. This scripts defines all necessary environment variables (including the PATH variable) to use the clang.


Source Code used to create the binaries
---------------------------------------

The repository with the source code for the clang is:

[https://android.googlesource.com/toolchain/llvm-project](https://android.googlesource.com/toolchain/llvm-project)

The source code was checked out in **04/2025**


To get the source for clang20 use these commands: 
```
git clone https://android.googlesource.com/toolchain/llvm-project

cd llvm-project

git checkout llvm-r547379-release
```

See the file 

**source/myconfigure** 

in the Magisk Module for the cmake options used to prepare the build process for the **clang20**.
The **clang20** binaries were compiled on a machine running the Linux OS with Cross Compiler from the **Android NDK r27b**.


The Android NDKs are available here:

[https://developer.android.com/ndk/downloads](https://developer.android.com/ndk/downloads)


The source code for the **make** binary is available here:

[https://ftp.gnu.org/gnu/make/](https://ftp.gnu.org/gnu/make/)


The source code for **pkg-config** is available here:

[https://pkgconfig.freedesktop.org/releases/](https://pkgconfig.freedesktop.org/releases/)


The source code for **pkgconf** is available here

[https://github.com/pkgconf/pkgconf](https://github.com/pkgconf/pkgconf)
