
#include "../picprocess.h"

class pic13process:public picprocess{

public :
    pic13process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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

        tmplabel=16 ,tmpnum=4 ,tmpdepth=-3000 ,tmpinc = -500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=11 ,tmpnum=7 ,tmpdepth=-2500 ,tmpinc = -500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=1 ,tmpnum=7,tmpdepth=-3500 ,tmpinc = 500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=29 ,tmpnum=8,tmpdepth=-500 ,tmpinc = -500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=22 ,tmpnum=1,tmpdepth=-2500 ,tmpinc = -500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=24 ,tmpnum=1,tmpdepth=-2500 ,tmpinc = -500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=23 ,tmpnum=1,tmpdepth=-3000 ,tmpinc = -500 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=18 ,tmpnum=1 ,tmpdepth=-3500 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;


        vect.push_back( edge ) ;

    }

};
