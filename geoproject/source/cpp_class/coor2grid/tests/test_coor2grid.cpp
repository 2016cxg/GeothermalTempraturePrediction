
#include "../coor2grid.h"

int main(){
//    cout<<"aaaaaa"<<endl;
    string settings = "D:\\workplace\\geoproject\\pictureproject\\source\\cpp\\coor2grid\\settings" ;
    string outputs = "D:\\workplace\\geoproject\\pictureproject\\source\\cpp\\coor2grid\\outputs" ;
    Coor2grid c2g(settings, outputs ) ;

    vector<int> piccoor = c2g.trasCoor2Grid(vector<double>{37.65,80.35}) ;

//    cout<<"===="<<endl;
    cout<<piccoor[0]<<" "<<piccoor[1]<<endl;
    return 0;
}
