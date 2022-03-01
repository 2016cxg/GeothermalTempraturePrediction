
#include "../../picprocess/CoorDeepth.h"
#include "pic2process.h"
#include "cpp/Data.h"

int main(){
    Data data ;

    string imgpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\5cleanedOutputpic\\"+to_string(data.num)+".png" ;
    string outpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\6testPos\\"+to_string(data.num)+".png" ;
    CoorDeepth<pic2process> ins(imgpth, outpth) ;

    int dpth = ins.calPos(vector<int>{3817,3075}) ;
    cout<<dpth<<endl;
    ins.outpic() ;

//    ins.testRandomPos() ;


}

