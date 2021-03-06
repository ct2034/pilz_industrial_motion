/*
 * Copyright (c) 2019 Pilz GmbH & Co. KG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MOTIONCMD_H
#define MOTIONCMD_H

#include <string>
#include <memory>

#include "motionplanrequestconvertible.h"

namespace pilz_industrial_motion_testutils
{

/**
 * @brief Base class for commands storing all general information of a command.
 */
class MotionCmd : public MotionPlanRequestConvertible
{
public:
  MotionCmd()
    : MotionPlanRequestConvertible()
  {
  }

public:
  void setPlanningGroup(const std::string &planning_group);

  void setTargetLink(const std::string &target_link);

  void setVelocityScale(double velocity_scale);
  void setAccelerationScale(double acceleration_scale);

protected:
  std::string planning_group_;
  //! Link to which all cartesian poses refer to.
  std::string target_link_;
  double vel_scale_;
  double acc_scale_;
};

inline void MotionCmd::setPlanningGroup(const std::string &planning_group)
{
  planning_group_ = planning_group;
}

inline void MotionCmd::setTargetLink(const std::string &target_link)
{
  target_link_ = target_link;
}

inline void MotionCmd::setVelocityScale(double velocity_scale)
{
  vel_scale_ = velocity_scale;
}

inline void MotionCmd::setAccelerationScale(double acceleration_scale)
{
  acc_scale_ = acceleration_scale;
}

using MotionCmdUPtr = std::unique_ptr<MotionCmd>;

}

#endif // MOTIONCMD_H
