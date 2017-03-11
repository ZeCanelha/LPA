#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    int n_lobos;
    int height;
    int width;

    int i;

    while(1)
    {
        scanf("%d %d",&width,&height);
        if ( width == 0 && height == 0)
        {
            break;
        }


        scanf("%d",&n_lobos);
        int cord_lobos[n_lobos][2];

        for ( i = 0; i < n_lobos; i++ )
        {
            scanf("%d %d",&cord_lobos[i][0],&cord_lobos[i][1]);
        }

        

    }




    return 0;
}
