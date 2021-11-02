//
// Created by Daan Meijer on 11/2/21.
//

#ifndef TESTER_READUTILS_H
#define TESTER_READUTILS_H
#include <wchar.h>


//Sets read to fail after n times. Set to -1 to never fail
void SetReadFail(int n);

size_t GetLastReadSizeAttempt();

ssize_t read(int fildes, void *buf, size_t nbyte);

ssize_t ReadSafe(int filedes, void *buf, size_t nbyte);

#endif //TESTER_READUTILS_H
