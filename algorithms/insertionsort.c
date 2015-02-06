#include "stdio.h"
int main (int argc, char const *argv[]) {
    int n, a[10], i, j, t;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    printf("Enter the numbers: ");
    for(i = 0; i < n; ++i) scanf("%d", &a[i]);
    for(i = 1; i < n; ++i) {
        for (j = i; j > 0 && a[j] < a[j-1]; j--) {
            t = a[j];
            a[j] = a[j-1];
            a[j-1] = t;
        }
    }
    for(i = 0; i < n; ++i) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
