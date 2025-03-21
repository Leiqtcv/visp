#############################################################################
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
# ViSP configuration file.
#
# Authors:
# Fabien Spindler
#
#############################################################################

vp_add_module(me visp_core)
vp_glob_module_sources()
vp_module_include_directories()
vp_create_module()
vp_add_tests(DEPENDS_ON visp_io visp_gui)

vp_set_source_file_compile_flag(src/moving-edges/vpMeSite.cpp -Wno-strict-overflow)

if(USE_OPENCV)
  vp_set_source_file_compile_flag(src/moving-edges/vpMeNurbs.cpp -Wno-float-equal)
  vp_set_source_file_compile_flag(test/testNurbs.cpp -Wno-float-equal)
endif()

if(WITH_CATCH2)
  # catch2 is private
  include_directories(${CATCH2_INCLUDE_DIRS})
endif()