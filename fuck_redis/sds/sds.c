#include <stdint.h>
#include <stdio.h>
/*
字节对齐有以下准则：

结构体变量的首地址能够被其对齐字节数大小所整除。
结构体每个成员相对结构体首地址的偏移都是成员大小的整数倍，如不满足，对前一个成员填充字节以满足。
结构体的总大小为结构体对最大成员大小的整数倍，如不满足，最后填充字节以满足。
*/

struct __attribute__((__packed__)) 
sdshdr8 {
  // buf已经使用的长度
  uint16_t len; /* used */
  // buf分配的长度，等于buf[]的总长度-1，因为buf有包括一个/0的结束符
  uint16_t alloc; /* excluding the header and null terminator */
  // 只有3位有效位，因为类型的表示就是0到4，所有这个8位的flags 有5位没有被用到
  unsigned char flags; /* 3 lsb of type, 5 unused bits */
  // 实际的字符串存在这里
  char buf[];
};

struct __attribute__((__packed__))
test_struct {
  unsigned char flag;
  uint16_t len;
  unsigned char c;
};

static inline int sdsHdrSize() { return sizeof(struct sdshdr8); }

static inline int testStructSize() { return sizeof(struct test_struct); }
int main() {
  int hdrlen = sdsHdrSize();
  printf("%d\n", hdrlen);
  hdrlen = testStructSize();
  printf("%d\n", hdrlen);
}