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

#include "pilz_industrial_motion_testutils/sequence.h"

#include <algorithm>

namespace pilz_industrial_motion_testutils
{

pilz_msgs::MotionSequenceRequest Sequence::toRequest() const
{
  pilz_msgs::MotionSequenceRequest req;

  bool first_cmd {true};
  for (const auto& cmd : cmds_)
  {
    pilz_msgs::MotionSequenceItem item;
    item.req = cmd.first->toRequest();

    if (!first_cmd)
    {
      // Remove start state because only the first request
      // is allowed to have a start state in a sequence.
      item.req.start_state = moveit_msgs::RobotState();
    }
    else
    {
      first_cmd = false;
    }

    item.blend_radius = cmd.second;
    req.items.push_back(item);
  }
  return req;
}

void Sequence::erase(const size_t start, const size_t end)
{
  const size_t orig_N {size()};
  if (start > orig_N || end > orig_N)
  {
    std::string msg;
    msg.append("Parameter start=").append(std::to_string(start));
    msg.append(" and end=").append(std::to_string(end));
    msg.append(" must not be greater then the number of #commands=");
    msg.append(std::to_string(size()));
    throw std::invalid_argument(msg);
  }
  cmds_.erase(cmds_.begin()+start, cmds_.begin()+end);
  if (end == orig_N)
  {
    // Make sure last radius is set zero
    cmds_.at(size()-1).second = 0.;
  }
}


}
