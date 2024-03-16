#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    printf("%s was running with %d args\n", argv[0], argc-1);

    return 0;
}
