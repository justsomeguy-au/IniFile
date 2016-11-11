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
  
  int read(void);
  int read(void *buf, int n);

  int peek(void);
  bool seek(int pos);

  bool isOpen(void) const;
  operator bool() const;

  long size(void);
  long position(void);
  int available(void);
	
	void print(const char *str);
	void print(uint8_t val , uint8_t size = 10);
	void println(const char *str = NULL);
	void println(uint8_t val, uint8_t size = 10);
	
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
