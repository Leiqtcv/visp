# ############################################################################
#
# ViSP, open source Visual Servoing Platform software.
# Copyright (C) 2005 - 2022 by Inria. All rights reserved.
#
# This software is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# See the file LICENSE.txt at the root directory of this source
# distribution for additional information about the GNU GPL.
#
# For using ViSP with software that can not be combined with the GNU
# GPL, please contact Inria about acquiring a ViSP Professional
# Edition License.
#
# See http://visp.inria.fr for more information.
#
# This software was developed at:
# Inria Rennes - Bretagne Atlantique
# Campus Universitaire de Beaulieu
# 35042 Rennes Cedex
# France
#
# If you have questions regarding the use of this file, please contact
# Inria at visp@inria.fr
#
# This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
# WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
# Description:
# Try to find Qualisys SDK
# Once run this will define:
#
# QUALISYS_FOUND
# QUALISYS_INCLUDE_DIRS
# QUALISYS_LIBRARIES
# QUALISYS_VERSION
#
# ############################################################################

find_path(QUALISYS_INCLUDE_DIR
  NAMES qualisys_cpp_sdk/RTProtocol.h
  PATHS
  $ENV{QUALISYS_DIR}/include
  ${QUALISYS_DIR}/include
  /usr/include
  /usr/local/include)

find_library(QUALISYS_LIBRARY
  NAMES qualisys_cpp_sdk
  PATHS
  $ENV{QUALISYS_DIR}/lib
  ${QUALISYS_DIR}/lib
  /usr/lib
  /usr/local/lib
)

if(QUALISYS_LIBRARY AND QUALISYS_INCLUDE_DIR)
  set(QUALISYS_INCLUDE_DIRS ${QUALISYS_INCLUDE_DIR})
  set(QUALISYS_LIBRARIES ${QUALISYS_LIBRARY})
  set(QUALISYS_FOUND TRUE)
else()
  set(QUALISYS_FOUND FALSE)
endif()

mark_as_advanced(
  QUALISYS_INCLUDE_DIR
  QUALISYS_LIBRARY
)
