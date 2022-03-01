
#include "../picprocess.h"

class pic4process:public picprocess{

public :
    pic4process(string imgpth, string outpth_):picprocess(imgpth, outpth_){
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

        tmplabel=45 ;
        tmpnum=17 ;
        tmpdepth=-16000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=22 ;
        tmpnum=8 ;
        tmpdepth=-13000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=20 ;
        tmpnum=7 ;
        tmpdepth=-13000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=7 ;
        tmpnum=6 ;
        tmpdepth=0 ;
        tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=76 ;
        tmpnum=6 ;
        tmpdepth=-3000 ;
        tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=83 ;
        tmpnum=4 ;
        tmpdepth=-13000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=85 ;
        tmpnum=3 ;
        tmpdepth=-5000 ;
        tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=73 ;
        tmpnum=4 ;
        tmpdepth=-2000 ;
        tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=71 ;
        tmpnum=4 ;
        tmpdepth=-10000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=55 ;
        tmpnum=2 ;
        tmpdepth=-4000 ;
        tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=29 ;
        tmpnum=2 ;
        tmpdepth=-13000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=29 ;
        tmpnum=2 ;
        tmpdepth=-13000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=66 ;
        tmpnum=1 ;
        tmpdepth=-11000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=78 ;
        tmpnum=1 ;
        tmpdepth=-4000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=77 ;
        tmpnum=1 ;
        tmpdepth=-10000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=52 ;
        tmpnum=1 ;
        tmpdepth=-2000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=57 ;
        tmpnum=1 ;
        tmpdepth=-2000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=50 ;
        tmpnum=1 ;
        tmpdepth=-4000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=49 ;
        tmpnum=1 ;
        tmpdepth=-3000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=53 ;
        tmpnum=1 ;
        tmpdepth=-7000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=60 ;
        tmpnum=1 ;
        tmpdepth=-6000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] );

        tmplabel=61 ;
        tmpnum=1 ;
        tmpdepth=-5000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=67 ;
        tmpnum=1 ;
        tmpdepth=-7000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=62 ;
        tmpnum=1 ;
        tmpdepth=-3000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=63 ;
        tmpnum=1 ;
        tmpdepth=-5000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=54 ;
        tmpnum=1 ;
        tmpdepth=-4000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=47 ;
        tmpnum=1 ;
        tmpdepth=-4000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=46 ;
        tmpnum=2 ;
        tmpdepth=-4000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=39 ;
        tmpnum=1 ;
        tmpdepth=-13000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=27 ;
        tmpnum=1 ;
        tmpdepth=-12000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=31 ;
        tmpnum=1 ;
        tmpdepth=-12000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=32 ;
        tmpnum=1 ;
        tmpdepth=-12000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=16 ;
        tmpnum=1 ;
        tmpdepth=-1000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        tmplabel=0 ;
        tmpnum=1 ;
        tmpdepth=-4000 ;
        tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;

        vect.push_back( edge ) ;

    }

};
