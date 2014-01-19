#ifndef BW_SPI_8BIT_H
#define BW_SPI_8BIT_H

class bw_spi_8bit {
public:
    bw_spi_8bit(const char *d=0,const char a=0,const char r=0,const char v=0);
    ~bw_spi_8bit();
    void setError(const char *e);
    void setAddress(const char a);
    void setRegister(const char r);
    void setValue(const char v);
    void setDevice(const char *d);
    
    char* device();
    char address();
    char reg();
    char value();
    void closespi();
    void clearError();
    char* error();

protected:
    char *device_loc;
    char addr_v;
    char register_v;
    char value_v;
    int fd;
    char *buf;
    char *error_str;
    uint8_t bits ;
    uint32_t speed ;
    uint16_t delay ;
    uint8_t spi_mode;
};

#endif // BW_SPI_8BIT_H
