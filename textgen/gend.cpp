#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <assert.h>


int main ( int argc , char ** argv ) {

    setbuf(stdout, NULL);

    long long k = 1000000 ;

    if ( argc < 2 ) {
        printf( " gen <row number> <pause value ms> <row block size> \n " ) ;

        exit( 0 ) ;
    } else {
        k = ( long long ) atof ( argv[1] ) ;
    }

    long long pp = 0 ;
    if ( argc > 2 ) {
        pp = ( long long ) atof ( argv[2] ) ;
    }


    long long blockSize = 1 ;
    if ( argc > 3 ) {
        blockSize = ( long long ) atof ( argv[3] ) ;
    }

    //fflush(stdout);


    for ( long long i = 0; i< k ; ++i ) {
        printf( "%g %d qwertyuiopasdfghjklzxcvbnm*****************************************************\n" , i*1.0 , i );

        if ( blockSize > 0 && i % blockSize == 0 ) {
            usleep( 1000 * pp ) ;
        }
    }
}

