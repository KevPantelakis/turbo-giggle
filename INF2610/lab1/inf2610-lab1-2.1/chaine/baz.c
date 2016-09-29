/*
 * baz.c
 *
 *  Created on: 2013-08-15
 *      Author: Francis Giraldeau <francis.giraldeau@gmail.com>
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "whoami.h"

int main(int argc, char **argv) {
	increment_rank();
	whoami("baz");
	int nb = atoi(argv[1]);
	nb--;
	char buffer[20];
	sprintf(buffer, "%d", nb);
  	execlp("foo", "foo",buffer , NULL);
	return 0;
}
