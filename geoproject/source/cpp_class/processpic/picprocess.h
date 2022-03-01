#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/cv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <stdlib.h>
#include <time.h>       /* time */
#include <fstream>

using namespace std ;
using namespace cv;

#ifndef PICPROCESS_
#define PICPROCESS_

class picprocess{
protected:
    void setPixel(Vec3b & pxl1, int val1, int val2, int val3 ){
        pxl1.val[0] = val1 ;
        pxl1.val[1] = val2 ;
        pxl1.val[2] = val3 ;

    }

    int px[10] = { -1,-1,-1,0,0,1,1,1 } ;
    int py[10] = { -1,0,1,-1,1,-1,0,1 } ;


    vector<vector<vector<int> > > vect ;
    vector<vector<int> > vectgrn ;

    void bfs(Mat& img, int a, int b , vector<vector<int> > & tmpvect ){
        queue< vector<int> > que ;
        que.push( vector<int>{a,b} ) ;
        Vec3b & pxl = img.at<Vec3b>( a, b )  ;
        setPixel( pxl, 255, 255, 255) ;
        tmpvect.push_back( vector<int>{a,b} ) ;

        while( que.size()>0 ){
            vector<int> tp = que.front() ;
            que.pop() ;
    //        cout<<que.size()<<endl;

            for( int i=0;i<8;i++){
                int tmpx = tp[0]+px[i] ;
                int tmpy = tp[1]+py[i] ;

                Vec3b & pxl2 = img.at<Vec3b>( tmpx,tmpy) ;
                if( pxl2[0] ==255 && pxl2[1] ==0 && pxl2[2] ==0 ){
                    setPixel( pxl2, 255,255,255) ;
                    tmpvect.push_back( vector<int>{tmpx,tmpy} ) ;

                    que.push( vector<int>{tmpx, tmpy} ) ;
                }
            }
        }
    }

    static bool cmp(vector<vector<int> > v1, const vector<vector<int> > v2){
        return v1.size()<=v2.size() ;
    }

    //dfs到dfs2做的工作是连接不连续的线段，并且去除非线段的蓝色区块，人工完成
    //bfs 出所有的蓝色区块和绿色区块
    //丢弃点很少的区块
    //画图

    void mydraw(Mat& img, int a, int b ){
        Vec3b & pxl = img.at<Vec3b>( a,b) ;
        setPixel( pxl, 0,0,255) ;
        for(int i=0;i<8;i++){
            int tmpx = a+px[i] ;
            int tmpy = b+py[i] ;

            Vec3b & pxl2 = img.at<Vec3b>( tmpx, tmpy) ;
            setPixel( pxl2, 0,0,255 ) ;
        }
    }

    const static int maxn = 100+10 ;
    int idxdpth[maxn] ;
    bool boolidxdpth[maxn] ;

    int caldis(vector<int> &v1, vector<int>& v2){
        return sqrt( (v1[0]-v2[0])*(v1[0]-v2[0]) + (v1[1]-v2[1])*(v1[1]-v2[1]) ) ;
    }
    double caldis2(vector<int> &v1, vector<int>& v2){
        return sqrt( (v1[0]-v2[0])*(v1[0]-v2[0]) + (v1[1]-v2[1])*(v1[1]-v2[1]) ) ;
    }
    void dfs_idxdpth(int x, int y, vector<vector<vector<int> > >& vect, int dpth, int inc, vector<int> tmpvect){
        if(y<=0)
            return ;
        idxdpth[x] = dpth ;
        boolidxdpth[x] = true ;

        vector<int> nxtvect ;
        int x1=0, dis=INT_MAX ;
        for(int i=0;i<vect.size();i++){
            if( boolidxdpth[i] )
                continue ;
            if( vect[i].size()<100 )
                continue ;

            for(int j=0;j<vect[i].size();j++){
                int tmpdis=caldis(tmpvect, vect[i][j]) ;
                if( tmpdis<dis){
                    dis = tmpdis ;
                    x1 = i ;
                    nxtvect = vect[i][j] ;
                }
            }
        }

        dfs_idxdpth(x1, y-1, vect, dpth+inc, inc, nxtvect) ;
    }


    void bfsEdge(Mat& img, int a, int b , vector<vector<int> > & tmpvect ){
        queue< vector<int> > que ;
        que.push( vector<int>{a,b} ) ;
        Vec3b & pxl = img.at<Vec3b>( a, b )  ;
        setPixel( pxl, 255, 255, 255) ;
        tmpvect.push_back( vector<int>{a,b} ) ;

        while( que.size()>0 ){
            vector<int> tp = que.front() ;
            que.pop() ;
    //        cout<<que.size()<<endl;

            for( int i=0;i<8;i++){
                int tmpx = tp[0]+px[i] ;
                int tmpy = tp[1]+py[i] ;

                Vec3b & pxl2 = img.at<Vec3b>( tmpx,tmpy) ;
                if( pxl2[1] ==255 && pxl2[0] ==0 && pxl2[2] ==0 ){
                    setPixel( pxl2, 255,255,255) ;
                    tmpvect.push_back( vector<int>{tmpx,tmpy} ) ;

                    que.push( vector<int>{tmpx, tmpy} ) ;
                }
            }
        }
    }

    Mat img ;
    string outimg ;

public:
    picprocess(){
    }

    picprocess(string imgpth, string outpth_){
        for( int i=0;i<maxn;i++){
            boolidxdpth[i] = false ;
            idxdpth[i] = 0 ;
        }

        img = imread(imgpth, IMREAD_COLOR) ;
        outimg = outpth_ ;
    }

    virtual void construct(string , string )=0 ;

    void retVal(vector<vector<vector<int> > >& vect_, int* idxdpth_, bool* bidxdpth_){
        vect_ = vect ;

        for(int i=0;i<maxn;i++){
            idxdpth_[i] = idxdpth[i] ;
            bidxdpth_[i] = boolidxdpth[i] ;
        }
    }
};


#endif // PICPROCESS_
