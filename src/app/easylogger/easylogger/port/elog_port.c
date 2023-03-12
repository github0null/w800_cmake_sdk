/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */

#include <stdio.h>

#include "elog.h"
#include "wm_include.h"

static tls_os_mutex_t *log_locker;

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void)
{
    ElogErrCode result = ELOG_NO_ERR;
    tls_os_mutex_create(40, &log_locker);
    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void)
{
    if (log_locker != NULL) {
        tls_os_mutex_delete(log_locker);
    }
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size)
{
    for (size_t i = 0; i < size; i++) {
        putchar((int)log[i]);
    }
}

/**
 * output lock
 */
void elog_port_output_lock(void)
{
    tls_os_mutex_acquire(log_locker, 0);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void)
{
    tls_os_mutex_release(log_locker);
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void)
{
    static char buf[256];
    sprintf(buf, "%8u", tls_os_get_time_ms());
    return buf;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void)
{
    return "pid:-1";
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void)
{
    return "tid:-1";
}
