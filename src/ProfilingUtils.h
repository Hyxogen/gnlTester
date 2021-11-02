//
// Created by Daan Meijer on 11/2/21.
//

#ifndef TESTER_PROFILINGUTILS_H
#define TESTER_PROFILINGUTILS_H

void __cyg_profile_func_enter (void *this_fn, void *call_site);
void __cyg_profile_func_exit  (void *this_fn, void *call_site);

#endif //TESTER_PROFILINGUTILS_H
