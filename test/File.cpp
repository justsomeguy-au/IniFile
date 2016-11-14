#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "File.h"
#include <string>
#include <iostream> // DEBUGGING
using namespace::std;

SDClass SD;

File SDClass::open(const char *filename, uint8_t mode) const
{
  return File(filename, mode);
}

bool SDClass::begin(const int pin)
{
	return true;
}

bool SDClass::exists(const char *filename)
{
	struct stat buffer;
	return (stat (filename, &buffer) == 0);
}


void SDClass::remove(const char *filename)
{
	::remove(filename);
}



File::File(void)
{
  _f = NULL;
}

File::File(const char *filename, uint8_t mode)
{
  //cout << "Opening " << filename << " with mode "
  //   << (mode & O_WRONLY ? "r+" : "r") << endl;
	if (mode == O_WRONLY)
		_f = fopen(filename, "w+");
	else if (mode  == O_RDONLY)
		_f = fopen(filename, "r+");
	else
		_f = fopen(filename, "r");
}

File::File(const File &a)
{
  _f = a._f;
}

File::~File()
{
  //close();
}

File& File::operator=(const File &a)
{
  _f = a._f;
  return *this;
}

void File::close(void)
{
  if (_f != NULL)
    fclose(_f);
  _f = NULL;
}

bool File::isOpen(void) const
{
  return _f != NULL;
}

File::operator bool() const
{
  return isOpen();
} 


long File::size(void)
{
  if (!isOpen())
    return -1;
  //return size() - position();
  long cur = ftell(_f);
  fseek(_f, 0, SEEK_END); // seek to eof
  long sz = ftell(_f);
  fseek(_f, cur, SEEK_SET); // return to initial position
  return sz; 
}

long File::position(void)
{
  if (!isOpen())
    return -1;
  return ftell(_f);
}
 

int File::available(void)
{
  if (!isOpen())
    return 0;
  return size() - position();
}

int File::read(void)
{
  if (!available())
    return -1;
  char c;
  fread(&c, 1, 1, _f);
  return c;
}

int File::read(void *buf, int n)
{
  return fread(buf, 1, n ,_f);
}

int File::peek(void)
{
  if (!available())
    return -1;

  char c;
  fread(&c, 1, 1, _f);
  ungetc(c, _f);
  return c;
}

bool File::seek(int pos)
{
  if (_f == NULL)
    return false;
  return (fseek(_f, pos, SEEK_SET) == -1 ? false : true);
}

void File::print(const char *str)
{
	if (str && strlen(str) > 0)
		fwrite(str, strlen(str), 1, _f);
}

void File::println(const char *str)
{
	char end = '\n';
	
	if (str && strlen(str) > 0)
		fwrite(str, strlen(str), 1, _f);
	fwrite(&end, 1, 1, _f);
}


void File::print(uint8_t val, uint8_t size)
{
	char buff[50];
	
	switch (size)
	{
		case 8:  sprintf(buff, "%o", val); break;
		case 10: sprintf(buff, "%d", val); break;
		case 16: sprintf(buff, "%X", val); break;
	}
	
	fwrite(buff, strlen(buff), 1, _f);
}

void File::println(uint8_t val, uint8_t size)
{
	char buff[50];
	
	switch (size)
	{
		case 8:  sprintf(buff, "%o\n", val); break;
		case 10: sprintf(buff, "%d\n", val); break;
		case 16: sprintf(buff, "%X\n", val); break;
	}
	
	fwrite(buff, strlen(buff), 1, _f);
}

void File::print(uint16_t val, uint8_t size)
{
	char buff[50];
	
	switch (size)
	{
		case 8:  sprintf(buff, "%o", val); break;
		case 10: sprintf(buff, "%d", val); break;
		case 16: sprintf(buff, "%X", val); break;
	}
	
	fwrite(buff, strlen(buff), 1, _f);
}

void File::println(uint16_t val, uint8_t size)
{
	char buff[50];
	
	switch (size)
	{
		case 8:  sprintf(buff, "%o\n", val); break;
		case 10: sprintf(buff, "%d\n", val); break;
		case 16: sprintf(buff, "%X\n", val); break;
	}
	
	fwrite(buff, strlen(buff), 1, _f);
}






void File::print(float val)
{
	char buff[20];
	sprintf(buff, "%f", val);
	fwrite(buff, strlen(buff), 1, _f);
}

void File::println(float val)
{
	char buff[20];
	sprintf(buff, "%f\n", val);
	fwrite(buff, strlen(buff), 1, _f);
}


