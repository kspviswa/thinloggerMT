thinloggerMT
============

Slim buffer to enable instrumentation in run time. Suitable for multi-threading application

Sometime logging to a file, won't help to debug issues.
For example, data corruption can happen if more than single thread, try to read & write
the shared resource at the same time.

But the scenario in which, these 2 threads come into picture, may be strongly dicdated by time.
There are cases where in such scenarion happens randomly @ certain instants.

Inorder to debug those issues, file logging may not be worth, since every I/O call calls for a latency.
The _race condition_ may not occur at all, if you introduce a delay.

thinloggerMT may be useful for these situations.

ThinloggerMT is a simple ringle-buffer implementation, where the buffers are indexed with the thread-id.
i.e Each thread has its own log buffer and these buffers are in-turn related to each other.

Since each thread, has its own buffer, these threads don't depend on each other. 
Hence there is no need for the threads to wait for a lock, thereby increasing the log-time of the threads.

These buffers are maintained in global state. As of now, if process core-dumps, then these buffers
could be examined from the core-file.

Future works have been planned, to dump the instrumentation on-demand basis or shared memory.
This buffer has been provided in a static lib format.

Steps to use this API
+++++++++++++++++++++

1) Define your own instrumentation info in THINLOGBUFFER struct.
2) Avoid using custom types. Live with primitive types.
3) Avoid pointers. If you do so, then focus on fill() to fill your pointees.
4) Include thinLoggerMT.h in your source.
5) call init() once and call doInstrumentation() with a pointer to THINLOGBUFFER struct N number of times you want.

--
Viswa [kspviswa]
