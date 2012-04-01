#include <arpa/inet.h>
#include <assert.h>
#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <math.h>

#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#ifdef IH_PLATFORM_DARWIN
#include <sys/time.h>
#include <uuid/uuid.h>
#endif

#ifdef IH_PLATFORM_LINUX
#include <sys/time.h>
#include <uuid/uuid.h>
#endif

#ifdef IH_PLATFORM_NETBSD
#include <curses.h>
#include <uuid.h>
#endif
