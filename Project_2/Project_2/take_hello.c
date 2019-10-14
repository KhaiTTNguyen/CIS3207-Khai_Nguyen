#include <stdio.h>

int main(int argc, char * argv[]){
        char buff[1024] = {0};
        fgets(buff, sizeof (buff), stdin);
        printf("Received: %s\n", buff);
        return 0;
}

