// http://apple.stackexchange.com/a/199958
#include <linux/hidraw.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {
  if (argc != 2 || strcmp(argv[1], "-h") == 0) {
    printf("Pass a hidraw device as the first and only parameter!\n");
    printf("You may find the right device with:\n");
    printf("  dmesg | grep Apple | grep Keyboard | grep input0 | tail -1 | "
           "sed -e 's/.hidraw\([[:digit:]]\+\)./\/dev\/hidraw\1/'\n");
    return 1;
  }
  int fd, i, res, desc_size = 0;
  char buf[256];
  struct hidraw_devinfo info;
  char *device = argv[1];
  fd = open(device, O_RDWR | O_NONBLOCK);
  if (fd < 0) {
    perror("Unable to open device");
    return 1;
  }
  memset(&info, 0, sizeof(info));
  memset(buf, 0, sizeof(buf));
  // Get Report Descriptor Size
  res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
  if (res < 0) {
    perror("HIDIOCGRDESCSIZE");
  }
//  if (desc_size != 75) {
//    printf("Error: unexpected descriptor size %d; you've probably got "
//           "the wrong hidraw device!\n", desc_size);
//    return 1;
//  }
  // Get Raw Info
  res = ioctl(fd, HIDIOCGRAWINFO, &info);
  if (res < 0) {
    perror("HIDIOCGRAWINFO");
  } else {
    if (info.vendor != 0x05ac) {
      printf("Error: Wrong vendor ID, make sure you got the right "
             "hidraw device!\n");
      return 1;
    }
    if (info.product != 0x0250) {
      printf("Warning: Unknown product ID 0x%x!\n", info.product);
    }
  }
  // Get Feature
  buf[0] = 0x09;  // Report Number
  res = ioctl(fd, HIDIOCGFEATURE(256), buf);
  if (res < 0) {
    perror("HIDIOCGFEATURE");
  } else {
    printf("HID Feature Report (before change):\n\t");
    for (i = 0; i < res; i++) printf("%hhx ", buf[i]);
    puts("\n");
  }
  // Set Feature
  buf[0] = 0x09;  // Report Number
  buf[1] = 0x00;  // Report data
  buf[2] = 0x00;  // padding
  buf[3] = 0x00;  // padding
  res = ioctl(fd, HIDIOCSFEATURE(4), buf);
  if (res < 0) {
    perror("HIDIOCSFEATURE");
  } else {
    printf("Caps lock delay disabled.\n");
  }
  // Get Feature
  buf[0] = 0x09;  // Report Number
  res = ioctl(fd, HIDIOCGFEATURE(256), buf);
  if (res < 0) {
    perror("HIDIOCGFEATURE");
  } else {
    printf("HID Feature Report (after change):\n\t");
    for (i = 0; i < res; i++) printf("%hhx ", buf[i]);
    puts("\n");
  }
  close(fd);
  return 0;
}
