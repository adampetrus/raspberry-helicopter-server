#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <linux/i2c-dev.h>
#include "bw_spi_8bit.h"

bw_spi_8bit::bw_spi_8bit(const char *d,const char a,const char r,const char v) {
error_str =0;
buf =0;
device_loc=0;
fd =0;

bits = 8;
speed = 450000;
delay = 2;
spi_mode =0;

if (d) setDevice(d);
if (error_str) return;
if (a) setAddress(a);
if (error_str) return;
if (r) setRegister(r);
if (error_str) return;
if (v) setValue(v);


}
bw_spi_8bit::~bw_spi_8bit() { 
    closespi();
    if (device_loc) delete device_loc;
    device_loc =0;
    if (error_str) delete error_str;
    error_str =0;
    if (buf) delete buf;
    buf =0;
}
void bw_spi_8bit::setDevice(const char *d) {
    if (error_str) return;
    if (!d) { device_loc =0; return; }
    if (device_loc) delete device_loc;
    const int devlen = strlen(d);
    device_loc = new char[devlen];
    strcpy(device_loc,d);
}

void bw_spi_8bit::setError(const char *e) {
    if (!e) { e =0; return; }
    if (error_str) delete error_str;
    const int errlen = strlen(e);
    error_str = new char[errlen];
    strcpy(error_str,e);
    printf("%s\n",e);
    }


void bw_spi_8bit::clearError() {
    if (error_str) delete error_str;
    error_str =0;
}


void bw_spi_8bit::closespi() {
    if (fd) close(fd);
    fd =0;
}

void bw_spi_8bit::setAddress(const char a) {
    if (fd) closespi();
    
    fd = open(device_loc, O_RDWR);
    
    if (fd<0) setError("Can't spi open device");
    if (error_str) return;
    addr_v =a;
    
     int ret;
  /*
   * spi mode
   */
  // printf ("setting spi mode. \n");
  ret = ioctl(fd, SPI_IOC_WR_MODE, &spi_mode);
  if (ret == -1)
    setError("can't set spi mode");

  ret = ioctl(fd, SPI_IOC_RD_MODE, &spi_mode);
  if (ret == -1)
    setError("can't get spi mode");

  /*
   * bits per word
   */
  ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
  if (ret == -1)
    setError("can't set bits per word");

  ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
  if (ret == -1)
    setError("can't get bits per word");

  /*
   * max speed hz
   */
  ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  if (ret == -1)
    setError("can't set max speed hz");

  ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
  if (ret == -1)
    setError("can't get max speed hz");

  //printf("spi mode: %d\n", spi_mode);
  //printf("bits per word: %d\n", bits);
  //printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);
    
}
void bw_spi_8bit::setRegister(char r) { 
    if (error_str) return;
    register_v = r; 
}
void bw_spi_8bit::setValue(char v) { 
  if (error_str) return;
  value_v =v;
  char bufx[5]; 
  bufx[0] = addr_v;
  bufx[1] = register_v;
  bufx[2] = value_v;
   int tlen =3;
   int rlen =0;
  int ret;
  struct spi_ioc_transfer tr;
  tr.delay_usecs = delay;
  tr.speed_hz = speed;
  tr.bits_per_word = bits;
 

  if (rlen > tlen) tr.len = rlen; 
  else             tr.len = tlen; 
  tr.tx_buf = (unsigned long) bufx; 
  tr.rx_buf = (unsigned long) bufx; 
  
  ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
  if (ret < 1)
  setError("can't send spi message");

}

char* bw_spi_8bit::device() { return device_loc; }
char bw_spi_8bit::address() { return addr_v; }
char bw_spi_8bit::reg() { return register_v; }
char bw_spi_8bit::value() { return value_v; }



