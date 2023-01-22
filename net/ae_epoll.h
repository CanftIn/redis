#include "ae.h"
#include "zmalloc.h"
#include "anet.h"
#include "redisassert.h"

#include <string.h>
#include <sys/epoll.h>
#include <errno.h>

typedef struct aeApiState {
    int epfd;
    struct epoll_event *events;
} aeApiState;

int aeApiCreate(aeEventLoop *eventLoop);
int aeApiResize(aeEventLoop *eventLoop, int setsize);
void aeApiFree(aeEventLoop *eventLoop);
int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask);
void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int delmask);
int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp);
char *aeApiName(void);

