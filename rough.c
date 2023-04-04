#include <stdio.h>
#include <stdlib.h>

// main() {
//     printf("main starts here\n");
//     printf("exit() initialises after this\n");
//     exit(1);
//     // exit(0) => terminated with no errors
//     // exit(1) => terminated with errors
//     printf("You shouldn't see this");
// }

int main(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("Arg %d: %s", i, argv[i]);
    }
    return 0;
}