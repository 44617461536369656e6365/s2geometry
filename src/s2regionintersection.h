// Copyright 2006 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS-IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef UTIL_GEOMETRY_S2REGIONINTERSECTION_H__
#define UTIL_GEOMETRY_S2REGIONINTERSECTION_H__

#include <vector>

#include <glog/logging.h>
#include "base/macros.h"
#include "s2.h"
#include "s2region.h"

class Decoder;
class Encoder;
class S2Cap;
class S2Cell;
class S2LatLngRect;

// An S2RegionIntersection represents the intersection of a set of regions.
// It is convenient for computing a covering of the intersection of a set of
// regions.
class S2RegionIntersection : public S2Region {
 public:
  // Creates an empty intersection that should be initialized by calling Init().
  // Note: an intersection of no regions covers the entire sphere.
  S2RegionIntersection();

  // Create a region representing the intersection of the given regions.
  // Takes ownership of all regions and clears the given vector.
  S2RegionIntersection(std::vector<S2Region*>* regions);

  virtual ~S2RegionIntersection();

  // Initialize region by taking ownership of the given regions.
  void Init(std::vector<S2Region*>* regions);

  // Release ownership of the regions of this union, and appends them to
  // "regions" if non-NULL.  Resets the region to be empty.
  void Release(std::vector<S2Region*>* regions);

  // Accessor methods.
  int num_regions() const { return regions_.size(); }
  inline S2Region const* region(int i) const { return regions_[i]; }

  ////////////////////////////////////////////////////////////////////////
  // S2Region interface (see s2region.h for details):

  virtual S2RegionIntersection* Clone() const;
  virtual S2Cap GetCapBound() const;
  virtual S2LatLngRect GetRectBound() const;
  virtual bool VirtualContainsPoint(S2Point const& p) const;
  bool Contains(S2Point const& p) const;
  virtual bool Contains(S2Cell const& cell) const;
  virtual bool MayIntersect(S2Cell const& cell) const;
  virtual void Encode(Encoder* const encoder) const {
    LOG(FATAL) << "Unimplemented";
  }
  virtual bool Decode(Decoder* const decoder) { return false; }

 private:
  // Internal constructor used only by Clone() that makes a deep copy of
  // its argument.
  S2RegionIntersection(S2RegionIntersection const* src);

  std::vector<S2Region*> regions_;

  DISALLOW_COPY_AND_ASSIGN(S2RegionIntersection);
};

#endif  // UTIL_GEOMETRY_S2REGIONINTERSECTION_H__