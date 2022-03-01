
#include "../picprocess.h"

class pic2process:public picprocess{

public :
    pic2process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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

        dfs_idxdpth(42,15,vect,-16000,1000, vect[42][0] ) ;
        dfs_idxdpth(18,7,vect,-13000,1000, vect[18][0] ) ;
        dfs_idxdpth(27,6,vect,-14000,1000, vect[27][0] ) ;
        dfs_idxdpth(6,6,vect,-1000,-1000, vect[6][0] ) ;
        dfs_idxdpth(29,2,vect,-13000,1000, vect[29][0] ) ;
        dfs_idxdpth(26,1,vect,-12000,1000, vect[26][0] ) ;
        dfs_idxdpth(65,5,vect,-13000,1000, vect[65][0] ) ;
        dfs_idxdpth(48,3,vect,-5000,-1000, vect[48][0] ) ;
        dfs_idxdpth(69,6,vect,-4000,-1000, vect[69][0] ) ;
        dfs_idxdpth(62,2,vect,-12000,1000, vect[62][0] ) ;
        dfs_idxdpth(71,2,vect,-12000,1000, vect[71][0] ) ;
        dfs_idxdpth(78,4,vect,-14000,1000, vect[78][0] ) ;
        dfs_idxdpth(83,1,vect,-7000,1000, vect[83][0] ) ;
        dfs_idxdpth(66,2,vect,-4000,-1000, vect[66][0] ) ;
        dfs_idxdpth(58,1,vect,-6000,-1000, vect[58][0] ) ;
        dfs_idxdpth(53,1,vect,-4000,-1000, vect[53][0] ) ;
        dfs_idxdpth(49,1,vect,-4000,-1000, vect[49][0] ) ;
        dfs_idxdpth(56,1,vect,-6000,-1000, vect[56][0] ) ;
        dfs_idxdpth(55,1,vect,-5000,-1000, vect[55][0] ) ;
        dfs_idxdpth(57,1,vect,-5000,-1000, vect[57][0] ) ;
        dfs_idxdpth(46,1,vect,-5000,-1000, vect[46][0] ) ;
        dfs_idxdpth(44,2,vect,-4000,-1000, vect[44][0] ) ;
        dfs_idxdpth(31,1,vect,-11000,-1000, vect[31][0] ) ;
        dfs_idxdpth(22,2,vect,-2000,-1000, vect[22][0] ) ;
        dfs_idxdpth(13,1,vect,-1000,-1000, vect[13][0] ) ;
        dfs_idxdpth(32,2,vect,-2000,1000, vect[32][0] ) ;

        vect.push_back( edge ) ;

    }

};
