/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OCEANBASE_STORAGE_LS_MEMBER_LIST_SERVICE_
#define OCEANBASE_STORAGE_LS_MEMBER_LIST_SERVICE_

#include "logservice/ob_log_handler.h"
#include "common/ob_member.h"

namespace oceanbase
{
namespace storage
{

class ObLSMemberListService final
{
public:
  ObLSMemberListService();
  virtual ~ObLSMemberListService();
  int init(storage::ObLS *ls, logservice::ObLogHandler *log_handler);
  void destroy();

public:
  int add_member(const common::ObMember &member,
                 const int64_t paxos_replica_num,
                 const share::SCN &transfer_scn,
                 const int64_t add_member_timeout_us);
  int replace_member(const common::ObMember &added_member,
                     const common::ObMember &removed_member,
                     const share::SCN &transfer_scn,
                     const int64_t replace_member_timeout_us);
  int switch_learner_to_acceptor(const common::ObMember &learner,
                                 const int64_t paxos_replica_num,
                                 const share::SCN &transfer_scn,
                                 const int64_t timeout_us);

private:
  int check_ls_transfer_scn_(const share::SCN &transfer_scn);
private:
  bool is_inited_;
  storage::ObLS *ls_;
  logservice::ObLogHandler *log_handler_;
  DISALLOW_COPY_AND_ASSIGN(ObLSMemberListService);
};

}
}
#endif
