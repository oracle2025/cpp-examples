#ifndef _LIB_H_
#define _LIB_H_

#include "sample_export.h"

#ifdef __cplusplus
extern "C" {
#endif

const char* SAMPLE_EXPORT string_from_lib();

void * SAMPLE_EXPORT get_widget();

#ifdef __cplusplus
}
#endif

#endif /* _LIB_H_ */
