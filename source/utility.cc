#include "utility.h"
#include <sys/time.h>


unsigned long now() {
    timeval tv;
    gettimeofday(&tv, nullptr);
    return tv.tv_sec * ONESEC + tv.tv_usec;
}

