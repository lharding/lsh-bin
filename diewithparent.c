/*
 * Copyright (C) 2012 Andrew Ayer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the
 * sale, use or other dealings in this Software without prior written
 * authorization.
 */

/* From:
 * https://www.agwa.name/blog/post/remote_ssh_commands_and_broken_connections
 */

#include <sys/prctl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char *optarg;
extern int optind, opterr, optopt;

int main (int argc, char** argv)
{
	int		usage_error = 0;
	int		signal = SIGTERM;
	int		flag;

	while ((flag = getopt(argc, argv, "+s:")) != -1) {
		switch (flag) {
		case 's':
			signal = atoi(optarg);
			break;
		default:
			usage_error = 1;
		}
	}

	if (usage_error || signal <= 0 || argc - optind < 1) {
		fprintf(stderr, "Usage: %s [-s SIGNUM] PROGRAM [ARGS...]\n", argv[0]);
		return 2;
	}

	if (prctl(PR_SET_PDEATHSIG, signal) == -1) {
		perror("prctl");
	}
	execvp(argv[optind], argv + optind);
	perror(argv[optind]);
	return 127;
}
