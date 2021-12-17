#include <stdio.h>
#include <cstring>

int search(int bits_num, int* numbers, int numbers_size, int* bucket1, int* bucket2, int* bucket3, bool most_common) {
    int* work_numbers = numbers;
    int work_numbers_size = numbers_size;

    int* output_one = bucket1;
    int output_one_size = 0;
    int* output_zero = bucket2;
    int output_zero_size = 0;
    int* output_back = bucket3;

    for (int bit = 0; bit < bits_num; ++bit) {
        for (int i = 0; i < work_numbers_size; ++i) {
            int num = work_numbers[i];
            bool has_one = num & 1 << (bits_num - bit - 1);
            if (has_one) {
                output_one[output_one_size++] = num;
            } else {
                output_zero[output_zero_size++] = num;
            }
        }

        if ((most_common && output_one_size >= output_zero_size) || (!most_common && output_one_size < output_zero_size)) {
            // Swap buckets
            work_numbers = output_one;
            work_numbers_size = output_one_size;
            output_one = output_back;
            output_back = work_numbers;
        } else {
            work_numbers = output_zero;
            work_numbers_size = output_zero_size;
            output_zero = output_back;
            output_back = work_numbers;
        }

        if (work_numbers_size == 1) {
            return work_numbers[0];
        }

        output_one_size = 0;
        output_zero_size = 0;
    }

    return -1;
}

int main(int argc, char* argv[]) {
    int numbers[1000] = {};
    int numbers_size = 0;

    // buckets to store intermediate results
    // keep 3 for swapping
    int bucket1[1000] = {};
    int bucket2[1000] = {};
    int bucket3[1000] = {};


    //FILE* file = fopen("input_small.txt", "r");
    FILE* file = fopen("input.txt", "r");

    // Parse input into int array.
    char buffer[13] = {0};
    int bits_num = 0;
    while ( fscanf(file, "%s", buffer) != EOF ) {
        bits_num = strlen(buffer);

        int num = 0;
        for (int i = 0; i < bits_num; ++i) {
            num += buffer[i] == '1' ? 1 << (bits_num - i - 1) : 0;
        }

        //printf("Input: %s => %d\n", buffer, num);
        numbers[numbers_size++] = num;
    }

    int oxygen_generator_rating = search(bits_num, numbers, numbers_size, bucket1, bucket2, bucket3, true);
    int co2_scrubber_rating = search(bits_num, numbers, numbers_size, bucket1, bucket2, bucket3, false);

    printf("Oxygen generator rating: %d\n", oxygen_generator_rating);
    printf("CO2 scrubber rating: %d\n", co2_scrubber_rating);

    printf("Result: %d\n", oxygen_generator_rating * co2_scrubber_rating);

    fclose(file);
    return 1;
}