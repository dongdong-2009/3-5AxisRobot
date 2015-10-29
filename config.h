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

#define TRUNK_VERSION "5.1.0"
#define APP_VERSION "XS5"

#define SW_VERSION APP_VERSION"_"TRUNK_VERSION
#define HW_VERSION "1.3"

#endif // CONFIG_H
