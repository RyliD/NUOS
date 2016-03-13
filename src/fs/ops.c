#include <include/fs/ops.h>

// Check any given flags against the option, return whether the desired
// permission bits were found. A.k.a. "allowed"
static bool check_permissions(unsigned short current_flags,
                              unsigned short desired) {
    /* 0 values of basic types map to false, others map to true. */
    return current_flags & desired; // If bool is inoptimal, this will change.
}
