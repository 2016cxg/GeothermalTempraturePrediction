/*
1pic 2 2outputpic
*/

#include "../../../picprocess/BinaryContourLine.h"
#include "Data.h"

int main(){
    Data data ;

    string pth("D:\\workplace\\geoproject\\pictureproject\\data\\deepth") ;
    BinaryContourLine ins ;

    ins.processBinary(pth, data.num ) ;
    return 0 ;
}
