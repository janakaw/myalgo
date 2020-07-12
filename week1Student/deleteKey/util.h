/*
 * util.h
 *
 *  Created on: 21/07/2011
 *      Author: phjlee
 */

#ifndef UTIL_H_
#define UTIL_H_

extern void *safe_malloc(size_t size);
extern FILE *safe_fopen(const char *path, const char *mode);

#endif /* UTIL_H_ */
