// Copyright 2014-2017 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <rmw_opendds_cpp/types.hpp>
#include <rmw_opendds_cpp/identifier.hpp>

#include <rmw/error_handling.h>
#include <rmw/impl/cpp/macros.hpp>
#include <rmw/rmw.h>

extern "C"
{
rmw_ret_t
rmw_compare_gids_equal(const rmw_gid_t * gid1, const rmw_gid_t * gid2, bool * result)
{
  if (!gid1) {
    RMW_SET_ERROR_MSG("gid1 is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!gid2) {
    RMW_SET_ERROR_MSG("gid2 is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!result) {
    RMW_SET_ERROR_MSG("result is null");
    return RMW_RET_INVALID_ARGUMENT;
  }
  if (!check_impl_id(gid1->implementation_identifier)) {
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }
  if (!check_impl_id(gid2->implementation_identifier)) {
    return RMW_RET_INCORRECT_RMW_IMPLEMENTATION;
  }
  auto detail1 = reinterpret_cast<const OpenDDSPublisherGID *>(gid1->data);
  if (!detail1) {
    RMW_SET_ERROR_MSG("gid1 is invalid");
    return RMW_RET_INVALID_ARGUMENT;
  }
  auto detail2 = reinterpret_cast<const OpenDDSPublisherGID *>(gid2->data);
  if (!detail2) {
    RMW_SET_ERROR_MSG("gid2 is invalid");
    return RMW_RET_INVALID_ARGUMENT;
  }
  *result = (detail1->publication_handle == detail2->publication_handle);
  return RMW_RET_OK;
}
}  // extern "C"
