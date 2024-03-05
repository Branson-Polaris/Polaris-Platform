#include "test_def.h"
#include <sysLib.h>
#include <hwif/drv/resource/vxbRtcLib.h>

void rtc_test_show(struct tm *rtcTime, char *prefix)
{
    char msg[64] = {0};

    asctime_r((struct tm *)rtcTime, msg);
    printf("%s: %s", prefix, msg);
}

STATUS rtc_test(void)
{
    struct tm   rtcTime1;
    struct tm   rtcTime2;
    int         i;
    int         sec;

    printf("getting date...\n");
    if(vxbRtcGet(&rtcTime1) != OK)
    {
        printf("failed to get date\n");
        return ERROR;
    }
    rtc_test_show(&rtcTime1, "current date");

    printf("setting date...\n");
    rtcTime1.tm_year = 117;
    rtcTime1.tm_mon = 8;
    rtcTime1.tm_mday = 11;
    rtcTime1.tm_hour = 17;
    rtcTime1.tm_min = 10;
    rtcTime1.tm_sec = 3;
    rtc_test_show(&rtcTime1, "date to be set");
    if(vxbRtcSet(&rtcTime1) != OK)
    {
        printf("failed to set date\n");
        return ERROR;
    }

    printf("checking date...\n");
    if(vxbRtcGet(&rtcTime2) != OK)
    {
        printf("failed to get RTC\n");
        return ERROR;
    }
    rtc_test_show(&rtcTime2, "current date");
    if((rtcTime1.tm_year != rtcTime2.tm_year) ||
        (rtcTime1.tm_mon != rtcTime2.tm_mon) ||
        (rtcTime1.tm_mday != rtcTime2.tm_mday) ||
        (rtcTime1.tm_hour != rtcTime2.tm_hour) ||
        (rtcTime1.tm_min != rtcTime2.tm_min) ||
        (rtcTime1.tm_sec > rtcTime2.tm_sec))
    {
        printf("date is not match\n");
        return ERROR;
    }

    sec = 12;
    if(vxbRtcGet(&rtcTime1) != OK)
    {
        printf("failed to call vxbRtcGet\n");
        return ERROR;
    }
    rtc_test_show(&rtcTime1, "get");

    for(i = 0; i < sec; i++)
    {
        taskDelay(sysClkRateGet() + 10);
        printf(" %d\n", i);
    }
    printf("\n");
    vxbRtcGet(&rtcTime2);
    rtc_test_show(&rtcTime2, "get");

    if((rtcTime1.tm_year != rtcTime2.tm_year) ||
        (rtcTime1.tm_mon != rtcTime2.tm_mon) ||
        (rtcTime1.tm_mday != rtcTime2.tm_mday) ||
        (rtcTime1.tm_hour != rtcTime2.tm_hour) ||
        (rtcTime1.tm_min != rtcTime2.tm_min) ||
        ((rtcTime1.tm_sec + 12) > rtcTime2.tm_sec))
        {
            printf("RTC is not working\n");
            return ERROR;
        }

    return OK;
}

