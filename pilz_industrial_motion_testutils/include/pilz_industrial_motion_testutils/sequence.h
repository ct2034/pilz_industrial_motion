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

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <stdexcept>
#include <vector>
#include <utility>

#include <pilz_msgs/MotionSequenceRequest.h>

#include "command_types_typedef.h"
#include "motioncmd.h"

namespace pilz_industrial_motion_testutils
{

/**
 * @brief Data class storing all information regarding a Sequence command.
 */
class Sequence
{
public:
  Sequence()
  {}

public:
  /**
   * @brief Adds a command to the end of the sequence.
   * @param cmd The command which has to be added.
   */
  void add(MotionCmdUPtr cmd, const double blend_radius = 0.);

  /**
   * @brief Returns the number of commands.
   */
  size_t size() const;

  MotionCmd& getCmd(const size_t index_cmd);
  const MotionCmd& getCmd(const size_t index_cmd) const;

  void setAllBlendRadiiToZero();
  void setBlendRadii(const size_t index_cmd, const double blend_radius);
  double getBlendRadius(const size_t index_cmd) const;

  /**
   * @brief Deletes all commands from index 'start' to index 'end'.
   */
  void erase(const size_t start, const size_t end);

  pilz_msgs::MotionSequenceRequest toRequest() const;

private:
  using TCmdRadiiPair = std::pair<MotionCmdUPtr, double>;
  std::vector<TCmdRadiiPair > cmds_;
};

inline void Sequence::add(MotionCmdUPtr cmd, const double blend_radius)
{
  if (!cmd) {throw std::invalid_argument("Cmd must not be null");}
  cmds_.emplace_back( std::move(cmd), blend_radius );
}

inline size_t Sequence::size() const
{
  return cmds_.size();
}

inline MotionCmd& Sequence::getCmd(const size_t index_cmd)
{
  return *(cmds_.at(index_cmd).first);
}

inline const MotionCmd& Sequence::getCmd(const size_t index_cmd) const
{
  return *(cmds_.at(index_cmd).first);
}

inline double Sequence::getBlendRadius(const size_t index_cmd) const
{
  return cmds_.at(index_cmd).second;
}

inline void Sequence::setBlendRadii(const size_t index_cmd, const double blend_radius)
{
  cmds_.at(index_cmd).second = blend_radius;
}

inline void Sequence::setAllBlendRadiiToZero()
{
  std::for_each(cmds_.begin(), cmds_.end(), [](TCmdRadiiPair &cmd){ cmd.second = 0.; });
}

}


#endif // SEQUENCE_H
