
#include "../picprocess.h"

class pic8process:public picprocess{

public :
    pic8process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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

        tmplabel=23 ,tmpnum=15 ,tmpdepth=-14000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=31 ,tmpnum=6 ,tmpdepth=-4000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=32 ,tmpnum=2,tmpdepth=-9000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=34 ,tmpnum=2 ,tmpdepth=-10000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=5 ,tmpnum=4 ,tmpdepth=-1000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=4 ,tmpnum=3 ,tmpdepth=-7000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=25 ,tmpnum=3 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=24 ,tmpnum=1 ,tmpdepth=1000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;



        vect.push_back( edge ) ;

    }

};
