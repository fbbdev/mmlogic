#include <stdio.h>
#include <stdlib.h>

main( int argc, char *argv[ ], char *envp[ ] )
{
FILE* file;
unsigned int address;
unsigned int value;
unsigned int oldvalue;

if ((argc < 3) || (argc > 4))
   {
   printf("binedt Filename Address [Value]\n");
   return 1;
   }

sscanf(argv[2],"%u", &address);

if(argc == 4) sscanf(argv[3],"%u", &value);

if ((file = fopen(argv[1],"rb+")) == NULL)
   {
   printf("Cannot open %s\n", argv[1]);
   return 1;
   }

fseek(file,address,SEEK_SET);
oldvalue = fgetc(file);
if(argc == 3) printf("%s %s %s %u\n",argv[0],argv[1], argv[2], oldvalue);

fseek(file,address,SEEK_SET);
if(argc == 4) fputc(value,file);
fclose(file);

return 1;

}