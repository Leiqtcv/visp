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
 * Test Universal Robots robot behavior
 *
 * Authors:
 * Fabien Spindler
 *
 *****************************************************************************/

/*!
  \example testUniversalRobotsCartVelocity.cpp

  Test robot from Universal Robots cartesian velocity controller implemented in vpRobotUniversalRobots.
*/

#include <iostream>

#include <visp3/core/vpConfig.h>

#if defined(VISP_HAVE_UR_RTDE) && (VISP_CXX_STANDARD >= VISP_CXX_STANDARD_11)

#include <visp3/robot/vpRobotUniversalRobots.h>

int main(int argc, char **argv)
{
  std::string robot_ip = "192.168.0.100";

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "--ip" && i + 1 < argc) {
      robot_ip = std::string(argv[i + 1]);
    } else if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
      std::cout << argv[0] << " [--ip " << robot_ip << "] [--help] [-h]"
                << "\n";
      return EXIT_SUCCESS;
    }
  }

  try {
    vpRobotUniversalRobots robot;
    robot.connect(robot_ip);

    std::cout << "WARNING: This example will move the robot! "
              << "Please make sure to have the user stop button at hand!" << std::endl
              << "Press Enter to continue..." << std::endl;
    std::cin.ignore();

    /*
     * Move to a safe position
     */
    vpColVector q(6, 0);
    q[0] = 0;
    q[1] = -M_PI_2;
    q[2] = M_PI_2;
    q[3] = -M_PI_2 / 2.;
    q[4] = -M_PI_2;
    q[5] = 0;
    std::cout << "Move to joint position: " << q.t() << std::endl;
    robot.setPositioningVelocity(10.);
    robot.setPosition(vpRobot::JOINT_STATE, q);

    /*
     * Move in cartesian velocity
     */
    double t0 = vpTime::measureTimeSecond();
    double delta_t = 4.0; // Time in second
    vpColVector qdot;
    vpColVector ve(6);
    //      ve[0] = -0.01; // vx goes toward the user
    //      ve[1] = 0.01; // vy goes left
    ve[2] = 0.02; // vz goes down
    //      ve[3] = vpMath::rad(5); // wx
    //      ve[4] = vpMath::rad(5); // wy
    //      ve[5] = vpMath::rad(5); // wz

    std::cout << "Apply cartesian vel in a loop for " << delta_t << " sec : " << ve.t() << std::endl;
    robot.setRobotState(vpRobot::STATE_VELOCITY_CONTROL);
    do {
      robot.setVelocity(vpRobot::END_EFFECTOR_FRAME, ve);
      vpTime::wait(10);
    } while (vpTime::measureTimeSecond() - t0 < delta_t);

    //      ve[0] = -0.01; // vx goes toward the user
    //            ve[1] = -0.01; // vy goes left
    ve[2] = -0.02; // vz goes down
    //      ve[3] = vpMath::rad(5); // wx
    //      ve[4] = vpMath::rad(5); // wy
    //      ve[5] = vpMath::rad(5); // wz
    std::cout << "Apply cartesian vel in a loop for " << delta_t << " sec : " << ve.t() << std::endl;
    t0 = vpTime::measureTimeSecond();
    do {
      robot.setVelocity(vpRobot::END_EFFECTOR_FRAME, ve);
      vpTime::wait(10);
    } while (vpTime::measureTimeSecond() - t0 < delta_t);

    std::cout << "Ask to stop the robot " << std::endl;
    robot.setRobotState(vpRobot::STATE_STOP);
  } catch (const vpException &e) {
    std::cout << "ViSP exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch (const std::exception &e) {
    std::cout << "ur_rtde exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "The end" << std::endl;
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
}

#endif
