#include <stdio.h>

int main(int argc, char* argv[]) {
    //FILE* file = fopen("input_small.txt", "r");
    FILE* file = fopen("input.txt", "r");

    int depth = 0;
    int hor = 0;
    int aim = 0;

    char cmdBuffer[8]= {0};
    int num = 0;

    while (fscanf(file, "%s %d", cmdBuffer, &num) != EOF ) {
        //printf("Input: %s %d\n", cmdBuffer, num);

        // don't care about bogus input.
        // just check first letter
        char cmd = cmdBuffer[0];
        switch (cmd)
        {
        case 'f': // forward
            hor += num;
            depth += aim * num;
            break;
        case 'u': // up
            aim -= num;
            break;
        case 'd': // down
            aim += num;
            break;
        
        default:
            break;
        }
    }

    printf("Result: %d\n", hor * depth);

    fclose(file);
    return 1;
}