Assuming uxMaxCount != 0 and uxInitialCount <= uxMaxCount,
this harness proves the memory safety of QueueCreateCountingSemaphore.

This proof is a work-in-progress.  Proof assumptions are described in
the harness.  The proof also assumes the following functions are
memory safe and have no side effects relevant to the memory safety of
this function:

* vPortEnterCritical
* vPortExitCritical
