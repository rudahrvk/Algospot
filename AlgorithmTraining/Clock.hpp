#pragma once

#ifndef __CLOCK_H
#define __CLOCK_H
#endif

#include <Windows.h>

class Clock
{
public:

	Clock(void)
	{
		::QueryPerformanceFrequency(&m_freq);
	}

	~Clock(void)
	{
	}

	inline void MeasureBegin(void)	{ ::QueryPerformanceCounter(&m_start); }
	inline void MeasureEnd(void)	{ ::QueryPerformanceCounter(&m_end); }
	inline double GetSectionTime(void)	{ return (double)(m_end.QuadPart - m_start.QuadPart) / m_freq.QuadPart; }

private:
	LARGE_INTEGER m_freq;
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_end;
};