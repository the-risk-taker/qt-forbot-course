# Qt Course for Forbot

This repository contains the source code for all examples and programs from my [Qt course on Forbot](https://forbot.pl/blog/kurs-qt-1-czym-jest-qt-pierwsza-aplikacja-w-praktyce-id35549) [written in Polish]. The course main parts:

1. About Qt, first program
2. Serial communication (UART) between desktop and Arduino dev board
3. First mobile application in Qt for Android
4. Bluetooth communication between smartphone and Arduino dev board with Bluetooth Classic module
5. Building interfaces with Qt Quick and QML
6. Passing data between C++ <-> QML
7. Intro to concurrent processing in Qt
8. Intro to multithreading in Qt
9. Intro to multitasking in Qt

[Forbot](https://forbot.pl/blog/) is the most popular robotics forum in Poland, regularly publishing guides for electronics and DIY enthusiasts who are passionate about building electronic devices on their own.

## Requirements

Install [Qt](https://www.qt.io/download-open-source) with additional libraries: `Qt Serial Port` and `Qt Bluetooth`.

## Setting up, building and running examples

The easiest way to set up, build, and run the examples is by opening the root `CMakeLists.txt` in QtCreator.

Alternatively, use the command line, for example:

```shell
cmake -S . -B build -DCMAKE_PREFIX_PATH=/home/mateusz/Qt/6.8.1/gcc_64
cmake --build build --parallel
```

> [!IMPORTANT]
> Mind providing a valid `CMAKE_PREFIX_PATH` with the location of Qt build for a specific toolchain
