#include <stdio.h>
#include <limits.h>

union Numbers {
    unsigned short n[4];
    unsigned long long packed;
};

static int n_1(Numbers n) {
    return n.n[0] + n.n[1] + n.n[2];
}

static int n_2(Numbers n) {
    return n.n[1] + n.n[2] + n.n[3];
}

int main(int argc, char* argv[]) {
    //FILE* file = fopen("input_small.txt", "r");
    FILE* file = fopen("input.txt", "r");

    int num = 0;
    int prev = INT_MAX;
    int result = 0;

    Numbers n = {};

    fscanf(file, "%hd", &n.n[0]);
    fscanf(file, "%hd", &n.n[1]);
    fscanf(file, "%hd", &n.n[2]);

    //printf("n: %d\n", n_1(n));

    while (fscanf(file, "%hd", &n.n[3]) != EOF ) {
        //printf("n: %d\n", n_2(n));

        if (n_1(n) < n_2(n)) {
            ++result;
        }

        n.packed = n.packed >> 16;
    }

    printf("Result: %d\n", result);

    fclose(file);
    return 1;
}