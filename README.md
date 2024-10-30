## DNP3OutstationSimulator
Outstation simulator for DNP3 protocol based on opendnp3 and wxwidgets.

### Requirements:
* opendnp3: https://github.com/dnp3/opendnp3
* wxwidgets 3.2.x: https://wxwidgets.org
* cmake: https://cmake.org/
##### For Windows:
* MSBuild https://visualstudio.microsoft.com/pl/downloads/
* NSIS:  https://nsis.sourceforge.io/Main_Page
##### For Linux:
* g++-10 or newer

### Build for Windows:

* git clone https://bitbucket.org/roberto64/dnp3outstationsimulator
* cd dnp3outstationsimulator

#### wxWidgets
* https://github.com/wxWidgets/wxWidgets/releases/tag/v3.2.6
	(wxMSW-3.2.6_vc14x_x64_ReleaseDLL.7z,
	 wxMSW-3.2.6_vc14x_x64_Dev.7z,
	 wxWidgets-3.2.6-headers.7z)
* unpack to ../wx

#### opendnp3
* git clone https://github.com/dnp3/opendnp3 ../opendnp3
* Open Developer PowerShell for VS 2022
* cd ../opendnp3 (path to opendnp3)
* cmake -Wno-dev -S . -B build
* cmake --build build  --config Release

#### dnp3outstationsimpuator
* Open Developer PowerShell for VS 2022
* cd ../ (path to dnp3outstationsimulator)
* cmake -S . -B build
* cmake --build build --config Release

### Build for Linux:

* git clone https://bitbucket.org/roberto64/dnp3outstationsimulator
* cd dnp3outstationsimulator

#### wxWidgets
* apt install libwxgtk3.2-dev nsis

#### opendnp3
* git clone https://github.com/dnp3/opendnp3 ../opendnp3
* cd ../opendnp3
* cmake -Wno-dev -S . -B build
* cmake --build build --config Release

#### dnp3outstationsimpuator
* cd ../
* cmake -S . -B build
* cmake --build build --config Release

### Build the installation package:
* cd build
* (Linux) cpack -G DEB -C Release
* (Windows) cpack.exe -G NSIS64 -C Release
