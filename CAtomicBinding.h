//
//  CAtomicBinding.h
//
//
//  Created by v on 2020/9/8.
//  Copyright © 2020 lvv. All rights reserved.
//

#ifndef _CAtomicBinding_H
#define _CAtomicBinding_H

#import <Foundation/Foundation.h>
#import <stdatomic.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, CAtomicMemoryOrder) {
    CAtomicMemoryOrderRelaxed = memory_order_relaxed,
    CAtomicMemoryOrderConsume = memory_order_consume,
    CAtomicMemoryOrderAcquire = memory_order_acquire,
    CAtomicMemoryOrderRelease = memory_order_release,
    CAtomicMemoryOrderAcqRel = memory_order_acq_rel,
    CAtomicMemoryOrderSeqCst = memory_order_seq_cst
};

static inline void CAtomicThreadFence(CAtomicMemoryOrder order) {
    atomic_thread_fence((memory_order)order);
}

static inline void CAtomicSignalFence(CAtomicMemoryOrder order) {
    atomic_signal_fence((memory_order)order);
}

#ifndef CATOMIC_DEFINE
#define CATOMIC_DEFINE(name, type) \
    @interface name : NSObject \
    \
    @property(nonatomic, readonly) type value; \
    @property(nonatomic, readonly) BOOL isLockFree; \
    \
    - (instancetype)initWithValue:(type)value; \
    \
    - (void)store:(type)desired; \
    \
    - (void)store:(type)desired order:(CAtomicMemoryOrder)order; \
    \
    - (type)load; \
    \
    - (type)loadWithOrder:(CAtomicMemoryOrder)order; \
    \
    - (BOOL)exchange:(type)desired; \
    \
    - (BOOL)exchange:(type)desired order:(CAtomicMemoryOrder)order; \
    \
    - (BOOL)compareExchangeStrong:(type *)expected desired:(type)desired; \
    \
    - (BOOL)compareExchangeStrong:(type *)expected desired:(type)desired \
                          success:(CAtomicMemoryOrder)success \
                          failure:(CAtomicMemoryOrder)failure; \
    \
    - (BOOL)compareExchangeWeak:(type *)expected desired:(type)desired; \
    \
    - (BOOL)compareExchangeWeak:(type *)expected desired:(type)desired \
                        success:(CAtomicMemoryOrder)success \
                        failure:(CAtomicMemoryOrder)failure; \
    \
    - (type)fetchAdd:(type)operand; \
    \
    - (type)fetchAdd:(type)operand order:(CAtomicMemoryOrder)order; \
    \
    - (type)fetchSub:(type)operand; \
    \
    - (type)fetchSub:(type)operand order:(CAtomicMemoryOrder)order; \
    \
    - (type)fetchOr:(type)operand; \
    \
    - (type)fetchOr:(type)operand order:(CAtomicMemoryOrder)order; \
    \
    - (type)fetchXor:(type)operand; \
    \
    - (type)fetchXor:(type)operand order:(CAtomicMemoryOrder)order; \
    \
    - (type)fetchAnd:(type)operand; \
    \
    - (type)fetchAnd:(type)operand order:(CAtomicMemoryOrder)order; \
    \
    @end
#endif // CATOMIC_DEFINE

#ifndef CATOMIC_IMPL
#define CATOMIC_IMPL(name, type) \
    @interface name () { \
     @private \
        _Atomic(type) _value; \
    } \
    \
    @end \
    \
    @implementation name \
    \
    - (instancetype)initWithValue:(type)value { \
        if (self = [super init]) { \
            _value = value; \
        } \
    \
        return self; \
    } \
    \
    - (type)value { \
        return atomic_load(&_value); \
    } \
    \
    - (BOOL)isLockFree { \
        return atomic_is_lock_free(&_value); \
    } \
    \
    - (void)store:(type)desired { \
        atomic_store(&_value, desired); \
    } \
    \
    - (void)store:(type)desired order:(CAtomicMemoryOrder)order { \
        atomic_store_explicit(&_value, desired, (memory_order)order); \
    } \
    \
    - (type)load { \
        return atomic_load(&_value); \
    } \
    \
    - (type)loadWithOrder:(CAtomicMemoryOrder)order { \
        return atomic_load_explicit(&_value, (memory_order)order); \
    } \
    \
    - (BOOL)exchange:(type)desired { \
        return atomic_exchange(&_value, desired); \
    } \
    \
    - (BOOL)exchange:(type)desired order:(CAtomicMemoryOrder)order { \
        return atomic_exchange_explicit(&_value, desired, (memory_order)order); \
    } \
    \
    - (BOOL)compareExchangeStrong:(type *)expected desired:(type)desired { \
        return atomic_compare_exchange_strong(&_value, expected, desired); \
    } \
    \
    - (BOOL)compareExchangeStrong:(type *)expected desired:(type)desired \
                          success:(CAtomicMemoryOrder)success \
                          failure:(CAtomicMemoryOrder)failure { \
        return atomic_compare_exchange_strong_explicit(&_value, expected, desired, \
                                                       (memory_order)success, (memory_order)failure); \
    } \
    \
    - (BOOL)compareExchangeWeak:(type *)expected desired:(type)desired { \
        return atomic_compare_exchange_weak(&_value, expected, desired); \
    } \
    \
    - (BOOL)compareExchangeWeak:(type *)expected desired:(type)desired \
                        success:(CAtomicMemoryOrder)success \
                        failure:(CAtomicMemoryOrder)failure { \
        return atomic_compare_exchange_weak_explicit(&_value, expected, desired, \
                                                     (memory_order)success, (memory_order)failure); \
    } \
    \
    - (type)fetchAdd:(type)operand { \
        return atomic_fetch_add(&_value, operand); \
    } \
    \
    - (type)fetchAdd:(type)operand order:(CAtomicMemoryOrder)order { \
        return atomic_fetch_add_explicit(&_value, operand, (memory_order)order); \
    } \
    \
    - (type)fetchSub:(type)operand { \
        return atomic_fetch_sub(&_value, operand); \
    } \
    \
    - (type)fetchSub:(type)operand order:(CAtomicMemoryOrder)order { \
        return atomic_fetch_sub_explicit(&_value, operand, (memory_order)order); \
    } \
    \
    - (type)fetchOr:(type)operand { \
        return atomic_fetch_or(&_value, operand); \
    } \
    \
    - (type)fetchOr:(type)operand order:(CAtomicMemoryOrder)order { \
        return atomic_fetch_or_explicit(&_value, operand, (memory_order)order); \
    } \
    \
    - (type)fetchXor:(type)operand { \
        return atomic_fetch_xor(&_value, operand); \
    } \
    \
    - (type)fetchXor:(type)operand order:(CAtomicMemoryOrder)order { \
        return atomic_fetch_xor_explicit(&_value, operand, (memory_order)order); \
    } \
    \
    - (type)fetchAnd:(type)operand { \
        return atomic_fetch_and(&_value, operand); \
    } \
    \
    - (type)fetchAnd:(type)operand order:(CAtomicMemoryOrder)order { \
        return atomic_fetch_and_explicit(&_value, operand, (memory_order)order); \
    } \
    \
    @end
#endif // CATOMIC_IMPL

CATOMIC_DEFINE(CAtomicBool, bool)
CATOMIC_DEFINE(CAtomicChar, char)
CATOMIC_DEFINE(CAtomicSChar, signed char)
CATOMIC_DEFINE(CAtomicUChar, unsigned char)
CATOMIC_DEFINE(CAtomicShort, short)
CATOMIC_DEFINE(CAtomicUShort, unsigned short)
CATOMIC_DEFINE(CAtomicInt, int)
CATOMIC_DEFINE(CAtomicUInt, unsigned int)
CATOMIC_DEFINE(CAtomicLong, long)
CATOMIC_DEFINE(CAtomicULong, unsigned long)
CATOMIC_DEFINE(CAtomicLLong, long long)
CATOMIC_DEFINE(CAtomicULLong, unsigned long long)
CATOMIC_DEFINE(CAtomicChar16, uint_least16_t)
CATOMIC_DEFINE(CAtomicChar32, uint_least32_t)
CATOMIC_DEFINE(CAtomicWChar, wchar_t)
CATOMIC_DEFINE(CAtomicIntLeast8, int_least8_t)
CATOMIC_DEFINE(CAtomicUIntLeast8, uint_least8_t)
CATOMIC_DEFINE(CAtomicIntLeast16, int_least16_t)
CATOMIC_DEFINE(CAtomicUIntLeast16, uint_least16_t)
CATOMIC_DEFINE(CAtomicIntLeast32, int_least32_t)
CATOMIC_DEFINE(CAtomicUIntLeast32, uint_least32_t)
CATOMIC_DEFINE(CAtomicIntLeast64, int_least64_t)
CATOMIC_DEFINE(CAtomicUIntLeast64, uint_least64_t)
CATOMIC_DEFINE(CAtomicIntFast8, int_fast8_t)
CATOMIC_DEFINE(CAtomicUIntFast8, uint_fast8_t)
CATOMIC_DEFINE(CAtomicIntFast16, int_fast16_t)
CATOMIC_DEFINE(CAtomicUIntFast16, uint_fast16_t)
CATOMIC_DEFINE(CAtomicIntFast32, int_fast32_t)
CATOMIC_DEFINE(CAtomicUIntFast32, uint_fast32_t)
CATOMIC_DEFINE(CAtomicIntFast64, int_fast64_t)
CATOMIC_DEFINE(CAtomicUIntFast64, uint_fast64_t)
CATOMIC_DEFINE(CAtomicIntPtr, intptr_t)
CATOMIC_DEFINE(CAtomicUIntPtr, uintptr_t)
CATOMIC_DEFINE(CAtomicSizeT, size_t)
CATOMIC_DEFINE(CAtomicPtrDiff, ptrdiff_t)
CATOMIC_DEFINE(CAtomicIntMax, intmax_t)
CATOMIC_DEFINE(CAtomicUIntMax, uintmax_t)

#ifdef __cplusplus
template <typename T>
class CAtomic final {
private:
    _Atomic(T) _value;

public:
    CAtomic(T value) :_value(value) {}

    BOOL isLockFree() {
        return atomic_is_lock_free(&_value);
    }

    void store(T desired, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        atomic_store_explicit(&_value, desired, (memory_order)order);
    }

    T load(CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_load_explicit(&_value, (memory_order)order);
    }

    BOOL exchange(T desired, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_exchange_explicit(&_value, desired, (memory_order)order);
    }

    BOOL compareExchangeStrong(T * _Nonnull expected, T desired,
                               CAtomicMemoryOrder success = CAtomicMemoryOrderSeqCst,
                               CAtomicMemoryOrder failure = CAtomicMemoryOrderSeqCst) {
        return atomic_compare_exchange_strong_explicit(&_value, expected, desired,
                                                       (memory_order)success, (memory_order)failure);
    }

    BOOL compareExchangeWeak(T * _Nonnull expected, T desired,
                             CAtomicMemoryOrder success = CAtomicMemoryOrderSeqCst,
                             CAtomicMemoryOrder failure = CAtomicMemoryOrderSeqCst) {
        return atomic_compare_exchange_weak_explicit(&_value, expected, desired,
                                                     (memory_order)success, (memory_order)failure);
    }

    T fetchAdd(T operand, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_fetch_add_explicit(&_value, operand, (memory_order)order);
    }

    T fetchSub(T operand, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_fetch_sub_explicit(&_value, operand, (memory_order)order);
    }

    T fetchOr(T operand, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_fetch_or_explicit(&_value, operand, (memory_order)order);
    }

    T fetchXor(T operand, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_fetch_xor_explicit(&_value, operand, (memory_order)order);
    }

    T fetchAnd(T operand, CAtomicMemoryOrder order = CAtomicMemoryOrderSeqCst) {
        return atomic_fetch_and_explicit(&_value, operand, (memory_order)order);
    }
};
#endif

NS_ASSUME_NONNULL_END

#endif // _CAtomicBinding_H
