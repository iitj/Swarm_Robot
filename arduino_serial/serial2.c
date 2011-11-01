//Arduino Serial Communication Codes
//Date: 1/11/2011
/*This further tests the working of Serial Communication with the Arduino Board
In this code, we can write an integer to the Arduino. To test the working of the code, upload serial2.pde onto the arduino and then open the Serial Monitor of the Arduino Software to check for the data you have sent.
*/
#include <stdio.h>
#include <stdlib.h>         //System Standard Library
#include <stdint.h>         //Useful for Embedded Programming
#include <string.h>         //For Strings
#include <unistd.h>         //Used to call the POSIX Library
#include <fcntl.h>          //File Control
#include <errno.h>          //To determine type of Error
#include <termios.h>        //POSIX terminal control
#include <sys/ioctl.h>      
#include <getopt.h>


void usage(void);
int serialport_init(const char* serialport);
int serialport_writebyte(int fd, uint8_t b);

void usage(void)
{
  printf("This program opens the port to the Arduino Board for Communication.\n Usage: serial1 <portname> <data>.\n Now to send a Number to the Arduino give Data as a number.\n");
}

int main(int argc, char* argv[])
{
  int fd = 0;
  char serialport[100];
  int baudrate = B9600;
  char buf[256];
  int rc,n;

  if(argc == 1)
    {
      usage();
      exit(0);
    }

  fd = serialport_init(argv[1]);
  if(fd == -1)
    {
      fprintf(stderr, "Error in opening the port.\n");
      exit(-1);
    }
  else
    {
      printf("Success in opening the Port with BaudRate 9600.\n");
    }

  if(argc == 3)
    {
      n = strtol(argv[2], NULL, 10);      
      //This function the input string into a number
      rc = serialport_writebyte(fd, (uint8_t)n);
      if(rc == -1)
	{
	  fprintf(stderr, "Error in sending data to the Arduino.\n");
	  exit(-1);
	}
      else
	{
	  printf("Success in Writing Data.\n");
	}
    }

}


//This is using the POSIX Library
//A good link to understanding the library is given in this link:
//http://en.wikibooks.org/wiki/Serial_Programming/termios
//This program opens port at 9600 baudrate
int serialport_init(const char* serialport)
{
  struct termios toptions;
  int fd;
  //fd is the file handler for the device

  fd = open(serialport, O_RDWR | O_NOCTTY | O_NDELAY);
  /*O_RDWR - Opens the Port for Reading and Writing
    O_NOCTTY - Port never will control the process
    O_NDELAY - Use Non Blocking I/O
  */

  if(fd == -1)
    {
      perror("init_serialport: Unable to open the port");
      return -1;
    }
  
  if(tcgetattr(fd, &toptions) < 0)
    {
      perror("init_serialport: Couldn't get term attributes");
      return -1;
    }

  speed_t brate = B9600;
  //Assuming that always 9600 will be used

  cfsetispeed(&toptions, brate);
  cfsetospeed(&toptions, brate);
  //Setting the input and output speed

  //Here on the settings below involves knowledge of Embedded Programming
  //Setting 8N1 flow of Data
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;

  // no flow control
  toptions.c_cflag &= ~CRTSCTS;
  
  toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
  toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
  
  toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
  toptions.c_oflag &= ~OPOST; // make raw

  // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
  toptions.c_cc[VMIN]  = 0;
  toptions.c_cc[VTIME] = 20;
    
  if( tcsetattr(fd, TCSANOW, &toptions) < 0) 
    {
      perror("init_serialport: Couldn't set term attributes");
      return -1;
    }

    return fd;
}
  
int serialport_writebyte( int fd, uint8_t b)
{
  int n = write(fd, &b, 1);
  if( n != 1)
    return -1;
  return 0;
}

