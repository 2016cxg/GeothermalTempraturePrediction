/*
1pic 2 2outputpic
*/

#include "../../../picprocess/BinaryContourLine.h"

int main(){
    string pth("D:\\workplace\\geoproject\\pictureproject\\data\\deepth") ;
    BinaryContourLine ins ;

    ins.processBinary(pth, 1) ;
    return 0 ;
}
