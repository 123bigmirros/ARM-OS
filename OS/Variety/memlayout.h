
#define EXTMEM 0x100000
#define KERNBASE 0x80000000 //内核在虚拟内存中的首ithiel
#define LINK_ADD 0x80100000
#define PHYSTOP 0x80E00000
#define V2P(x) (x)
#define P2V(x) ((x) + KERNBASE)
//因为arm的内存的首地址就是0x80000000，我们会将链接地址设为0x80100000