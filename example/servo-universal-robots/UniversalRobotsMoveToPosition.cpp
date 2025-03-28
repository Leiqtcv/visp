/****************************************************************************
 *
 * ViSP, open source Visual Servoing Platform software.
 * Copyright (C) 2005 - 2022 by Inria. All rights reserved.
 *
 * This software is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact Inria about acquiring a ViSP Professional
 * Edition License.
 *
 * See http://visp.inria.fr for more information.
 *
 * This software was developed at:
 * Inria Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 *
 * If you have questions regarding the use of this file, please contact
 * Inria at visp@inria.fr
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Description:
 * Universal Robots robot tool.
 *
 *****************************************************************************/

/*!
  \example UniversalRobotsMoveToPosition.cpp
  Move robot from UniversalRobots to a position specified from a file.
*/

#include <iostream>

#include <visp3/core/vpConfig.h>

#if defined(VISP_HAVE_UR_RTDE)

#include <visp3/core/vpIoTools.h>
#include <visp3/robot/vpRobotUniversalRobots.h>

int main(int argc, char **argv)
{
  std::string opt_robot_ip = "192.168.0.100";
  std::string opt_position_filename = "";

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "--ip" && i + 1 < argc) {
      opt_robot_ip = std::string(argv[i + 1]);
    } else if (std::string(argv[i]) == "--read" && i + 1 < argc) {
      opt_position_filename = std::string(argv[i + 1]);
    } else if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
      std::cout << "Move UR robot to a position specified from a file." << std::endl;
      std::cout << argv[0] << " [--ip <default " << opt_robot_ip << ">] [--read <position file name>] [--help] [-h]\n"
                << std::endl;
      std::cout << "Example:\n" << argv[0] << " --ip 192.168.0.100 --read position.pos\n" << std::endl;

      return EXIT_SUCCESS;
    }
  }

  if (opt_position_filename.empty()) {
    std::cout << "\nError: no position file given as input with --read option. " << std::endl;
    std::cout << "Call \"" << argv[0] << " --help\" to get usage" << std::endl;
    return EXIT_FAILURE;
  }
  if (!vpIoTools::checkFilename(opt_position_filename)) {
    std::cout << "\nError: position filename \"" << opt_position_filename << "\" given as input doesn't exist. "
              << std::endl;
    std::cout << "Call \"" << argv[0] << " --help\" to get usage" << std::endl;
    return EXIT_FAILURE;
  }

  vpRobotUniversalRobots robot;

  try {
    robot.connect(opt_robot_ip);

    robot.move(opt_position_filename);
  } catch (const vpException &e) {
    std::cout << "ViSP exception: " << e.what() << std::endl;
    std::cout << "Stop the robot " << std::endl;
    robot.setRobotState(vpRobot::STATE_STOP);
    return EXIT_FAILURE;
  } catch (const std::exception &e) {
    std::cout << "ur_rtde exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
#else
int main()
{
#if !defined(VISP_HAVE_UR_RTDE)
  std::cout << "ViSP is not build with libur_rtde 3rd party used to control a robot from Universal Robots..."
            << std::endl;
#endif
#if (VISP_CXX_STANDARD < VISP_CXX_STANDARD_11)
  std::cout << "Build ViSP with c++11 or higher compiler flag (cmake -DUSE_CXX_STANDARD=11)." << std::endl;
#endif
  return EXIT_SUCCESS;
}
#endif
