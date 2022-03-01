/*
1pic 2 2outputpic
*/

#include "../../../picprocess/BinaryContourLine.h"
#include "Data.h"

int main(){
    Data data ;

    for( int i=11;i<=16;i++){
        string pth("D:\\workplace\\geoproject\\pictureproject\\data\\deepth") ;
        BinaryContourLine ins ;

        ins.processBinary(pth, i ) ;
    }
    return 0 ;
}
