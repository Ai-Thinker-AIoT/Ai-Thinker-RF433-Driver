/* inttypes.h — 为固件的 PRIu32 / PRIu16 等提供格式宏
 * C351 32位：uint32_t=unsigned long(%lu)，uint16_t=unsigned int(%u)
 */
#ifndef __INTTYPES_H
#define __INTTYPES_H

#define PRId8   "d"
#define PRId16  "d"
#define PRId32  "ld"
#define PRId64  "ld"

#define PRIu8   "u"
#define PRIu16  "u"
#define PRIu32  "lu"
#define PRIu64  "lu"

#define PRIx8   "x"
#define PRIx16  "x"
#define PRIx32  "lx"
#define PRIx64  "lx"

#endif /* __INTTYPES_H */
