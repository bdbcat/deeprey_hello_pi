# ~~~
# Summary:      Local, non-generic plugin setup
# Copyright (c) 2020-2021 Mike Rossiter
# License:      GPLv3+
# ~~~
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.


# -------- Options ----------

set(OCPN_TEST_REPO
    "opencpn/deeprey-alpha"
    CACHE STRING "Default repository for untagged builds"
)
set(OCPN_BETA_REPO
    "opencpn/deeprey-beta"
    CACHE STRING "Default repository for tagged builds matching 'beta'"
)
set(OCPN_RELEASE_REPO
    "opencpn/deeprey-prod"
    CACHE STRING "Default repository for tagged builds not matching 'beta'"
)
option(DEEPREY_USE_SVG "Use SVG graphics" ON)


#
#
# -------  Plugin setup --------
#
set(PKG_NAME deeprey_hello_pi)
set(PKG_VERSION  0.1.0.0)
set(PKG_PRERELEASE "")  # Empty, or a tag like 'beta'

set(DISPLAY_NAME DEEPREY_HELLO)    # Dialogs, installer artifacts, ...
set(PLUGIN_API_NAME DEEPREY_HELLO) # As of GetCommonName() in plugin API
set(PKG_SUMMARY "Deeprey Hello Base plugin")
set(PKG_DESCRIPTION [=[
Deeprey Hello.
]=])

set(PKG_AUTHOR "Dave Register")
set(PKG_IS_OPEN_SOURCE "yes")
set(CPACK_PACKAGE_HOMEPAGE_URL https://github.com/bdbcat/deeprey_hello_pi)
set(PKG_INFO_URL https://opencpn.org/OpenCPN/plugins/deeprey.html)

set(SRC
  src/deeprey_hello_pi.h
  src/deeprey_hello_pi.cpp
  src/IPanel.cpp
)


set(PKG_API_LIB api-17)  #  A directory in libs/ e. g., api-17 or api-16

macro(late_init)
  # Perform initialization after the PACKAGE_NAME library, compilers
  # and ocpn::api is available.
  if (DEEPREY_USE_SVG)
    target_compile_definitions(${PACKAGE_NAME} PUBLIC DEEPREY_USE_SVG)
  endif ()
endmacro ()

macro(add_plugin_libraries)
  # Add libraries required by this plugin
  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/plugin_dc")
  target_link_libraries(${PACKAGE_NAME} ocpn::plugin-dc)

#  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/wxJSON")
#  target_link_libraries(${PACKAGE_NAME} ocpn::wxjson)

#  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/plugingl")
#  target_link_libraries(${PACKAGE_NAME} ocpn::plugingl)

#  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/jsoncpp")
#  target_link_libraries(${PACKAGE_NAME} ocpn::jsoncpp)

  # The wxsvg library enables SVG overall in the plugin
#  add_subdirectory("${CMAKE_SOURCE_DIR}/opencpn-libs/wxsvg")
#  target_link_libraries(${PACKAGE_NAME} ocpn::wxsvg)

endmacro ()
