#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    int n_lobos;
    int height;
    int width;
    int n_paths;

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



        if ( n_paths > 1 )
        {
            printf("There are %d paths from Little Red Riding Hood's house to her grandmother's house.\n",n_paths);
        }
        if ( n_paths == 1 )
        {
            printf("There is one paths from Little Red Riding Hood's house to her grandmother's house.\n")
        }
        else
        {
            printf("There is no path.\n")
        }


    }




    return 0;
}
