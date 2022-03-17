cmake_minimum_required(VERSION 3.0.0)

project(DNP3OutstationSimulator VERSION 1.1.1)

if (UNIX)
add_compile_options(-Wall)
endif (UNIX)

if (WIN32)
add_link_options(/SUBSYSTEM:WINDOWS)
set(wxWidgets_ROOT_DIR "${CMAKE_HOME_DIRECTORY}/../wx/")
set(RC resources/icons.rc)
endif (WIN32)

option(wxWidgets_USE_DEBUG OFF)

find_package(wxWidgets 3.0 COMPONENTS core base adv aui xml REQUIRED)

include_directories(../opendnp3/cpp/lib/include)
include(${wxWidgets_USE_FILE})
add_definitions(-DwxWidgets_DEFINITIONS -DVERSION="${PROJECT_VERSION}")

link_directories(../opendnp3/build/cpp/lib)

add_executable(${PROJECT_NAME} mapp.cpp frames.cpp mframes.cpp dnp3.cpp ${RC})
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} opendnp3)

string(TOLOWER ${PROJECT_NAME} PN)
set(CPACK_PACKAGE_FILE_NAME ${PN}-${PROJECT_VERSION})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "roberto@linux.pl")
set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_HOME_DIRECTORY}/resources/LICENSE-2.0.txt")
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
if (UNIX)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libwxgtk3.0-gtk3-0v5")
install(FILES resources/dnp3outstationsimulator.png DESTINATION share/icons/)
install(FILES resources/dnp3outstationsimulator.desktop DESTINATION share/applications/)
endif (UNIX)

include(CPack)
