#include "bw_spi_8bit.cpp"

int main(int argc, char *argv[])
{
const char *device = "/dev/spidev0.0";
bw_spi_8bit  a20(device,0x86,0x23,0x0);
   for (int val=0;val<=0xFF;val+=0x20) {
        a20.setValue(val);
        sleep(1);
    }
  exit (0);
}


