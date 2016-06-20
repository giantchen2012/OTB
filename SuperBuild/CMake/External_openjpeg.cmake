INCLUDE_ONCE_MACRO(OPENJPEG)

SETUP_SUPERBUILD(PROJECT OPENJPEG)

# declare dependencies
ADDTO_DEPENDENCIES_IF_NOT_SYSTEM(OPENJPEG ZLIB TIFF PNG)

ADD_SUPERBUILD_CMAKE_VAR(OPENJPEG TIFF_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OPENJPEG TIFF_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OPENJPEG ZLIB_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OPENJPEG ZLIB_LIBRARY)
ADD_SUPERBUILD_CMAKE_VAR(OPENJPEG PNG_INCLUDE_DIR)
ADD_SUPERBUILD_CMAKE_VAR(OPENJPEG PNG_LIBRARY)

if(MSVC)
  #TODO: add LCMS dependency
endif()

# forward compilation flags
set(OPENJPEG_SB_COMPILATION_FLAGS
  -DCMAKE_BUILD_TYPE:STRING=${CMAKE_BUILD_TYPE}
  -DCMAKE_C_FLAGS:STRING=${CMAKE_C_FLAGS}
  -DCMAKE_CXX_FLAGS:STRING=${CMAKE_CXX_FLAGS}
  -DCMAKE_EXE_LINKER_FLAGS:STRING=${CMAKE_EXE_LINKER_FLAGS}
  -DCMAKE_MODULE_LINKER_FLAGS:STRING=${CMAKE_MODULE_LINKER_FLAGS}
  -DCMAKE_SHARED_LINKER_FLAGS:STRING=${CMAKE_SHARED_LINKER_FLAGS}
  -DCMAKE_STATIC_LINKER_FLAGS:STRING=${CMAKE_STATIC_LINKER_FLAGS}
  )

ExternalProject_Add(OPENJPEG
  PREFIX OPENJPEG
  GIT_REPOSITORY "https://github.com/uclouvain/openjpeg.git"
  GIT_TAG d0babeb6f6cdd1887308137df37bb2b4724a6592
  BINARY_DIR ${OPENJPEG_SB_BUILD_DIR}
  INSTALL_DIR ${SB_INSTALL_PREFIX}
  DOWNLOAD_DIR ${DOWNLOAD_LOCATION}
  CMAKE_CACHE_ARGS
  ${SB_CMAKE_CACHE_ARGS}
  ${OPENJPEG_SB_COMPILATION_FLAGS}
  -DBUILD_CODEC:BOOL=ON
  -DBUILD_DOC:BOOL=OFF
  -DBUILD_JPIP:BOOL=OFF
  -DBUILD_JPWL:BOOL=OFF
  -DBUILD_MJ2:BOOL=OFF
  -DBUILD_PKGCONFIG_FILES:BOOL=ON
  -DBUILD_THIRDPARTY:BOOL=OFF
  ${OPENJPEG_SB_CONFIG}
  DEPENDS ${OPENJPEG_DEPENDENCIES}
  CMAKE_COMMAND ${SB_CMAKE_COMMAND}
  )

SUPERBUILD_UPDATE_CMAKE_VARIABLES(OPENJPEG FALSE)

#Apply patches to openjpeg (for now Even Roualt optim)
SUPERBUILD_PATCH_SOURCE(OPENJPEG)
