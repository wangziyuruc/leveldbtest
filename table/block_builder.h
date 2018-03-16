// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
#define STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_

#include <vector>

#include <stdint.h>
#include "leveldb/slice.h"

namespace leveldb {

struct Options;

class BlockBuilder {
 public:
  explicit BlockBuilder(const Options* options);

  // Reset the contents as if the BlockBuilder was just constructed.
  void Reset();//void Reset(); // 重设内容，通常在Finish之后调用已构建新的block  

  // REQUIRES: Finish() has not been called since the last call to Reset().
  // REQUIRES: key is larger than any previously added key
  //添加k/v，要求：Reset()之后没有调用过Finish()；Key > 任何已加入的key  
  void Add(const Slice& key, const Slice& value);

  // Finish building the block and return a slice that refers to the
  // block contents.  The returned slice will remain valid for the
  // lifetime of this builder or until Reset() is called.
  // 结束构建block，并返回指向block内容的指针  
  // 返回Slice的生存周期：Builder的生存周期，or直到Reset()被调用
  Slice Finish();

  // Returns an estimate of the current (uncompressed) size of the block
  // we are building.
  // 返回正在构建block的未压缩大小—估计值 
  size_t CurrentSizeEstimate() const;

  // Return true iff no entries have been added since the last Reset()
  // 没有entry则返回true
  bool empty() const {
    return buffer_.empty();
  }

 private:
  const Options*        options_;
  std::string           buffer_;      // Destination buffer block的内容  
  std::vector<uint32_t> restarts_;    // Restart points   重启点-后面会分析到 
  int                   counter_;     // Number of entries emitted since restart 重启后生成的entry数  
  bool                  finished_;    // Has Finish() been called?
  std::string           last_key_;    // 记录最后添加的key

  // No copying allowed
  BlockBuilder(const BlockBuilder&);
  void operator=(const BlockBuilder&);
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
