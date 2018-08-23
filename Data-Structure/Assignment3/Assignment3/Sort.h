//
//  Sort.h
//  Sorting
//
//  Created by Guanhua Yang on 10/28/15.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#ifndef sort_h
#define sort_h

#include <vector>

using Val = int;
using Container = std::vector<Val>;
using Iter = long;

int insertionSort(Container& arr, Iter start, Iter end);
int mergeSort(Container& arr, Iter start, Iter end);
int quickSort(Container& arr, Iter start, Iter end);
int shellSort(Container& arr, Iter start, Iter end);

#endif /* sort_h */