//
// Created by user on 3/4/26.
//

#include "ArraySearch.h"

#include <iostream>

namespace search {
    // O(n)
    int linearSearch(const int *arr, const int size, const int x) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == x) {
                return i;
            }
        }
        return -1;
    }

    // O (log n)
    int binarySearch(const int arr[], const int size, const int x) {
        int low = 0;
        int high = size - 1;
        int mid = (low + high) / 2;

        while (true) {
            if (arr[mid] == x) {
                return mid;
            }

            if (mid == high || mid == low) {
                break;
            }

            if (x > arr[mid]) {
                low = mid;
                mid = (low + high) / 2;
            } else if (x < arr[mid]) {
                high = mid;
                mid = (low + high) / 2;
            }
        }

        return -1;
    }
} // search
