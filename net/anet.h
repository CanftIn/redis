/* anet.c -- Basic TCP socket stuff made a bit less boring
 *
 * Copyright (c) 2006-2012, Salvatore Sanfilippo <antirez at gmail dot com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Redis nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ANET_H
#define ANET_H

#include <stdint.h>
#include <sys/types.h>

#define ANET_OK 0
#define ANET_ERR -1
#define ANET_ERR_LEN 256

/* Flags used with certain functions. */
#define ANET_NONE 0
#define ANET_IP_ONLY (1<<0)

// tcp非阻塞连接
int anetTcpNonBlockConnect(char *err, const char *addr, int port);
// tcp服务器的bind非阻塞连接并且会失败重连
int anetTcpNonBlockBestEffortBindConnect(char *err, const char *addr, int port, const char *source_addr);
// 处理所有主机地址为名称或是ip
int anetResolve(char *err, char *host, char *ipbuf, size_t ipbuf_len, int flags);
// tcp中ipv4或ipv6的IP协议服务器套接字处理
int anetTcpServer(char *err, int port, char *bindaddr, int backlog);
// tcp中ipv6的IP协议服务器套接字处理
int anetTcp6Server(char *err, int port, char *bindaddr, int backlog);
// unix本地文件服务器套接字处理
int anetUnixServer(char *err, char *path, mode_t perm, int backlog);
// tcp套接字服务器端接收客户端的连接
int anetTcpAccept(char *err, int serversock, char *ip, size_t ip_len, int *port);
// 本地服务器的接收连接函数 对连接的客户端信息没有存储要求
int anetUnixAccept(char *err, int serversock);
// 设置用于通信的描述符的状态 阻塞还是非阻塞
int anetNonBlock(char *err, int fd);
int anetBlock(char *err, int fd);
int anetCloexec(int fd);
// 设置网络链接nodelay属性 是否关闭Nagle算法
int anetEnableTcpNoDelay(char *err, int fd);
int anetDisableTcpNoDelay(char *err, int fd);
int anetSendTimeout(char *err, int fd, long long ms);
int anetRecvTimeout(char *err, int fd, long long ms);
int anetFdToString(int fd, char *ip, size_t ip_len, int *port, int remote);
// 开启tcp的SO_KEEPALIVE
int anetKeepAlive(char *err, int fd, int interval);
int anetFormatAddr(char *fmt, size_t fmt_len, char *ip, int port);
int anetPipe(int fds[2], int read_flags, int write_flags);
int anetSetSockMarkId(char *err, int fd, uint32_t id);
int anetGetError(int fd);

#endif
