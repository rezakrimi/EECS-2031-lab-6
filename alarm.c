#include <string.h>
#include <math.h>
#include "ifttt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double strtotemp(char* in){
    double result;
    int temp = atoi(in);
    double remaining = temp % 1000;
    temp /= 1000;
    remaining = remaining /1000;
    result = temp + remaining;
    return result;
}

double readTemp(char* serial){
    FILE *fd;
 int n;
 char buf[101];
 char path[80];
 char temperature[6];
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

void doubleToStr(double num, char* result){
    sprintf(result, "%2.4f", num);
}

int main(int argc, char *argv[])
{
    double prevTemperature, newTemperature;
    double min;
    double max;
    char maxStr[10];
    char minStr[10];
    char tempStr[10];
if(argc == 1)
 printf("no arguments were given\n");
else{
  prevTemperature = readTemp(argv[1]);
  max = prevTemperature;
  min = prevTemperature;
  doubleToStr(max, maxStr);
  doubleToStr(min, minStr);
  doubleToStr(prevTemperature, tempStr);
  printf("\n *** %f ***\n", prevTemperature);
  ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/Cnfhg7_qaNykhn6Du0ekJ", tempStr, maxStr, minStr);
  wait(1);
  while(1){
    newTemperature = readTemp(argv[1]);
    
    if(newTemperature > max){
        max = newTemperature;
        doubleToStr(max, maxStr);
    }
    if(newTemperature < min){
        min = newTemperature;
        doubleToStr(min, minStr);
    }
    
    if(fabs(newTemperature - prevTemperature) > 1){
        doubleToStr(newTemperature, tempStr);
        printf("\n new assignment *** %f ***\n", newTemperature);
        printf("\n max: %f\n", max);
        printf("\n min: %f\n", min);
        ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/Cnfhg7_qaNykhn6Du0ekJ", tempStr, maxStr, minStr);
        prevTemperature = newTemperature;
    }
    wait(1);
  }
}
return 0;
}
