#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void extract(FILE* in, FILE* out);

int main(int argc, char* argv[])
{
    FILE* in = fopen(argv[1], "rb");
    FILE* out = fopen(argv[2], "wb");
    
    extract(in, out);

    return 0;
}

void extract(FILE* in, FILE* out)
{
    int size = 0;
    char* txt = NULL;
    int id = 0;
    
    txt = calloc(1, sizeof(char));
    
    while(strcmp(txt, "eof") != 0)
    {
        free(txt);
        
        fread(&size, sizeof(char), 1, in);
        
        while(size == 0)
        {
            /*fprintf(out, "0x%lX ", ftell(in));
            fflush(out);*/
            fread(&size, sizeof(char), 1, in);
        }
        
        fread(&id, sizeof(char), 1, in);

        if(id != 0x01)
        {
            fseek(in, -1, SEEK_CUR);
        }
        else
        {
            printf("0x%.8lX\n", ftell(in));
        }
        
        txt = calloc(size + 1, sizeof(char));
        
        fread(txt, sizeof(char), size, in);
    
        fprintf(out, "%s\n", txt);
    }
}