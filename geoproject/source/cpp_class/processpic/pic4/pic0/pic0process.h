
#include "../picprocess.h"

class pic0process:public picprocess{

public :
    pic0process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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

        sort( vect.begin(), vect.end(), cmp ) ;
    //    for( int i=0;i<vect.size() ;i++){
    //        cout<<vect[i].size()<<endl;
    //    }


        dfs_idxdpth(25,16,vect,-17000,1000, vect[25][0] ) ;
        dfs_idxdpth(21,9,vect,-5000,-1000, vect[21][0] ) ;
        dfs_idxdpth(55,5,vect,-11000,1000, vect[55][0] ) ;
        dfs_idxdpth(53,11,vect,-14000,1000, vect[53][0] ) ;
        dfs_idxdpth(43,1,vect,-5000,1000, vect[43][0] ) ;
        dfs_idxdpth(85,2,vect,-8000,-1000, vect[85][0] ) ;
        dfs_idxdpth(20,1,vect,-9000,-1000, vect[20][0] ) ;
        dfs_idxdpth(0,7,vect,-8000,-1000, vect[0][0] ) ;
        dfs_idxdpth(9,3,vect,-5000,-1000, vect[9][0] ) ;
        dfs_idxdpth(44,4,vect,-13000,1000, vect[44][0] ) ;
        dfs_idxdpth(15,3,vect,-6000,-1000, vect[15][0] ) ;
        dfs_idxdpth(61,3,vect,-14000,1000, vect[61][0] ) ;
        dfs_idxdpth(10,3,vect,-5000,-1000, vect[10][0] ) ;
        dfs_idxdpth(40,2,vect,-14000,1000, vect[40][0] ) ;
        dfs_idxdpth(23,1,vect,-3000,1000, vect[23][0] ) ;
        dfs_idxdpth(19,4,vect,-2000,-1000, vect[19][0] ) ;
        dfs_idxdpth(11,4,vect,-1000,-1000, vect[11][0] ) ;
        dfs_idxdpth(8,3,vect,-3000,-1000, vect[8][0] ) ;
        dfs_idxdpth(80,1,vect,-9000,-1000, vect[80][0] ) ;
        dfs_idxdpth(76,1,vect,-9000,-1000, vect[76][0] ) ;
        dfs_idxdpth(88,1,vect,-11000,-1000, vect[88][0] ) ;
        dfs_idxdpth(18,1,vect,-9000,-1000, vect[18][0] ) ;
        dfs_idxdpth(12,1,vect,-7000,-1000, vect[12][0] ) ;
        dfs_idxdpth(51,1,vect,-5000,-1000, vect[51][0] ) ;
        dfs_idxdpth(34,1,vect,-7000,-1000, vect[34][0] ) ;
        dfs_idxdpth(16,1,vect,-10000,-1000, vect[16][0] ) ;
        dfs_idxdpth(3,1,vect,-6000,-1000, vect[3][0] ) ;
        dfs_idxdpth(14,1,vect,-6000,-1000, vect[14][0] ) ;
        dfs_idxdpth(5,1,vect,-13000,-1000, vect[5][0] ) ;
        dfs_idxdpth(1,1,vect,-13000,-1000, vect[1][0] ) ;
        dfs_idxdpth(4,1,vect,-4000,-1000, vect[4][0] ) ;

        vect.push_back( edge ) ;

    }

};
