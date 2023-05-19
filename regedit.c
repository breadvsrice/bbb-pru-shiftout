// The TOKEN
// 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

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd;
    volatile unsigned int *reg;

    printf("Preparing to open /dev/mem with R/W permissions...\n");

    fd = open("/dev/mem", O_RDWR);
    if (fd == -1) {
        printf("Error opening /dev/mem: %s\n", strerror(errno));
        return -1;
    }

    // Map physical memory address to virtual memory
    reg = (volatile unsigned int *)mmap(NULL, sizeof(unsigned int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x44E00400);
    if (reg == MAP_FAILED) {
        printf("Error mapping memory: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    // Read the value from the register
    unsigned int value = *reg;

    // Perform operations on the value
    printf("RegVal: 0x%x\n", value);

    // Set bit 3 in the value
    // unsigned int bitmask = 1 << 3;
    // value |= bitmask;

    // Write the modified value back to the register
    // *reg = value;

    // Unmap the memory
    if (munmap((void *)reg, sizeof(unsigned int)) == -1) {
        printf("Error unmapping memory: %s\n", strerror(errno));
    }

    printf("Closing /dev/mem instance...\n");
    close(fd);

    printf("Program Complete!\n");

    return 0;
}
