#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#define MY_RNG_IOCTL_RAND      _IOR('q', 1, unsigned int)
#define MY_RNG_IOCTL_SET_MODE  _IOW('q', 2, unsigned int)
#define MY_RNG_IOCTL_GET_MODE  _IOR('q', 3, unsigned int)
#define DEVICE_PATH "/dev/my_rng_driver"
#define RAND_IOCTL	0x80047101
#define SEED_IOCTL	0x40047101

int main() {
    int fd = open("/dev/my_rng_driver", O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device file");
        return -1;
    }

    unsigned int mode = 1;  // Set to time-based RNG mode
    if (ioctl(fd, MY_RNG_IOCTL_SET_MODE, &mode) < 0) {
        perror("Failed to set RNG mode");
        close(fd);
        return -1;
    }

    printf("RNG mode set to %u\n", mode);

    unsigned int random_number;
    for (int i = 0; i < 5; i++) {
        if (ioctl(fd, MY_RNG_IOCTL_RAND, &random_number) < 0) {
            perror("Failed to get random number");
            close(fd);
            return -1;
        }
        printf("Random number %d: %u\n", i, random_number);
    }

    close(fd);
    return 0;
}
