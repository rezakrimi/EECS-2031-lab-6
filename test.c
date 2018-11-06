#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
if(argc == 1)
 printf("%s\n", argv[0]);
if(argc == 2)
 printf("%s", argv[1]);
 /*
 FILE *fd;
 int n;
 char buf[101];
 if((fd = fopen("test.text", "r")) == (FILE *)NULL) {
 perror("open of test.text failed");
 (void) exit(1);
 }
 n = fread(buf, 1, 100, fd);
 if(n == 0) {
 perror("read fails!");
 exit(1);
 }
 buf[n] = '\0';
 fprintf(stdout, "Read '%s'\n", buf);
 (void) fclose(fd);
 return 0;
 */
}
