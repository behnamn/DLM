/*
 *
 *	GetLine.h
 * 	Author: Behnam
 *
 */
#ifndef GETLINE_H_
#define GETLINE_H_

#include "Headers.h"

ssize_t getline(char **linebuf, size_t *n, FILE *file);
ssize_t getdelim(char **linebuf, size_t *linebufsz, int delimiter, FILE *file);

#endif /* GETLINE_H_ */
