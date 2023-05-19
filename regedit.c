# The TOKEN
# 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

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

        printf("Preparing to open /dev/mem with R/W permissions...\n");

        int fd = open("/dev/mem", O_RDWR);
    if (fd == -1) {
        // Handle error opening /dev/mem
                printf("Handle Error...\n");
        return -1;
    }

    // Perform operations on /dev/mem using the file descriptor
        printf("Closing /dev/mem instance...\n");
    close(fd);

        printf("Program Complete!\n");

    return 0;
}
