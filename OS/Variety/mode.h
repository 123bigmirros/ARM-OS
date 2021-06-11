#define MODE_MASK 0x1f
#define SVC_MODE 0x13 //svc模式
#define PSR_F_BIT (1 << 6)
#define PSR_I_BIT (1 << 7) //PSR中断

#define CR_C (1 << 2)
#define CR_W (1<<3)
#define CR_Z (1 << 11)
#define CR_I (1 << 12)
#define CR_M (1 << 0)
#define CR_CLOSE CR_C | CR_Z | CR_I
#define DOMAIN_DEFAULT 0x55555555 //将所有domain设为client模式
