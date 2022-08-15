#pragma once

#include <functional>
#include <initializer_list>

namespace sorter {

template <typename T>
inline void swap(T &a, T &b) { T tmp = a; a = b; b = tmp; }

template <typename T>
void bubble_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	for (int i = 0; i < size - 1; i++)
		for (int j = 0, k = 1; j < size - i - 1; j++, k++)
			if (!cmp(arr[j], arr[k]))
				swap(arr[j], arr[k]);
}

/// selection_sort do less swap than bubble_sort.
template <typename T>
void selection_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	for (int i = 0; i < size - 1; i++) {
		int k = i;
		for (int j = i + 1; j < size; j++) {
			if (!cmp(arr[k], arr[j]))
				k = j;
		}

		if (k != i)
			swap(arr[i], arr[k]);
	}
}

template <typename T>
void __insertion_sort(T arr[], int size, std::function<bool (T&, T&)> cmp,
			int delta)
{
	for (int i = delta; i < size; i++) {
		T tmp = arr[i];
		int j = i;
		while (j >= delta && !cmp(arr[j - delta], tmp)) {
			arr[j] = arr[j - delta];
			j -= delta;
		}

		if (j != i)
			arr[j] = tmp;
	}
}

template <typename T>
void insertion_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	__insertion_sort(arr, size, cmp, 1);
}

template <typename T>
void shell_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	int delta = 1;
	while (delta < size / 3)
		delta = delta * 3 + 1; // Knuth, 1973

	for (; delta >= 1; delta /= 3)
		__insertion_sort(arr, size, cmp, delta);
}

/// merge 2 sorted arrays
template <typename T>
void __merge(T arr[], int start, int mid, int end,
		std::function<bool (T&, T&)> cmp)
{
	T *buf = new T[end - start];
	int s1 = start, s2 = mid, i = 0;

	while (s1 < mid && s2 < end) {
		if (cmp(arr[s1], arr[s2]))
			buf[i++] = arr[s1++];
		else
			buf[i++] = arr[s2++];
	}

	while (s1 < mid)
		buf[i++] = arr[s1++];

	while (s2 < end)
		buf[i++] = arr[s2++];

	for (int j = 0; j < i; j++)
		arr[start + j] = buf[j];

	delete[] buf;
}

template <typename T>
void __merge_sort_recur(T arr[], int start, int end,
			std::function<bool (T&, T&)> cmp)
{
	if (start >= end - 1)
		return;

	int mid = (start + end) / 2;

	__merge_sort_recur(arr, start, mid, cmp);
	__merge_sort_recur(arr, mid, end, cmp);

	__merge(arr, start, mid, end, cmp);
}

template <typename T>
void merge_sort_recur(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	__merge_sort_recur(arr, 0, size, cmp);
}

template <typename T>
void __merge_sort_step(T arr[], int size, int step,
			std::function<bool (T&, T&)> cmp)
{
	int unit = step * 2;
	for (int i = 0; i < size; i += unit)
		__merge(arr, i, std::min(i + step, size),
			std::min(i + unit, size), cmp);
}

template <typename T>
void merge_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	for (int step = 1; step < size; step *= 2)
		__merge_sort_step(arr, size, step, cmp);
}

template <typename T>
int __divide(T arr[], int start, int end, std::function<bool (T&, T&)> cmp) {
	T mid = arr[end - 1];
	int left = start;
	int right = end - 2;

	while (left < right) {
		while (cmp(arr[left], mid) && left < right)
			left++;

		while (!cmp(arr[right], mid) && left < right)
			right--;

		if (left != right)
			swap(arr[left], arr[right]);
	}

	if (!cmp(arr[left], mid))
		swap(arr[left], arr[end - 1]);

	return left + 1;
}

template <typename T>
void __quick_sort_recur(T arr[], int start, int end,
			std::function<bool (T&, T&)> cmp)
{
	if (start >= end - 1)
		return;

	int mid = __divide(arr, start, end, cmp);

	__quick_sort_recur(arr, start, mid, cmp);
	__quick_sort_recur(arr, mid, end, cmp);
}

template <typename T>
void quick_sort_recur(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	__quick_sort_recur(arr, 0, size, cmp);
}

int log2_int(int num) {
	int i = 0;
	for (; num > 1; num /= 2)
		i++;

	if (num % 2 == 0)
		return i;
	else
		return i + 1;
}

class Range {
public:
	Range(int start, int end) : start(start), end(end) {}
	Range() {}

public:
	int start;
	int end;
};

template <typename T>
void quick_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	Range *range_stack = new Range[log2_int(size)];

	// i always points to the next empty stack slot
	int i = 0;

	range_stack[i++] = {0, size};
	while (i) {
		Range r = range_stack[--i];
		if (r.start >= r.end - 1)
			continue;

		int mid = __divide(arr, r.start, r.end, cmp);

		range_stack[i++] = {r.start, mid};
		range_stack[i++] = {mid, r.end};
	}

	delete[] range_stack;
}

template <typename T>
void heap_adjust(T arr[], int size, int parent,
			std::function<bool (T&, T&)> cmp)
{
	T top = arr[parent];
	int p = parent;

	for (int i = p * 2 + 1; i < size; i = i * 2 + 1) {
		// i always represents the child of p
		if (cmp(arr[i], arr[i + 1]) && i + 1 < size)
			i++;

		if (!cmp(top, arr[i]))
			break;

		arr[p] = arr[i];
		p = i;
	}

	if (p != parent)
		arr[p] = top;
}

template <typename T>
void heap_sort(T arr[], int size, std::function<bool (T&, T&)> cmp) {
	// create the heap from bottom. (start from the first non-leaf node)
	for (int i = size / 2 - 1; i >= 0; i--)
		heap_adjust(arr, size, i, cmp);

	for (int i = size - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		heap_adjust(arr, i, 0, cmp);
	}
}

} // namespace sorter

