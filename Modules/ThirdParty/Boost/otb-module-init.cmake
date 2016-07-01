# Required
find_package ( Boost
  1.35.0
  REQUIRED
  )

if (BUILD_TESTING)
  # Optional components
  # Boost (OPTIONAL_COMPONENTS does not work with Boost find_package)
  # unit_test_framework component is used only in GdalAdapters module
  set(OTB_Boost_OPTIONAL_COMPONENTS unit_test_framework)

  message(STATUS "Looking for optional Boost components : ${OTB_Boost_OPTIONAL_COMPONENTS}")
  find_package ( Boost
    QUIET
    1.35.0
    COMPONENTS ${OTB_Boost_OPTIONAL_COMPONENTS}
    )
endif()
