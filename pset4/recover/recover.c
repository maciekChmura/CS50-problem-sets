/*
recover
*/
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

// ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }

    // 1 open memory card file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open card.raw\n");
        return 2;
    }

    //buffer for 512 block of bytes
    unsigned char buffer[512];   //magic number!
    //file ID
    int fileID = 0;
    //file placeholder
    FILE* picture = NULL;

    //status of working on file
    bool working = false;

    //go trough card.raw
    // 5 detect end of file
    while (fread(buffer, 512, 1, file) == true) {

        // 2 find beginning of JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
        // 3 open a new JPEG

            // found the beggining of file AND have opened a file!!!!
            // have to close old file and open a new one
            if (working == true) {
                //close opened file
                fclose(picture);
            } else {
                // change status to working and go open a new file
                working = true;
            }

        char fileName[8];
        sprintf(fileName, "%03i.jpg", fileID);
        picture = fopen(fileName, "a");
        fileID++;

        }
        if( working == true) {
            // 4 write 512 bytes untill new JPEG is found
            fwrite(&buffer, 512, 1, picture);
        }
    }
    //end of file
    fclose(picture);
    fclose(file);

    return 0;
}