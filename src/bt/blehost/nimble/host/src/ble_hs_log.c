/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "os/os.h"
#include "host/ble_hs.h"

struct log ble_hs_log;

void
ble_hs_log_mbuf(const struct os_mbuf *om_)
{
    struct os_mbuf *mbuff = (struct os_mbuf *)om_;
    while (mbuff) {
        BLE_HS_LOG(HEXDUMP, __FUNCTION__, 8, mbuff->om_data, mbuff->om_len);
        mbuff = SLIST_NEXT(mbuff, om_next);
    }
}

void
ble_hs_log_flat_buf(const void *data, int len)
{
    BLE_HS_LOG(HEXDUMP, __FUNCTION__, 4, data, len);
}
