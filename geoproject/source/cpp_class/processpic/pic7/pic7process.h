
#include "../picprocess.h"

class pic7process:public picprocess{

public :
    pic7process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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



        int tmplabel,tmpnum,tmpdepth,tmpinc ;

        tmplabel=41 ,tmpnum=16 ,tmpdepth=-15000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=23 ,tmpnum=9 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=1 ,tmpnum=3,tmpdepth=-3000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=2 ,tmpnum=4 ,tmpdepth=-5000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=53 ,tmpnum=5 ,tmpdepth=-5000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=54 ,tmpnum=1 ,tmpdepth=-9000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=50 ,tmpnum=1 ,tmpdepth=-10000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=54 ,tmpnum=1 ,tmpdepth=-9000 ,tmpinc = -1000 ;
        tmplabel=47 ,tmpnum=1 ,tmpdepth=-3000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=42 ,tmpnum=1 ,tmpdepth= 0 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=43 ,tmpnum=1 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=44 ,tmpnum=1 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=10 ,tmpnum=1 ,tmpdepth=-4000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=22 ,tmpnum=1 ,tmpdepth=-6000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=46 ,tmpnum=1 ,tmpdepth=-3000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=19 ,tmpnum=1 ,tmpdepth=-3000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=21 ,tmpnum=1 ,tmpdepth=-3000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=25 ,tmpnum=1 ,tmpdepth=-4000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=31 ,tmpnum=1 ,tmpdepth=-4000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=20 ,tmpnum=1 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=8 ,tmpnum=1 ,tmpdepth=-3000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=14 ,tmpnum=1 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=12 ,tmpnum=1 ,tmpdepth=-1000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=45 ,tmpnum=1 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;



        vect.push_back( edge ) ;

    }

};
