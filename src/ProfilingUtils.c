//
// Created by Daan Meijer on 11/2/21.
//

#include "ProfilingUtils.h"
#include <dlfcn.h>
#include "Logger.h"

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	Dl_info info;
	Dl_info extra_info;

	dladdr(this_fn, &info);
	dladdr(call_site, &extra_info);
	LogF("this_fn dli_fname:%s dli_sname:%s\n", info.dli_fname, info.dli_sname);
	LogF("call_site dli_fname:%s dli_sname:%s\n", extra_info.dli_fname, extra_info.dli_sname);
	LogF("__cyg_profile_func_enter this_fn:%p call_site:%p\n", this_fn, call_site);
}

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	LogF("__cyg_profile_func_exit this_fn:%p call_site:%p\n", this_fn, call_site);
}