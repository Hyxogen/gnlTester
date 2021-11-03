//
// Created by Daan Meijer on 11/2/21.
//

#include "ProfilingUtils.h"
#include <dlfcn.h>
#include <stdlib.h>
#include "Logger.h"
#include "LinkedList.h"
#include "Assert.h"

static LinkedList *g_Profiler = NULL;
static t_bool g_ProfileOn = FALSE;

static FuncInfo *CreateFuncInfo(void *function) {
	FuncInfo *funcInfo;

	funcInfo = malloc(sizeof(FuncInfo));
	ASSERT(funcInfo);
	funcInfo->m_Func = function;
	funcInfo->m_Busy = 0;
	funcInfo->m_CallCount = 0;
	return (funcInfo);
}

void StartProfiler() {
	g_ProfileOn = TRUE;
	if (!g_Profiler) {
		ClearListWithElements(&g_Profiler, &FreeFuncInfo);
		g_Profiler = 0;
	}
}

void StopProfiler() {
	g_ProfileOn = FALSE;
}

void LogProfileData() {
	ForEachElement(g_Profiler, &LogFuncInfo);
}

void LogFuncInfo(const void *funcInfoPtr) {
	const FuncInfo *funcInfo;
	Dl_info info;

	funcInfo = funcInfoPtr;
	dladdr(funcInfo->m_Func, &info);
	LogF("\n---Profiling for: %p(%s)---\n", funcInfo->m_Func, info.dli_sname);
	LogF("Times called: %lu times\n", funcInfo->m_CallCount);
	LogF("Total time busy: %f seconds\n", funcInfo->m_Busy);
	LogF("Average time busy: %f seconds/call\n", funcInfo->m_Busy / funcInfo->m_CallCount);
	LogF("------------------------------------------------\n", funcInfo->m_Func, info.dli_sname);
}

void __cyg_profile_func_enter(void *this_fn, void *call_site) {
	LinkedList *funcElement;
	FuncInfo *funcInfo;
	clock_t now;
	Dl_info info;

	now = clock();
	call_site = NULL;
	funcElement = NULL;
	if (!g_ProfileOn) {
		return;
	}
	if (g_Profiler)
		funcElement = FindFirst(g_Profiler, &FuncInfoEqual, this_fn);
	if (!funcElement) {
		funcInfo = CreateFuncInfo(this_fn);
		AddBack(&g_Profiler, CreateElement(funcInfo));
	} else
		funcInfo = funcElement->m_Content;
	funcInfo->m_Start = now;
	funcInfo->m_CallCount += 1;
	dladdr(this_fn, &info);
//	LogF("Call:%p(%s)\n", this_fn, info.dli_sname);
}

void __cyg_profile_func_exit(void *this_fn, void *call_site) {
	LinkedList *funcElement;
	FuncInfo *funcInfo;
	clock_t now;
//	Dl_info info;

	now = clock();
	call_site = NULL;
	if (!g_ProfileOn)
		return;
	funcElement = FindFirst(g_Profiler, &FuncInfoEqual, this_fn);
//	if (!funcElement) {
//		dladdr(this_fn, &info);
//		LogF("Did not find entry for:%p(%s)\n", this_fn, info.dli_sname);
//		return;
//	}
	funcInfo = funcElement->m_Content;
	funcInfo->m_Busy += (now - funcInfo->m_Start)/(double)CLOCKS_PER_SEC;
//	LogF("__cyg_profile_func_exit this_fn:%p call_site:%p\n", this_fn, call_site);
}

t_bool FuncInfoEqual(const void *funcInfo, const void *function) {
	if (!funcInfo) {
		LogF("FuncInfo was nullptr!\n");
		return (FALSE);
	}
	return (((FuncInfo*)funcInfo)->m_Func == function);
}

void FreeFuncInfo(void *funcInfo) {
	free(funcInfo);
}