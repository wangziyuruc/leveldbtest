// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "leveldb/options.h"

#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "leveldb/filter_policy.h"
#include <iostream>

namespace leveldb {

Options::Options()
    : comparator(BytewiseComparator()),
      create_if_missing(false),
      error_if_exists(false),
      paranoid_checks(false),
      env(Env::Default()),
      info_log(NULL),
      write_buffer_size(4<<20),
      max_open_files(1000),
      block_cache(NULL),
      block_size(4096),
      block_restart_interval(16),
      max_file_size(2<<20),
      compression(kNoCompression),
      reuse_logs(false),
      filter_policy(NewBloomFilterPolicy(100)),
      amplify(4.0),
      top_level_size(10.0*1048576.0){
          //std::cout<<"options:filter:"<<filter_policy<<std::endl;
}

}  // namespace leveldb