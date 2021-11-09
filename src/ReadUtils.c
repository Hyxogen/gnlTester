//
// Created by Daan Meijer on 11/2/21.
//

#include "ReadUtils.h"
#include <unistd.h>
#include <dlfcn.h>
#include "Logger.h"

static int g_ReadFail = -1;
static size_t g_LastReadSize;

ssize_t read(int fildes, void *buf, size_t nbyte) {
	ssize_t (*libc_read)(int,void*,size_t) = dlsym(RTLD_NEXT, "read");
	g_LastReadSize = nbyte;
	if (!g_ReadFail) {
		g_ReadFail = -1;
		return (-1);
	} else if (g_ReadFail > -1)
		g_ReadFail--;
	return (libc_read(fildes, buf, nbyte));
}

ssize_t ReadSafe(int fildes, void *buf, size_t nbyte) {
	ssize_t (*libc_read)(int,void*,size_t) = dlsym(RTLD_NEXT, "read");
	return (libc_read(fildes, buf, nbyte));
}

void SetReadFail(int n) {
//	LogF("Setting read to fail in %d\n", n);
	g_ReadFail = n;
}

size_t GetLastReadSizeAttempt() {
	return (g_LastReadSize);
}