/*
    Copyright [2016] [Elías Serrano]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _CPPUTILS_H_
#define _CPPUTILS_H_

#if __cplusplus > 199711L

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

namespace GangerEngine {
    template<class T> struct _Unique_if {
        typedef std::unique_ptr<T> _Single_object;
    };

    template<class T> struct _Unique_if<T[]> {
        typedef std::unique_ptr<T[]> _Unknown_bound;
    };

    template<class T, size_t N> struct _Unique_if<T[N]> {
        typedef void _Known_bound;
    };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
            typedef typename std::remove_extent<T>::type U;
            return std::unique_ptr<T>(new U[n]());
        }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;
}  // namespace GangerEngine

#endif

#endif  // _CPPUTILS_H_
