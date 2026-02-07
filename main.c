/**
 * @file      main.c
 * @brief     程序入口文件
 * @author    huenrong (sgyhy1028@outlook.com)
 * @date      2026-02-01 15:32:30
 *
 * @copyright Copyright (c) 2026 huenrong
 *
 */

#include <stdio.h>
#include <string.h>

#include "hs_time.h"

/**
 * @brief 程序入口
 *
 * @param[in] argc: 参数个数
 * @param[in] argv: 参数列表
 *
 * @return 成功: 0
 * @return 失败: 其它
 */
int main(int argc, char *argv[])
{
    char compile_date_time[64] = "";
    int ret = hs_time_get_compile_date_time(compile_date_time, sizeof(compile_date_time));
    if (ret == 0)
    {
        printf("compile date time: %s\n", compile_date_time);
    }
    else
    {
        printf("get compile date time failed. ret: %d\n", ret);
    }

    char timezone[64] = "";
    ret = hs_time_get_system_timezone(timezone, sizeof(timezone));
    if (ret == 0)
    {
        printf("timezone: %s\n", timezone);
    }
    else
    {
        printf("get timezone failed. ret: %d\n", ret);
    }

    uint8_t gap_flag = 0;
    char date_time_str[64] = "";
    ret = hs_time_get_date_time_str(date_time_str, sizeof(date_time_str), gap_flag);
    if (ret == 0)
    {
        printf("gap flag: %d, date time: %s\n", gap_flag, date_time_str);
    }
    else
    {
        printf("get date time failed(gap flag: %d). ret: %d\n", gap_flag, ret);
    }

    gap_flag = 1;
    memset(date_time_str, 0, sizeof(date_time_str));
    ret = hs_time_get_date_time_str(date_time_str, sizeof(date_time_str), gap_flag);
    if (ret == 0)
    {
        printf("gap flag: %d, date time: %s\n", gap_flag, date_time_str);
    }
    else
    {
        printf("get date time failed(gap flag: %d). ret: %d\n", gap_flag, ret);
    }

    gap_flag = 2;
    memset(date_time_str, 0, sizeof(date_time_str));
    ret = hs_time_get_date_time_str(date_time_str, sizeof(date_time_str), gap_flag);
    if (ret == 0)
    {
        printf("gap flag: %d, date time: %s\n", gap_flag, date_time_str);
    }
    else
    {
        printf("get date time failed(gap flag: %d). ret: %d\n", gap_flag, ret);
    }

    uint64_t uptime_ms = 0;
    ret = hs_time_get_uptime_ms(&uptime_ms);
    if (ret == 0)
    {
        printf("uptime(ms): %lu\n", uptime_ms);
    }
    else
    {
        printf("get uptime failed. ret: %d\n", ret);
    }

    hs_date_time_t local_time = {0};
    ret = hs_time_get_local_time(&local_time);
    if (ret == 0)
    {
        printf("current date time: %04d-%02d-%02d %02d:%02d:%02d, yday: %d, wday: %d\n", local_time.tm_year,
               local_time.tm_mon, local_time.tm_mday, local_time.tm_hour, local_time.tm_min, local_time.tm_sec,
               local_time.tm_yday, local_time.tm_wday);
    }
    else
    {
        printf("get date time failed. ret: %d\n", ret);
    }

    uint64_t timestamp_ms = 0;
    ret = hs_time_get_current_timestamp_ms(&timestamp_ms);
    if (ret == 0)
    {
        printf("current timestamp(ms): %lu\n", timestamp_ms);
    }
    else
    {
        printf("get current timestamp failed. ret: %d\n", ret);
    }

    /////////////////////////////////////////////////

    hs_date_time_t local_time_base = {.tm_year = 2026,
                                      .tm_mon = 1,
                                      .tm_mday = 2,
                                      .tm_hour = 10,
                                      .tm_min = 20,
                                      .tm_sec = 30,
                                      .tm_yday = 2,
                                      .tm_wday = 5};
    uint64_t unix_timestamp_s_base = 1767320430;

    uint64_t unix_timestamp_s = unix_timestamp_s_base;
    memset(&local_time, 0, sizeof(local_time));
    ret = hs_time_convert_unix_to_local(&local_time, unix_timestamp_s);
    if (ret == 0)
    {
        if (memcmp(&local_time, &local_time_base, sizeof(local_time)) == 0)
        {
            printf("convert unix to local success.\n");
        }
        else
        {
            printf("convert unix to local failed. convert local time: %04d-%02d-%02d %02d:%02d:%02d, "
                   "yday: %d, wday: %d\n",
                   local_time.tm_year, local_time.tm_mon, local_time.tm_mday, local_time.tm_hour, local_time.tm_min,
                   local_time.tm_sec, local_time.tm_yday, local_time.tm_wday);
        }
    }
    else
    {
        printf("convert unix to local failed. ret: %d\n", ret);
    }

    memset(&local_time, 0, sizeof(local_time));
    memcpy(&local_time, &local_time_base, sizeof(local_time));
    unix_timestamp_s = 0;
    ret = hs_time_convert_local_to_unix(&unix_timestamp_s, &local_time);
    if (ret == 0)
    {
        if (unix_timestamp_s == unix_timestamp_s_base)
        {
            printf("convert local to unix success.\n");
        }
        else
        {
            printf("convert local to unix failed. convert unix timestamp: %lu\n", unix_timestamp_s);
        }
    }
    else
    {
        printf("convert local to unix failed. ret: %d\n", ret);
    }

    return 0;
}
