// The TOKEN
// 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

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int fd;
    volatile unsigned int *reg;

    printf("Preparing to open /dev/mem with R/W permissions...\n");

    fd = open("/dev/mem", O_RDWR);
    if (fd == -1) {
        printf("Error opening /dev/mem.\n");
        return -1;
    }

    // Map physical memory address to virtual memory
    // 0x4A300000 = PRU_ICSS Base Addr
    // 0x44E00400 = CFG_WKUP Base Addr
    reg = (volatile unsigned int *)mmap(NULL, sizeof(unsigned int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x4A300000);
    if (reg == MAP_FAILED) {
        printf("Error mapping memory.\n");
        close(fd);
        return -1;
    }

    // Read the value from the register
    unsigned int value = *reg;

    // Perform operations on the value
    printf("RegVal: 0x%x\n", value);
    
    // Set bit 3 in the value
    //unsigned int bitmask = 1 << 23;
    //value |= bitmask;

    // Write the modified value back to the register
    //*reg = value;

    // Unmap the memory
    munmap((void *)reg, sizeof(unsigned int));

    printf("Closing /dev/mem instance...\n");
    close(fd);

    printf("Program Complete!\n");

    return 0;
}
