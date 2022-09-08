// -*- C++ -*-
//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCUDACXX___FUNCTIONAL_BIND_FRONT_H
#define _LIBCUDACXX___FUNCTIONAL_BIND_FRONT_H

#include <__config>
#include <__functional/invoke.h>
#include <__functional/perfect_forward.h>
#include <__utility/forward.h>
#include <type_traits>

#if !defined(_LIBCUDACXX_HAS_NO_PRAGMA_SYSTEM_HEADER)
#  pragma GCC system_header
#endif

_LIBCUDACXX_BEGIN_NAMESPACE_STD

#if _LIBCUDACXX_STD_VER > 17

struct __bind_front_op {
    template <class ..._Args>
    _LIBCUDACXX_HIDE_FROM_ABI
    constexpr auto operator()(_Args&& ...__args) const
        noexcept(noexcept(_CUDA_VSTD::invoke(_CUDA_VSTD::forward<_Args>(__args)...)))
        -> decltype(      _CUDA_VSTD::invoke(_CUDA_VSTD::forward<_Args>(__args)...))
        { return          _CUDA_VSTD::invoke(_CUDA_VSTD::forward<_Args>(__args)...); }
};

template <class _Fn, class ..._BoundArgs>
struct __bind_front_t : __perfect_forward<__bind_front_op, _Fn, _BoundArgs...> {
    using __perfect_forward<__bind_front_op, _Fn, _BoundArgs...>::__perfect_forward;
};

template <class _Fn, class... _Args, class = enable_if_t<
    _And<
        is_constructible<decay_t<_Fn>, _Fn>,
        is_move_constructible<decay_t<_Fn>>,
        is_constructible<decay_t<_Args>, _Args>...,
        is_move_constructible<decay_t<_Args>>...
    >::value
>>
_LIBCUDACXX_HIDE_FROM_ABI
constexpr auto bind_front(_Fn&& __f, _Args&&... __args) {
    return __bind_front_t<decay_t<_Fn>, decay_t<_Args>...>(_CUDA_VSTD::forward<_Fn>(__f), _CUDA_VSTD::forward<_Args>(__args)...);
}

#endif // _LIBCUDACXX_STD_VER > 17

_LIBCUDACXX_END_NAMESPACE_STD

#endif // _LIBCUDACXX___FUNCTIONAL_BIND_FRONT_H
