#ifndef __OY_CATTREE__
#define __OY_CATTREE__

#include <cstdint>
#include <functional>

namespace OY {
    template <typename _Tp, typename _Operation>
    struct CatTree {
        std::vector<std::vector<_Tp>> m_sub;
        _Operation m_op;
        uint32_t m_length;
        _Tp m_defaultValue;
        void _check() {
            // assert(m_op(m_defaultValue, m_defaultValue) == m_defaultValue);
        }
        CatTree(uint32_t __length = 0, _Operation __op = std::max<_Tp>, _Tp __defaultValue = _Tp()) : m_op(__op), m_defaultValue(__defaultValue) {
            _check();
            resize(__length);
        }
        template <typename _Iterator>
        CatTree(_Iterator __first, _Iterator __last, _Operation __op = std::max<_Tp>, _Tp __defaultValue = _Tp()) : m_op(__op), m_defaultValue(__defaultValue) {
            _check();
            reset(__first, __last);
        }
        void resize(uint32_t __length) {
            if (!__length) return;
            m_length = __length;
            uint32_t d = m_length > 1 ? 32 - std::__countl_zero(m_length - 1) : 1;
            m_sub.resize(d);
            for (uint32_t i = 0; i < d; i++) {
                m_sub[i].resize(m_length * 2);
                for (uint32_t j = 0, k = j + (1 << i); j < m_length; j += 1 << i, k = std::min(j + (1 << i), m_length)) {
                    for (uint32_t l = j; l < k; l++) m_sub[i][l * 2] = l == j ? m_defaultValue : m_op(m_sub[i][(l - 1) * 2], m_defaultValue);
                    for (uint32_t l = k - 1; ~(l - j); l--) m_sub[i][l * 2 + 1] = l == k - 1 ? m_defaultValue : m_op(m_sub[i][(l + 1) * 2 + 1], m_defaultValue);
                }
            }
        }
        template <typename _Iterator>
        void reset(_Iterator __first, _Iterator __last) {
            m_length = __last - __first;
            uint32_t d = m_length > 1 ? 32 - std::__countl_zero(m_length - 1) : 1;
            m_sub.resize(d);
            for (uint32_t i = 0; i < d; i++) {
                m_sub[i].resize(m_length * 2);
                for (uint32_t j = 0, k = j + (1 << i); j < m_length; j += 1 << i, k = std::min(j + (1 << i), m_length)) {
                    for (uint32_t l = j; l < k; l++) m_sub[i][l * 2] = l == j ? *(__first + l) : m_op(m_sub[i][(l - 1) * 2], *(__first + l));
                    for (uint32_t l = k - 1; ~(l - j); l--) m_sub[i][l * 2 + 1] = l == k - 1 ? *(__first + l) : m_op(m_sub[i][(l + 1) * 2 + 1], *(__first + l));
                }
            }
        }
        void update(uint32_t __i, _Tp __val) {
            m_sub[0][__i * 2] = __val;
            for (uint32_t i = 1; i < m_sub.size(); i++) {
                uint32_t j = __i - (__i & (1 << i) - 1), k = std::min(j + (1 << i), m_length);
                for (int l = j; l < k; l++) m_sub[i][l * 2] = l == j ? query(l) : m_op(m_sub[i][(l - 1) * 2], query(l));
                for (int l = k - 1; l >= j; l--) m_sub[i][l * 2 + 1] = l == k - 1 ? query(l) : m_op(m_sub[i][(l + 1) * 2 + 1], query(l));
            }
        }
        _Tp query(uint32_t __i) const { return m_sub[0][__i * 2]; }
        _Tp query(uint32_t __left, uint32_t __right) const {
            if (__left == __right) return m_sub[0][__left * 2];
            uint32_t d = 31 - std::__countl_zero(__right ^ __left);
            return m_op(m_sub[d][__left * 2 + 1], m_sub[d][__right * 2]);
        }
        _Tp queryAll() const { return query(0, m_length - 1); }
    };
    template <typename _Tp = int>
    CatTree(uint32_t = 0, const _Tp &(*)(const _Tp &, const _Tp &) = std::max<_Tp>) -> CatTree<_Tp, const _Tp &(*)(const _Tp &, const _Tp &)>;
    template <typename _Tp = int>
    CatTree(uint32_t, _Tp (*)(_Tp, _Tp)) -> CatTree<_Tp, _Tp (*)(_Tp, _Tp)>;
    template <typename _Operation, typename _Tp = std::decay_t<typename decltype(std::mem_fn(&_Operation::operator()))::result_type>>
    CatTree(uint32_t, _Operation) -> CatTree<_Tp, _Operation>;
    template <typename _Iterator, typename _Tp = typename std::iterator_traits<_Iterator>::value_type>
    CatTree(_Iterator, _Iterator, const _Tp &(*)(const _Tp &, const _Tp &) = std::max<_Tp>) -> CatTree<_Tp, const _Tp &(*)(const _Tp &, const _Tp &)>;
    template <typename _Iterator, typename _Tp = typename std::iterator_traits<_Iterator>::value_type>
    CatTree(_Iterator, _Iterator, _Tp (*)(_Tp, _Tp)) -> CatTree<_Tp, _Tp (*)(_Tp, _Tp)>;
    template <typename _Iterator, typename _Operation, typename _Tp = typename std::iterator_traits<_Iterator>::value_type>
    CatTree(_Iterator, _Iterator, _Operation) -> CatTree<_Tp, _Operation>;
}

#endif