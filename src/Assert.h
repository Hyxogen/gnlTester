//
// Created by Daan Meijer on 11/1/21.
//

#ifndef TESTER_ASSERT_H
#define TESTER_ASSERT_H

#include <signal.h>

#ifdef TESTER_ASSERT_ENABLE
#define ASSERT(x) if (!(x)) { raise(SIGTRAP); } else { }
#else
#define ASSERT(x)
#endif
#endif //TESTER_ASSERT_H
