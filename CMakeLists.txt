#-------------------------------------------------
#
# Project created by QtCreator 2012-03-22T15:21:03
#
#-------------------------------------------------

#SET(CMAKE_C_COMPILER "clang")
#SET(CMAKE_CXX_COMPILER "clang++")

cmake_minimum_required(VERSION 2.6.1)
PROJECT(OCR-Demo1)

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

FILE(GLOB_RECURSE SOURCES *.cc)
FILE(GLOB_RECURSE HEADERS *.hh)
SET(QOBJECT_HEADER src/mainwindow.hh src/strokescene.hh src/charactersbar.hh)
#FILE(GLOB RESOURCES *.qrc)

#ADD_DEFINITIONS(-D__PALETTES_PATH__=${USRDIR}/palettes)
#ADD_DEFINITIONS(-D__PALETTES_PATH__=palettes)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "-O2 -march=native -Wall -std=c++11 -ftree-vectorize -fomit-frame-pointer")
SET(CMAKE_CXX_FLAGS_DISTRIBUTION "-O2 -Wall -std=c++11 -ftree-vectorize -fomit-frame-pointer")
SET(CMAKE_EXE_LINKER_FLAGS "")

QT4_WRAP_CPP(HEADERS_MOC "${QOBJECT_HEADER}")
#QT4_ADD_RESOURCES(RESOURCES_RCC "${RESOURCES}")

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(ocr-demo ${SOURCES}
                        ${HEADERS_MOC}
                        ${RESOURCES_RCC}
                        ${RC}
                )
TARGET_LINK_LIBRARIES(ocr-demo ${QT_LIBRARIES})
