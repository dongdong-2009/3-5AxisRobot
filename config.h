#ifndef CONFIG_H
#define CONFIG_H

#ifndef HC_8AXIS
#define HC_8AXIS
#endif

#ifndef HC_ARMV6
#define HC_ARMV6
#endif

#define IFPOS_DECIMAL 0
#define POS_DECIMAL 2
#define SECTION_DECIMAL 1
#define STACK_DECIMAL 2

#define TRUNK_VERSION "GONGZHUANG-01-1.1-XS5-6.0.3"
#define APP_VERSION "CHUANYI-STD1-1.7"

#define SW_VERSION APP_VERSION"_"HOST_TYPE"_"TRUNK_VERSION
#define HW_VERSION "1.3"

#endif // CONFIG_H
