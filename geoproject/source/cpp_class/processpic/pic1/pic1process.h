
#include "../picprocess.h"

class pic1process:public picprocess{

public :
    pic1process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
        construct(imgpth, outpth_) ;
    }

    void construct(string imgpth, string outpth_ ){

        vector<vector<int> > edge ;
        int edgei,edgej ;
        for( int i=1266; i<4369; i++ ){
            for( int j=1129; j<7820; j++ ){
                Vec3b & pxl = img.at<Vec3b>( i,j) ;

                vector<vector<int> > tmpvect ;

                if( (pxl[0]==255) && (pxl[1]+pxl[2]==0) ){
                    bfs( img, i,j, tmpvect ) ;
                    vect.push_back( tmpvect ) ;
                }
                else if( (pxl[1]==255) &&(pxl[0]+pxl[2] ==0)){
                    edgei = i ;
                    edgej = j ;
                }
                else{
                    setPixel( pxl, 255, 255, 255) ;
                }
            }
        }
        bfsEdge(img, edgei,edgej, edge) ;

        dfs_idxdpth(38,16,vect,-17000,1000, vect[38][0] ) ;
        dfs_idxdpth(41,5,vect,-11000,1000, vect[41][0] ) ;
        dfs_idxdpth(51,2,vect,-12000,-1000, vect[51][0] ) ;
        dfs_idxdpth(56,1,vect,-13000,-1000, vect[56][0] ) ;
        dfs_idxdpth(59,4,vect,-7000,1000, vect[59][0] ) ;
        dfs_idxdpth(69,3,vect,-12000,-1000, vect[69][0] ) ;
        dfs_idxdpth(63,2,vect,-12000,-1000, vect[63][0] ) ;
        dfs_idxdpth(71,3,vect,-11000,1000, vect[71][0] ) ;
        dfs_idxdpth(18,7,vect,-14000,1000, vect[18][0] ) ;
        dfs_idxdpth(17,5,vect,-14000,1000, vect[17][0] ) ;
        dfs_idxdpth(6,8,vect,-1000,-1000, vect[6][0] ) ;
        dfs_idxdpth(55,4,vect,-13000,1000, vect[55][0] ) ;
        dfs_idxdpth(42,2,vect,-6000,-1000, vect[42][0] ) ;
        dfs_idxdpth(44,1,vect,-5000,-1000, vect[44][0] ) ;
        dfs_idxdpth(45,1,vect,-5000,-1000, vect[45][0] ) ;
        dfs_idxdpth(40,1,vect,-7000,-1000, vect[40][0] ) ;
        dfs_idxdpth(58,1,vect,-8000,-1000, vect[58][0] ) ;
        dfs_idxdpth(57,1,vect,-4000,-1000, vect[57][0] ) ;
        dfs_idxdpth(46,1,vect,-6000,-1000, vect[46][0] ) ;
        dfs_idxdpth(32,2,vect,-14000,1000, vect[32][0] ) ;
        dfs_idxdpth(23,1,vect,-12000,1000, vect[23][0] ) ;

        vect.push_back( edge ) ;

    }

};
