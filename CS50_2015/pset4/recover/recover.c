#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile.\n");
        return 1;
    }
    
    char *infile = argv[1];   
    FILE *input = fopen(infile, "r");   
    FILE *output;
    if(input == NULL)
    {
        fclose(input);
        fprintf(stderr, "File can not be opened.\n");
        return 2;
    }
    
    int counter = 0, open = 0;
    uint8_t memory[512];
    uint8_t checker[4];
    uint8_t correct1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t correct2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    fread(&memory, 512, 1, input);

    while(fread(&memory, 512, 1, input) > 0)
    {
        for(int j = 0; j < 4; j++)
        {
            checker[j] = memory[j];   
        }
        
        if(memcmp(correct1, checker, 4) == 0 || memcmp(correct2, checker, 4) == 0)
        {   
            
            char name[10];
            sprintf(name, "%03d.jpg", counter);
            
            if(open == 0)
            {
                output = fopen(name, "w");
                fwrite(&memory, sizeof(memory), 1, output);
                open = 1;
            }
            if(open == 1)
            {
                fclose(output);
                output = fopen(name, "w");
                fwrite(&memory, sizeof(memory), 1, output);
                counter = counter +1;
            }
            
        }
        else
        {
            if(open == 1)
            {
                fwrite(&memory, sizeof(memory), 1, output);   
            }
        }
        
    }
    fclose(input);
}