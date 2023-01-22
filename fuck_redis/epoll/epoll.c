#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#define EXIT_IF(r, ...)                                            \
  if (r) {                                                         \
    printf(__VA_ARGS__);                                           \
    printf("error no: %d error msg %s\n", errno, strerror(errno)); \
    exit(1);                                                       \
  }

void setNonBlock(int fd) {
  int flag = fcntl(fd, F_GETFL, 0);
  EXIT_IF(flag < 0, "fcntl failed");
  int r = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
  EXIT_IF(r < 0, "fcntl failed");
}

void updateEvents(int efd, int fd, int events, int op) {
  struct epoll_event ev;
  memset(&ev, 0, sizeof(ev));
  ev.events = events;
  ev.data.fd = fd;
  printf("%s fd %d events read %d write %d\n",
         op == EPOLL_CTL_MOD ? "mod" : "add", fd, ev.events & EPOLLIN,
         ev.events & EPOLLOUT);
  int r = epoll_ctl(efd, op, fd, &ev);
  EXIT_IF(r, "epoll_ctl failed");
}

void loop_once(int efd, int fd, int wait_ms) {
  const int kMaxEvents = 20;
  struct epoll_event active_events[100];
  int n = epoll_wait(efd, active_events, kMaxEvents, wait_ms);
  printf("epoll_wait return %d\n", n);
  
}

int main() {
  int port = 0;
  int epollfd = epoll_create(1);
  EXIT_IF(epollfd < 0, "epoll_create failed");
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  EXIT_IF(listenfd < 0, "socket failed");

  struct sockaddr_in addr;
  memset(&addr, 0, sizeof addr);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_ANY;
  int r = bind(listenfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
  EXIT_IF(r, "bind to 0.0.0.0:%d failed %d %s", port, errno, strerror(errno));
  r = listen(listenfd, 20);
  EXIT_IF(r, "listen failed %d %s", errno, strerror(errno));
  printf("fd %d listening at %d\n", listenfd, port);
  setNonBlock(listenfd);
  updateEvents(epollfd, listenfd, EPOLLIN, EPOLL_CTL_ADD);
  for (;;) {
    loop_once(epollfd, listenfd, 10000);
  }
}