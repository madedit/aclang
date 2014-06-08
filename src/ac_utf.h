/* see copyright notice in aclang.h */

#ifndef AC_UTF_H
#define AC_UTF_H

#include "ac_config.h"
#include "ac_utility.h"
#include <string>

/**
 * @return the length of dch in utf-8 format or 0 when error occurred
 */
int dcharToUTF8(acDchar dch, acChar *buf);

/**
 * @return the length of dch in utf-8 format or 0 when error occurred
 */
int UTF8ToDchar(const acChar *buf, int buf_len, acDchar &dch);

/**
 * convert acDcharVector to utf8 string
 */
void dcVecToUTF8Str(acDcharVector& dcVec, std::string& str);

#endif //AC_UTF_H
