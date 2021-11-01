//
// Created by Daan Meijer on 11/1/21.
//

#ifndef TESTER_ASSERT_H
#define TESTER_ASSERT_H
#include <signal.h>

//TODO test this
#define Assert(x) if (!x) { raise(SIGTRAP); } else { }
#endif //TESTER_ASSERT_H
