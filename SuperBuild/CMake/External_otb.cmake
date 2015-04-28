set(proj OTB)

if(NOT __EXTERNAL_${proj}__)
set(__EXTERNAL_${proj}__ 1)

message(STATUS "Setup OTB...")

SETUP_SUPERBUILD(PROJECT ${proj})
message(STATUS "  Using OTB SuperBuild version")

if(SUPERBUILD_IN_OTB_TREE)
  set(OTB_SB_SRC ${CMAKE_SOURCE_DIR}/..)
endif()

set(${proj}_ADDITIONAL_CACHE)

#set(BUILD_EXAMPLES ON)

if(ENABLE_OTB_LARGE_INPUTS)
  set(OTB_SB_LARGEINPUT_CONFIG 
    -DOTB_DATA_USE_LARGEINPUT:BOOL=ON
    -DOTB_DATA_LARGEINPUT_ROOT:PATH=${OTB_DATA_LARGEINPUT_ROOT}
    )
else()
  set(OTB_SB_LARGEINPUT_CONFIG 
    -DOTB_DATA_USE_LARGEINPUT:BOOL=OFF
    )
endif()

set(${proj}_DEPENDENCIES
    GDAL
    OSSIM
    ITK
    TINYXML
    BOOST
    )

if(OTB_USE_CURL)
  list(APPEND ${proj}_DEPENDENCIES CURL)
endif()

if(OTB_USE_LIBKML)
  list(APPEND ${proj}_DEPENDENCIES LIBKML)
endif()

if(OTB_USE_OPENCV)
  list(APPEND ${proj}_DEPENDENCIES OPENCV)
endif()

if(OTB_USE_LIBSVM)
  list(APPEND ${proj}_DEPENDENCIES LIBSVM)
endif()

if(OTB_USE_MUPARSER)
  list(APPEND ${proj}_DEPENDENCIES MUPARSER)
endif()

if(OTB_USE_MUPARSERX)
  list(APPEND ${proj}_DEPENDENCIES MUPARSERX)
endif()

if(OTB_WRAP_PYTHON OR OTB_WRAP_JAVA)
  list(APPEND ${proj}_DEPENDENCIES SWIG)
endif()

if(OTB_USE_QT4)
  list(APPEND ${proj}_DEPENDENCIES QT4)
  if(USE_SYSTEM_QT4 AND UNIX)
    message(STATUS "  Qt4 is not built by SuperBuild. You need to install it via package manager.")
  endif()
endif()

INCLUDE_SUPERBUILD_DEPENDENCIES(${${proj}_DEPENDENCIES})
# set proj back to its original value
set(proj OTB)

ADD_SUPERBUILD_CMAKE_VAR(GDAL_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(GDAL_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OSSIM_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OSSIM_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(GDAL_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(GDAL_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(ITK_DIR)

ADD_SUPERBUILD_CMAKE_VAR(MUPARSER_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(MUPARSER_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(MUPARSERX_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(MUPARSERX_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(TINYXML_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(TINYXML_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(Boost_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(Boost_LIBRARY_DIR)

ADD_SUPERBUILD_CMAKE_VAR(LIBKML_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_BASE_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_CONVENIENCE_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_DOM_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_ENGINE_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_REGIONATOR_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_XSD_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(LIBKML_MINIZIP_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(OpenCV_DIR)

ADD_SUPERBUILD_CMAKE_VAR(LIBSVM_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(LIBSVM_LIBRARY)

ADD_SUPERBUILD_CMAKE_VAR(CURL_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(CURL_LIBRARY)

if(MSVC)
  ADD_SUPERBUILD_CMAKE_VAR(JPEG_LIBRARY)
endif()

ADD_SUPERBUILD_CMAKE_VAR(SWIG_EXECUTABLE)


if(SUPERBUILD_IN_OTB_TREE)
  set(OTB_HG_SOURCES DOWNLOAD_COMMAND "")
else()
  set(OTB_HG_SOURCES
    HG_REPOSITORY "http://hg.orfeo-toolbox.org/OTB"
    HG_TAG tip
    )
endif()

# issue with APPLE : the DYLD_LIBRARY_PATH is disabled everywhere but it is 
# necessary here
if(APPLE)
  set(OTB_SB_CMAKE_COMMAND
    env
    ${LDLIBVAR}=${CMAKE_INSTALL_PREFIX}/lib:$ENV{${LDLIBVAR}}
    ${CMAKE_COMMAND})
  list(APPEND OTB_SB_CONFIG
    -DCMAKE_C_FLAGS:STRING=-I${CMAKE_INSTALL_PREFIX}/include
    -DCMAKE_CXX_FLAGS:STRING=-I${CMAKE_INSTALL_PREFIX}/include)
else()
  set(OTB_SB_CMAKE_COMMAND ${SB_CMAKE_COMMAND})
endif()

# forward compilation flags
set(OTB_SB_COMPILATION_FLAGS
    -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
    -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
    -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
    -DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
    -DCMAKE_MODULE_LINKER_FLAGS:STRING=${CMAKE_MODULE_LINKER_FLAGS}
    -DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}
    -DCMAKE_STATIC_LINKER_FLAGS:STRING=${CMAKE_STATIC_LINKER_FLAGS}
    )

ExternalProject_Add(${proj}
    DEPENDS ${${proj}_DEPENDENCIES}
    PREFIX ${proj}
    ${OTB_HG_SOURCES}
    SOURCE_DIR ${OTB_SB_SRC}
    BINARY_DIR ${OTB_SB_BUILD_DIR}
    INSTALL_DIR ${CMAKE_INSTALL_PREFIX}
      DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
    CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:STRING=${CMAKE_INSTALL_PREFIX}
      ${OTB_SB_COMPILATION_FLAGS}
      -DBUILD_SHARED_LIBS:BOOL=${SB_BUILD_SHARED_LIBS}
      -DBUILD_TESTING:BOOL=${BUILD_TESTING}
      -DBUILD_EXAMPLES:BOOL=${BUILD_EXAMPLES}
      -DCMAKE_PREFIX_PATH:STRING=${CMAKE_INSTALL_PREFIX};${CMAKE_PREFIX_PATH}
      -DOTB_DATA_ROOT:STRING=${OTB_DATA_ROOT}
      -DOTB_USE_6S:BOOL=${OTB_USE_6S}
      -DOTB_USE_CURL:BOOL=${OTB_USE_CURL}
      -DOTB_USE_LIBKML:BOOL=${OTB_USE_LIBKML}
      -DOTB_USE_LIBSVM:BOOL=${OTB_USE_LIBSVM}
      -DOTB_USE_MAPNIK:BOOL=${OTB_USE_MAPNIK}
      -DOTB_USE_MUPARSER:BOOL=${OTB_USE_MUPARSER}
      -DOTB_USE_MUPARSERX:BOOL=${OTB_USE_MUPARSERX}
      -DOTB_USE_OPENCV:BOOL=${OTB_USE_OPENCV}
      -DOTB_USE_OPENJPEG:BOOL=${OTB_USE_OPENJPEG}
      -DOTB_USE_QT4:BOOL=${OTB_USE_QT4}
      -DOTB_USE_SIFTFAST:BOOL=${OTB_USE_SIFTFAST}
      ${OTB_SB_CONFIG}
      ${OTB_SB_LARGEINPUT_CONFIG}
      -DOTB_WRAP_PYTHON:BOOL=${OTB_WRAP_PYTHON}
      -DOTB_WRAP_JAVA:BOOL=${OTB_WRAP_JAVA}
      ${OTB_ADDITIONAL_CACHE}
    CMAKE_COMMAND ${OTB_SB_CMAKE_COMMAND}
    )



endif()
