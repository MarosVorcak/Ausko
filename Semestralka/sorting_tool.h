#pragma once
#include <vector>
#include <functional>
class Sorter {
public:
	template<typename T, typename comparator>
	static void sort(std::vector<T>& src, comparator compare) {
		if (!src.empty()) {
			Sorter::quick(src, compare, 0, src.size() - 1);
		}
	}

	template<typename T, typename comparator>
	static void quick(std::vector<T>& src, comparator compare, size_t min, size_t max) {
		T pivot = src[min + (max - min) / 2];
		size_t left = min;
		size_t right = max;
		while (left <= right) {
			while (compare(src[left], pivot)) {
				++left;
			}
			while (right > 0 && compare(pivot, src[right])) {
				--right;
			}
			if (left <= right) {
				std::swap(src[left], src[right]);
				++left;
				if (right > 0) {
					--right;
				}
			}
		}
		if (min < right) {
			Sorter::quick(src, compare, min, right);
		}
		if (left < max) {
			Sorter::quick(src, compare, left, max);
		}
	}
};