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

    // Get the page size for the system
    int page_size = getpagesize();
    printf("Page size: %d\n", page_size);

    // Address to be mapped (change it accordingly)
    unsigned int address = 0x44E00400;

    // Align the address to the page size
    unsigned int aligned_address = address & ~(page_size - 1);

    // Calculate the offset from the aligned address
    unsigned int offset = address - aligned_address;

    // Map physical memory address to virtual memory
    reg = (volatile unsigned int *)mmap(NULL, sizeof(unsigned int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, aligned_address);
    if (reg == MAP_FAILED) {
        printf("Error mapping memory: %s\n", strerror(errno));
        close(fd);
        return -1;
    }

    // Read the value from the register
    unsigned int value = reg[offset / sizeof(unsigned int)];

    // Perform operations on the value
    printf("RegVal: 0x%x\n", value);

    // Unmap the memory
    if (munmap((void *)reg, sizeof(unsigned int)) == -1) {
        printf("Error unmapping memory: %s\n", strerror(errno));
    }

    printf("Closing /dev/mem instance...\n");
    close(fd);

    printf("Program Complete!\n");

    return 0;
}
