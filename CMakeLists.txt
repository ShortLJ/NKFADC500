#MakeLists.txt for event package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(NKFADC500GUI)

# You need to tell CMake where to find the ROOT installation. This can be done in a number of ways:
#   - ROOT built with classic configure/make use the provided $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS Core RIO Net Hist Graf Graf3d Gpad Tree Rint Postscript Matrix Physics MathCore Thread Spectrum Minuit Gui)

include(${ROOT_USE_FILE})

include_directories(
${ROOT_INCLUDE_DIRS}
${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/src
#/usr/local/Cellar/libusb/1.0.21/include/libusb-1.0
)

link_directories(
/usr/local/Cellar/libusb/1.0.21/lib
)

add_definitions(${ROOT_CXX_FLAGS})

ROOT_GENERATE_DICTIONARY(NoticeFADC500IBSROOTDict
${CMAKE_SOURCE_DIR}/include/NoticeFADC500IBS.h
${CMAKE_SOURCE_DIR}/include/NoticeFADC500IBSROOT.h
LINKDEF ${CMAKE_SOURCE_DIR}/include/NoticeFADC500IBSROOTLinkDef.h
)

ROOT_GENERATE_DICTIONARY(NoticeTCBIBSROOTDict
${CMAKE_SOURCE_DIR}/include/NoticeTCBIBS.h
${CMAKE_SOURCE_DIR}/include/NoticeTCBIBSROOT.h
LINKDEF ${CMAKE_SOURCE_DIR}/include/NoticeTCBIBSROOTLinkDef.h
)

ROOT_GENERATE_DICTIONARY(NKUSBROOTDict
${CMAKE_SOURCE_DIR}/include/NKUSBROOT.h
LINKDEF ${CMAKE_SOURCE_DIR}/include/NKUSBROOTLinkDef.h
)

ROOT_GENERATE_DICTIONARY(nkusbDict
${CMAKE_SOURCE_DIR}/include/nkusb.hh
)

ROOT_GENERATE_DICTIONARY(usb3comrootDict
${CMAKE_SOURCE_DIR}/include/usb3com.h
${CMAKE_SOURCE_DIR}/include/usb3comroot.h
LINKDEF ${CMAKE_SOURCE_DIR}/include/usb3comrootLinkDef.h
)

ROOT_GENERATE_DICTIONARY(usb3tcbrootDict
${CMAKE_SOURCE_DIR}/include/usb3tcb.h
${CMAKE_SOURCE_DIR}/include/usb3tcbroot.h
LINKDEF ${CMAKE_SOURCE_DIR}/include/usb3tcbrootLinkDef.h
)

ROOT_GENERATE_DICTIONARY(NKFADC500GUIDict
${CMAKE_SOURCE_DIR}/include/FADC500setting.h
${CMAKE_SOURCE_DIR}/include/FADC500run.h
${CMAKE_SOURCE_DIR}/include/FADC500gui.h
)

set(HEADER_FILES 
${CMAKE_SOURCE_DIR}/include/nkusbconst.hh
)

#---Create a shared library with geneated dictionary
add_library(NKFADC500GUI SHARED
${CMAKE_SOURCE_DIR}/src/NoticeFADC500IBS.cc
${CMAKE_SOURCE_DIR}/src/NoticeFADC500IBSROOT.cc
NoticeFADC500IBSROOTDict.cxx

${CMAKE_SOURCE_DIR}/src/NoticeTCBIBS.cc
${CMAKE_SOURCE_DIR}/src/NoticeTCBIBSROOT.cc
NoticeTCBIBSROOTDict.cxx

${CMAKE_SOURCE_DIR}/src/NKUSBROOT.cc
NKUSBROOTDict.cxx

${CMAKE_SOURCE_DIR}/src/nkusb.cc
nkusbDict.cxx

${CMAKE_SOURCE_DIR}/src/usb3com.cc
${CMAKE_SOURCE_DIR}/src/usb3comroot.cc
usb3comrootDict.cxx

${CMAKE_SOURCE_DIR}/src/usb3tcb.cc
${CMAKE_SOURCE_DIR}/src/usb3tcbroot.cc
usb3tcbrootDict.cxx

${CMAKE_SOURCE_DIR}/src/FADC500setting.cc
${CMAKE_SOURCE_DIR}/src/FADC500run.cc
${CMAKE_SOURCE_DIR}/src/FADC500gui.cc
NKFADC500GUIDict.cxx
)

target_link_libraries(NKFADC500GUI ${ROOT_LIBRARIES} usb-1.0)
