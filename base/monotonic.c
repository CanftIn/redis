#include "monotonic.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#undef NDEBUG
#include <assert.h>

/* The function pointer for clock retrieval.  */
monotime (*getMonotonicUs)(void) = NULL;

static char monotonic_info_string[32];

static monotime getMonotonicUs_posix() {
    /* clock_gettime() is specified in POSIX.1b (1993).  Even so, some systems
     * did not support this until much later.  CLOCK_MONOTONIC is technically
     * optional and may not be supported - but it appears to be universal.
     * If this is not supported, provide a system-specific alternate version.  */
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ((uint64_t)ts.tv_sec) * 1000000 + ts.tv_nsec / 1000;
}

static void monotonicInit_posix() {
    /* Ensure that CLOCK_MONOTONIC is supported.  This should be supported
     * on any reasonably current OS.  If the assertion below fails, provide
     * an appropriate alternate implementation.  */
    struct timespec ts;
    int rc = clock_gettime(CLOCK_MONOTONIC, &ts);
    assert(rc == 0);

    snprintf(monotonic_info_string, sizeof(monotonic_info_string),
            "POSIX clock_gettime");
    getMonotonicUs = getMonotonicUs_posix;
}

const char * monotonicInit() {
    if (getMonotonicUs == NULL) monotonicInit_posix();

    return monotonic_info_string;
}

const char *monotonicInfoString() {
    return monotonic_info_string;
}

monotonic_clock_type monotonicGetType() {
    if (getMonotonicUs == getMonotonicUs_posix)
        return MONOTONIC_CLOCK_POSIX;
    return MONOTONIC_CLOCK_HW;
}
