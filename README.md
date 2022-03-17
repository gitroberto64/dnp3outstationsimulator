## DNP3OutstationSimulator
Outstation simulator for DNP3 protocol based on opendnp3 and wxwidgets.

### Requirements:
* opendnp3: https://github.com/dnp3/opendnp3
* wxwidgets 3.0.5: https://wxwidgets.org
* cmake: https://cmake.org/
##### For Windows:
* Visual Studio 2019
* NSIS:  https://nsis.sourceforge.io/Main_Page
##### For Linux:
* g++-10 or newer

### Build for Windows:

* git clone https://bitbucket.org/roberto64/dnp3outstationsimulator
* cd dnp3outstationsimulator

#### wxWidgets
* unpack to ../wx
* Compile by Visual Studio 2019 (build/msw)

#### opendnp3
* git clone https://github.com/dnp3/opendnp3 ../opendnp3
* cd opendnp3
* cmake -S . -B build
* cmake --build build

#### dnp3outstationsimpuator
* cd ../
* cmake -S . -B build
* cmake --build build

### Build for Linux:

* git clone https://bitbucket.org/roberto64/dnp3outstationsimulator
* cd dnp3outstationsimulator

#### wxWidgets
* apt install libwxgtk3.0-gtk3-dev

#### opendnp3
* git clone https://github.com/dnp3/opendnp3 ../opendnp3
* cd opendnp3
* cmake -S . -B build
* cmake --build build

#### dnp3outstationsimpuator
* cd ../
* cmake -S . -B build
* cmake --build build

### Install:
* cd build
* (Linux) cpack -G DEB -C Release
* (Windows) cpack.exe -G NSIS64 -C Release