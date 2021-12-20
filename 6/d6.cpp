#include <stdio.h>

const int GROUP_NUM = 9;
//const int TURN_LIMIT = 18;
const int TURN_LIMIT = 80;

void dump_groups(long long groups[GROUP_NUM]) {
    printf("Groups:\n");
    for (int i = 0; i < GROUP_NUM; ++i) {
        printf("  [%d] => %lld\n", i, groups[i]);
    }
}

long long solve(FILE* file, int turn_limit) {
    long long groups[GROUP_NUM] = {};

    int age;
    while ( fscanf(file, "%d", &age) != EOF ) {
        //printf("Age: %d\n", age);
        // skip comma
        fscanf(file, ",");

        groups[age]++;
    }

    //dump_groups(groups);

    for (int i = 0; i < turn_limit; ++i) {

        long long carry = 0;
        for (int gi = GROUP_NUM - 1; gi >= 1; --gi) {
            long long fish_count = groups[gi];
            groups[gi] = carry;
            carry = fish_count;
        }

        // handle first group
        long long fish_count = groups[0];
        groups[GROUP_NUM-1] = fish_count; // newborn
        groups[6] += fish_count; // start new cycle
        groups[0] = carry;

    }

    long long total_fish = 0;
    for (int gi = 0; gi < GROUP_NUM; ++gi) {
        total_fish += groups[gi];
    }

    dump_groups(groups);

    return total_fish;
}

int main(int argc, char* argv[]) {
    //FILE* file = fopen("input_small.txt", "r");
    FILE* file = fopen("input.txt", "r");
    //int result = solve(file, 80); // puzzle 1
    long long result = solve(file, 256); // puzzle 2
    printf("Result: %lld\n", result);
    fclose(file);
    return 1;
}