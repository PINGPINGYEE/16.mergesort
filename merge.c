#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 20 // 최댓값

// 변화 과정 출력
void printArrayWithHighlight(int A[], int from, int to) {
    for (int i = 0; i < N; i++) {
        if (i >= from && i <= to) {
            printf("%d ", A[i]);
        }
        else {
            printf("%d ", A[i]);
        }
    }
    printf("\n");
}

// merge하는 함수
void merge(int A[], int temp[], int from, int mid, int to, int* moveCount, int* compareCount, int cycleCount)
{
    int k = from, i = from, j = mid + 1;

    // 비교
    while (i <= mid && j <= to)
    {
        (*compareCount)++;
        if (A[i] < A[j]) {
            temp[k] = A[i];
            i++;
        }
        else {
            temp[k] = A[j];
            j++;
        }
        k++;
        (*moveCount)++;
    }

    while (i <= mid) {
        temp[k++] = A[i++];
        (*moveCount)++;
    }
    while (j <= to) {
        temp[k++] = A[j++];
        (*moveCount)++;
    }

    for (int i = from; i <= to; i++) {
        A[i] = temp[i];
    }

    if (cycleCount == 1) {
        printf("Result of merge: ");
        printArrayWithHighlight(A, from, to);
    }
}

// 정렬하는 함수
void mergesort(int A[], int temp[], int low, int high, int* moveCount, int* compareCount, int cycleCount)
{
    for (int m = 1; m <= high - low; m = 2 * m)
    {
        for (int i = low; i < high; i += 2 * m)
        {
            int from = i;
            int mid = i + m - 1;
            int to = (i + 2 * m - 1 < high) ? i + 2 * m - 1 : high;

            merge(A, temp, from, mid, to, moveCount, compareCount, cycleCount);
        }
    }
}

// 배열 출력
void printArray(int A[])
{
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// main 함수
int main()
{
    int A[N], temp[N];
    int cycleCount = 0;
    srand(time(NULL));

    int totalMoveCount = 0, totalCompareCount = 0;

    for (int repeat = 0; repeat < 20; repeat++) {
        cycleCount++;
        for (int i = 0; i < N; i++) {
            A[i] = (rand() % 100);
        }

        if (cycleCount == 1) {
            printf("Original array: ");
            printArray(A);
        }

        int moveCount = 0, compareCount = 0;

        mergesort(A, temp, 0, N - 1, &moveCount, &compareCount, cycleCount);

        totalMoveCount += moveCount;
        totalCompareCount += compareCount;

        if (cycleCount == 1) {
            printf("Sorted array: ");
            printArray(A);
            printf("\n");
        }
    }

    printf("Average Move Count: %d\n", totalMoveCount / 20);
    printf("Average Compare Count: %d\n", totalCompareCount / 20);

    return 0;
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 20
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y) =(t))
int total_comparisons = 0;  // 총 비교 횟수
int total_moves = 0;        // 총 이동 횟수
int run_count = 0;          // 실행 횟수

int sorted[MAX_SIZE]; // 추가적인 공간이 필요
void merge(int list[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left, l;

    while (i <= mid && j <= right) {
        total_comparisons++; // 비교 횟수 증가
        if (list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
        total_moves++; // 이동 횟수 증가
    }

    if (i > mid) {
        for (l = j; l <= right; l++, k++) {
            sorted[k] = list[l];
            total_moves++; // 이동 횟수 증가
        }
    }
    else {
        for (l = i; l <= mid; l++, k++) {
            sorted[k] = list[l];
            total_moves++; // 이동 횟수 증가
        }
    }

    for (l = left; l <= right; l++) {
        list[l] = sorted[l];
    }

    if (run_count == 1) { // 첫 번째 실행에서만 전체 배열 출력
        printf("Current Array: ");
        for (int i = 0; i < MAX_SIZE; i++) {
            printf("%d ", list[i]);
        }
        printf("\n");
    }
}

void merge_sort(int list[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

int main() {
    int i, n = MAX_SIZE;
    int list[MAX_SIZE];

    srand(time(NULL)); // 랜덤 시드 설정

    for (run_count = 1; run_count <= 20; run_count++) {
        for (i = 0; i < MAX_SIZE; i++) {
            list[i] = rand() % 100;
        }

        merge_sort(list, 0, n - 1);
    }
    printf("Average Move Count: %d\n", total_moves / 20);
    printf("Average Comparison Count: %d\n", total_comparisons / 20);


    return 0;
}*/
