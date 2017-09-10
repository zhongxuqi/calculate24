#include "TimeUtils.h"

long long TimeUtils::getCurrentTime() {
    timeval curTime;
    gettimeofday(&curTime, NULL);
    return (long long)(curTime.tv_sec) * 1000 + (long long)(curTime.tv_usec) / 1000;
}