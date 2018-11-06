#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double strtotemp(char* in){
    int temp = atoi(in);
    double remaining = temp % 1000;
    temp /= 1000;
    remaining = remaining /1000;
    double result = temp + remaining;
    return result;
}

double readTemp(char* serial){
    FILE *fd;
 int n;
 char buf[101];
 char path[80];
 strcpy(path, "/sys/bus/w1/devices/");
strcat(path, serial);
strcat(path, "/w1_slave");
 if((fd = fopen(path, "r")) == (FILE *)NULL) {
 perror("open of test.text failed");
 (void) exit(1);
 }
 n = fread(buf, 1, 100, fd);
 if(n == 0) {
 perror("read fails!");
 exit(1);
 }
 buf[n] = '\0';
 
 char temperature[6];
 memcpy( temperature, &buf[69], 6);
 temperature[5] = '\0';
 (void) fclose(fd);
return strtotemp(temperature);
}

void wait(int s){
    double start = time(NULL);
    double current = time(NULL);
    while(current - start < s){
        current = time(NULL);
    }
}

int main(int argc, char *argv[])
{
    double prevTemperature, newTemperature;
    double min;
    double max;
if(argc == 1)
 printf("no arguments were given\n");
else{
  prevTemperature = readTemp(argv[1]);
  max = prevTemperature;
  min = prevTemperature;
  printf("\n *** %f ***\n", prevTemperature);
  wait(1);
  while(1){
    newTemperature = readTemp(argv[1]);
    
    if(newTemperature > max){
        max = newTemperature;
    }
    if(newTemperature < min){
        min = newTemperature;
    }
    
    if(fabs(newTemperature - prevTemperature) > 1){
        printf("\n new assignment *** %f ***\n", newTemperature);
        printf("\n max: %f\n", max);
        printf("\n min: %f\n", min);
        prevTemperature = newTemperature;
    }
    wait(1);
  }
}
return 0;
}
