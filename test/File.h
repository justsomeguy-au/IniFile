#ifndef _FILE_H
#define _FILE_H

#include <strstream>

#include "arduino_compat.h"

class File : public std::strstream {
public:
  File(void);
  File(const char *filename, uint8_t mode);
  File(const File &a);
  ~File();

  File& operator=(const File &a);
  
  void close(void);
  
  size_t read(void);
  size_t read(void *buf, size_t n);

  int peek(void);
  bool seek(int pos);

  bool isOpen(void) const;
  operator bool() const;

  long size(void);
  long position(void);
  long available(void);
	
	void print(const char *str);
	void println(const char *str = NULL);
	
	void print(uint8_t val , uint8_t size = 10);
	void println(uint8_t val, uint8_t size = 10);
	
	void print(uint16_t val , uint8_t size = 10);
	void println(uint16_t val, uint8_t size = 10);
	
	void print(float val);
	void println(float val);
	
private:
  FILE *_f;
  
};

class SDClass {
public:
  SDClass(void) { };
  
  File open(const char *filename, uint8_t mode) const;
	
	 bool begin(const int pin);
	 bool exists(const char *filename);
	 void remove(const char *filename);
	
private:
  
};

extern SDClass SD;


#endif
