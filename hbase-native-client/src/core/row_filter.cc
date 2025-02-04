/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "row_filter.h"

const char *RowFilter::FILTER_NAME = "org.apache.hadoop.hbase.filter.RowFilter";

RowFilter::RowFilter(const CompareOp &compare_op, const ByteArrayComparable *comparator):CompareFilter(compare_op, comparator) {
  // TODO Auto-generated constructor stub

}

RowFilter::~RowFilter() {
  // TODO Auto-generated destructor stub
}

const char *RowFilter::GetName(){

  return RowFilter::FILTER_NAME;
}

bool RowFilter::ToByteArray(hbase::pb::Filter &filter) {

  bool status = false;
  hbase::pb::CompareFilter comp_filter;
  google::protobuf::Message *msg = &comp_filter;
  std::unique_ptr<google::protobuf::Message> comparefilter_msg(this->Convert());
  msg = comparefilter_msg.get();
  if (nullptr != msg) {
    hbase::pb::CompareFilter *comp_filter_resp = dynamic_cast<hbase::pb::CompareFilter *>(msg);
    hbase::pb::RowFilter *row_filter = new hbase::pb::RowFilter();
    row_filter->set_allocated_compare_filter(comp_filter_resp);
    filter.set_name(this->GetName());
    filter.set_serialized_filter(row_filter->SerializeAsString());
    status = true;
  }
  return status;

}
