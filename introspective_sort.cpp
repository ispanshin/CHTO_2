#pragma once

#include <random>
#include <utility>

template<class RandomIt, class Compare>
void heapify(RandomIt first, RandomIt last, RandomIt i, Compare comp) {
    size_t large = i - first;
    size_t n = last - first;
    size_t l = large * 2 + 1, r = 2 * large + 2;

    if (l < n && comp(*(first + large), *(first + l))) {
        large = l;
    }

    if (r < n && comp(*(first + large), *(first + r))) {
        large = r;
    }

    if (large != i - first) {
        swap(*i, *(first + large));
        heapify(first, last, large + first, comp);
    }
}


template<class RandomIt, class Compare>
void ___heap_sort(RandomIt first, RandomIt last, Compare comp) {
    size_t n = last - first;
    if (n == 0) {
        return;
    }
    for (long long i = (n / 2) - 1; i >= 0; --i) {
        heapify(first, last, i + first, comp);
    }
    for (long long i = n - 1; i >= 0; --i) {
        std::swap(*first, *(first + i));
        heapify(first, i + first, first, comp);
    }
}

template<class RandomIt, class Compare>
void ___insert_sort(RandomIt first, RandomIt last, Compare comp) {
    if (first == last) {
        return;
    }
    for (auto it = first + 1; it != last; ++it) {
        for (auto new_pos = it - 1; ; --new_pos) {
            if (comp(*new_pos, *(new_pos + 1))) {
                break;
            }
            std::swap(*new_pos, *(new_pos + 1));

            if (new_pos == first) {
                break;
            }
        }
    }
}
template<class RandomIt, class Compare>
RandomIt PartitionByPivot(RandomIt first, RandomIt last, Compare comp) {
    if (last == first) {
        return first;
    }

    std::mt19937 rnd;
    RandomIt pivot = first + (rnd() % (last - first));
    std::swap(*first, *pivot);
    RandomIt first_half = first;

    for (auto it = first + 1; it != last; ++it) {
        if (comp(*it, *first)) {
            ++first_half;
            std::swap(*first_half, *it);
        } /*else if (!comp(*first, *it)) { // means they are equal
            if (rnd() % 2) { // better expectation, but greater algorithm uses partition to 3 parts
                ++first_half;
                std::swap(*first_half, *it);
            }
        }*/
    }
    return ++first_half;

}

template<class RandomIt, class Compare>
void ___introspective_sort(RandomIt first, RandomIt last, size_t max_len, Compare comp) {
    if (last - first <= 16) {
        ___insert_sort(first, last, comp);
        return;
    }
    if (max_len == 0) {
        ___heap_sort(first, last, comp);
        return;
    }
    auto Mid = PartitionByPivot(first, last, comp);
    ___introspective_sort(first, Mid, max_len >> 1, comp);
    ___introspective_sort(Mid, last, max_len >> 1, comp);
}


template<class RandomIt, class Compare>
void introspective_sort(RandomIt first, RandomIt last, Compare comp) {
    ___introspective_sort(first, last, (last - first) * 2LL, comp);
}


