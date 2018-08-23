//
//  Sort.cpp
//  Sorting
//
//  Created by Guanhua Yang on 10/28/15.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include "Sort.h"

//implementation of insertionsort
int insertionSort(Container& arr, Iter start, Iter end)
{
    Val key,comparison=0;
    Iter i,j;
    for(i=start+1;i<end;i++)
    {
        key=arr[i];
        j=i-1;
        comparison++;
        while(j>=0 && arr[j]>key)
        {
            comparison++;
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
    return comparison;
}

//implementation of quicksort
void partition(Container& arr, Iter start, Iter end, Val &comparison)
{
    if(arr.size()<=1)
    {
        return;
    }
    Val pivot=arr[end-1];
    Iter i=start,j=end-1;
    Container less,great,equal;
    if(i<j)
    {
        while(j>=0)
        {
            if(arr[j]<pivot)
            {
                less.push_back(arr[j--]);
            }
            else if(arr[j]==pivot)
            {
                equal.push_back(arr[j--]);
            }
            else
            {
                great.push_back(arr[j--]);
            }
            comparison++;
        }
    }
    partition(less, 0, less.size(),comparison);
    partition(great, 0, great.size(),comparison);
    Iter y=0;
    for(int x=0;x<less.size();x++)
    {
        arr[y++]=less[x];
    }
    for(int x=0;x<equal.size();x++)
    {
        arr[y++]=equal[x];
    }
    for(int x=0;x<great.size();x++)
    {
        arr[y++]=great[x];
    }
}


int quickSort(Container& arr, Iter start, Iter end)
{
    Val comparison=0;
    partition(arr,start,end,comparison);
    return comparison;
    
}

//implementation of mergesort

void merge(Container & arr, Iter start,Iter mid, Iter end, Val &count)
{
    Container temp;
    Iter i = start, j=mid;
    Iter m = mid-1, n=end-1;
    while(i<=m && j<=n)
    {
        if(arr[i] <= arr[j])
        {
            temp.push_back(arr[i++]);
        }
        else
        {
            temp.push_back(arr[j++]);
        }
        count++;
    }
    while(i<=m)
    {
        temp.push_back(arr[i++]);
    }
    while(j<=n)
    {
        temp.push_back(arr[j++]);
    }
    for(i=start;i<=end-1;i++)
    {
        arr[i]=temp[i-start];
    }
}
void merge_build(Container& arr, Iter start, Iter end,Val &count)
{
    Iter mid;
    if(end-start==1)
    {
        return;
    }
    if(start < end)
    {
        mid=(start+end)/2;
        merge_build(arr, start, mid,count);
        merge_build(arr,mid,end,count);
        merge(arr,start,mid,end,count);
    }
}

int mergeSort(Container& arr, Iter start, Iter end)
{
    int comparison=0;
    merge_build(arr,start,end,comparison);
    return comparison;
}


//implementation of shellsort
int shellSort(Container& arr, Iter start, Iter end)
{
    Val comparison=0;
    for(Iter gap= (end/2); gap > 0; gap/=2)
    {
        for(Iter i=gap; i<end; i++)
        {
            Val temp = arr[i];
            Iter j;
            for(j=i;j>=gap && arr[j-gap] > temp; j=j-gap)
                arr[j] = arr[j-gap];
                arr[j] = temp;
                comparison++;
        }
    }
    return comparison;
}
