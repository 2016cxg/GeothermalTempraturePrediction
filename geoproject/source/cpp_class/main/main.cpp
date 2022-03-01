
#include "../picprocess/CoorDeepth.h"

#include "../processpic/pic0/pic0process.h"
#include "../processpic/pic1/pic1process.h"
#include "../processpic/pic2/pic2process.h"
#include "../processpic/pic3/pic3process.h"
#include "../processpic/pic4/pic4process.h"
#include "../processpic/pic5/pic5process.h"
#include "../processpic/pic6/pic6process.h"
#include "../processpic/pic7/pic7process.h"
#include "../processpic/pic8/pic8process.h"
#include "../processpic/pic9/pic9process.h"
#include "../processpic/pic10/pic10process.h"
#include "../processpic/pic11/pic11process.h"
#include "../processpic/pic12/pic12process.h"
#include "../processpic/pic13/pic13process.h"
#include "../processpic/pic14/pic14process.h"
#include "../processpic/pic15/pic15process.h"
#include "../processpic/pic16/pic16process.h"


int calByLayer_Pos(int layer = 0, int posx=3817, int posy=3075 ){

    string imgpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\5cleanedOutputpic\\"+to_string(layer)+".png" ;
    string outpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\6testPos\\"+to_string(layer)+".png" ;

    CoorDeepth *ins ;

    if(layer == 0){
        pic0process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==1){
        pic1process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==2){
        pic2process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==3){
        pic3process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==4){
        pic4process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==5){
        pic5process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==6){
        pic6process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==7){
        pic7process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==8){
        pic8process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==9){
        pic9process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==10){
        pic10process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==11){
        pic11process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==12){
        pic12process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==13){
        pic13process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==14){
        pic14process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==15){
        pic15process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }else if(layer==16){
        pic16process tmpins(imgpth, outpth) ;
        ins = new CoorDeepth(imgpth, outpth, tmpins) ;
    }

    int dpth = ins->calPos(vector<int>{posx,posy}) ;
    cout<<dpth<<" "<<posx<<" "<<posy<<" "<<layer<<endl;
//    ins->outpic() ;

//    ins.testRandomPos() ;

}

int main(){
    for(int i=0;i<=16;i++){
        calByLayer_Pos(i) ;
    }
}

