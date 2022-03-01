
#include "../../picprocess/CoorDeepth.h"
#include "pic0process.h"

int main(){
    string imgpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\5cleanedOutputpic\\0.png" ;
    string outpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\6testPos\\0.png" ;
    CoorDeepth<pic0process> ins(imgpth, outpth) ;

    int dpth = ins.calPos(vector<int>{3817,3075}) ;
    cout<<dpth<<endl;
    ins.outpic() ;

//    ins.testRandomPos() ;


}

