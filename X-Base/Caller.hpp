#pragma once
#include "pch.h"
#include "Invoker.hpp"

template <typename T>
static inline void native_push(T val)
{
	UINT64 val64 = 0;
	if (sizeof(T) > sizeof(UINT64)) throw "error, value size > 64 bit";
	*reinterpret_cast<T *>(&val64) = val;
	g_invoker->native_push64(val64);
};

template <typename R>
static inline R invoke(UINT64 hash)
{
	g_invoker->native_init(hash);
	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1>
static inline R invoke(UINT64 hash, T1 P1)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2>
static inline R invoke(UINT64 hash, T1 P1, T2 P2)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);
	native_push<T20>(P20);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);
	native_push<T20>(P20);
	native_push<T21>(P21);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);
	native_push<T20>(P20);
	native_push<T21>(P21);
	native_push<T22>(P22);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);
	native_push<T20>(P20);
	native_push<T21>(P21);
	native_push<T22>(P22);
	native_push<T23>(P23);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);
	native_push<T20>(P20);
	native_push<T21>(P21);
	native_push<T22>(P22);
	native_push<T23>(P23);
	native_push<T24>(P24);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}

template <typename R, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
static inline R invoke(UINT64 hash, T1 P1, T2 P2, T3 P3, T4 P4, T5 P5, T6 P6, T7 P7, T8 P8, T9 P9, T10 P10, T11 P11, T12 P12, T13 P13, T14 P14, T15 P15, T16 P16, T17 P17, T18 P18, T19 P19, T20 P20, T21 P21, T22 P22, T23 P23, T24 P24, T25 P25)
{
	g_invoker->native_init(hash);

	native_push<T1>(P1);
	native_push<T2>(P2);
	native_push<T3>(P3);
	native_push<T4>(P4);
	native_push<T5>(P5);
	native_push<T6>(P6);
	native_push<T7>(P7);
	native_push<T8>(P8);
	native_push<T9>(P9);
	native_push<T10>(P10);
	native_push<T11>(P11);
	native_push<T12>(P12);
	native_push<T13>(P13);
	native_push<T14>(P14);
	native_push<T15>(P15);
	native_push<T16>(P16);
	native_push<T17>(P17);
	native_push<T18>(P18);
	native_push<T19>(P19);
	native_push<T20>(P20);
	native_push<T21>(P21);
	native_push<T22>(P22);
	native_push<T23>(P23);
	native_push<T24>(P24);
	native_push<T25>(P25);

	return *reinterpret_cast<R *>(g_invoker->native_call());
}