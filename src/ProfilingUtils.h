//
// Created by Daan Meijer on 11/2/21.
//

#ifndef TESTER_PROFILINGUTILS_H
#define TESTER_PROFILINGUTILS_H

#include <time.h>
#include "../include/tester.h"

typedef struct S_FuncInfo {
	void *m_Func;
	double m_Busy;
	unsigned long long m_CallCount;
	clock_t m_Start;
} FuncInfo;

void StartProfiler();
void StopProfiler();
void LogProfileData();
void ClearProfilerData();

/**
 *
 * @param funcInfo Exptects valid FuncInfo
 */
void LogFuncInfo(const void *funcInfoPtr);

void __cyg_profile_func_enter(void *this_fn, void *call_site);
void __cyg_profile_func_exit(void *this_fn, void *call_site);

/**
 *
 * @param funcInfo FuncInfo element
 * @param function function pointer
 * @return
 */
t_bool FuncInfoEqual(const void *funcInfo, const void *function);
void FreeFuncInfo(void *funcInfo);
#endif //TESTER_PROFILINGUTILS_H
