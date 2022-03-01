
#include "../picprocess.h"

class pic10process:public picprocess{

public :
    pic10process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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

        tmplabel=25 ,tmpnum=7 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=14 ,tmpnum=6 ,tmpdepth=-5000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=2 ,tmpnum=5,tmpdepth=-6000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=23 ,tmpnum=2 ,tmpdepth=0 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=26 ,tmpnum=1 ,tmpdepth=-1000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=22 ,tmpnum=1 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=10 ,tmpnum=1 ,tmpdepth=1000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=9 ,tmpnum=1 ,tmpdepth=1000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=16 ,tmpnum=1 ,tmpdepth= 0 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=27 ,tmpnum=1 ,tmpdepth=-1000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;



        vect.push_back( edge ) ;

    }

};
