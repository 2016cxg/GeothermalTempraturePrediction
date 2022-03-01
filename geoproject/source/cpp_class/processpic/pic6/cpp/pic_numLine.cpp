



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
#include "Data.h"
/*
这一步是对图片中等值线的数值进行标记
4binarypic 2 5cleanedoutputpic
*/

using namespace std ;
using namespace cv;


class ContourVal{
private:
    void setPixel(Vec3b & pxl1, int val1, int val2, int val3 ){
        pxl1.val[0] = val1 ;
        pxl1.val[1] = val2 ;
        pxl1.val[2] = val3 ;

    }

    int px[10] = { -1,-1,-1,0,0,1,1,1 } ;
    int py[10] = { -1,0,1,-1,1,-1,0,1 } ;


    vector<vector<vector<int> > > vect ;
    vector<vector<int> > vectgrn ;

    void dfs(Mat& img, int a, int b , vector<vector<int> > & tmpvect ){
        Vec3b & pxl = img.at<Vec3b>( a,b) ;
        setPixel( pxl, 255, 255, 255) ;
        tmpvect.push_back( vector<int>{a,b} ) ;
    //    cout<<"123"<<endl;

        for( int i=0;i<8;i++){
            int tmpx = a+px[i] ;
            int tmpy = b+py[i] ;

            Vec3b & pxl2 = img.at<Vec3b>( tmpx,tmpy) ;
            if( pxl2[0] ==0 && pxl2[1] ==0 && pxl2[2] ==0){

                dfs( img, tmpx, tmpy, tmpvect ) ;
            }
        }
    }

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

    const static int maxn = 1000 ;
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

    vector<int> findNearAll(vector<int>& p0, int& validx, int& valdpth){
        vector<int> tmpvect ;
        double dis = DBL_MAX ;
        for( int i=0;i<vect.size(); i++){
            for( int j=0;j<vect[i].size(); j++){
                double tmpdis = caldis2(p0, vect[i][j] ) ;
                if( tmpdis< dis ){
                    dis = tmpdis ;
                    validx = i ;
                    valdpth = idxdpth[i] ;
                    tmpvect = vect[i][j] ;
                }
            }
        }
        return tmpvect ;
    }

    vector<int> findNearVal(vector<int>& p0, int valdpth ){
        vector<int> tmpvect ;
        double dis = DBL_MAX ;
        for( int i=0;i<vect.size();i++){
            if( idxdpth[i] != valdpth )
                continue ;

            for( int j=0;j<vect[i].size(); j++){
                double tmpdis = caldis2(p0, vect[i][j] ) ;
                if( tmpdis< dis ){
                    dis = tmpdis ;
                    tmpvect = vect[i][j] ;
                }
            }
        }
        return tmpvect ;
    }


    bool judcircle(vector<int> & p0, vector<int>& p1, int & validx){
        for( int i=0;i<vect[validx].size();i++){
            vector<int> px = vect[validx][i] ;
            vector<int> p0px = vector<int>{px[0]-p0[0], px[1]-p0[1] } ;
            vector<int> p0p1 = vector<int>{p1[0]-p0[0], p1[1]-p0[1] } ;
            double x1=p0px[0], y1 = p0px[1] ;
            double x2=p0p1[0], y2 = p0p1[1] ;
            double cosx = (x1*x2+y1*y2)/(sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2)) ;

    //        cout<<cosx<<" "<<p0[0]<<" "<<p0[1]<<" "<<px[0]<<" "<<px[1]<<" "<<p1[0]<<" "<<p1[1]<<" "<<x1*x1+y1*y1<<" "<<x2*x2+y2*y2<<endl;
            if( (abs(cosx-1) <0.0009) && ( (x1*x1+y1*y1)<(x2*x2+y2*y2) )){
    //            cout<<cosx<<" "<<<<endl;
                return true ;
            }
        }
    //    cout<<mincos<<" "<<maxcos<<" "<<abs(maxcos-1)<<endl;
        return false ;
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


    int calpoint(Mat& img, vector<int> p0){
        vector<vector<int> > vect2elm ;
    //    vector<int> p0 = vector<int>{2800, 1233} ;
        int valdpth, validx, inc=1000 ;
        vector<int> p = findNearAll(p0, validx, valdpth); //查找和p0最近的点
    //    cout<<validx<<" === "<<vect.size()-1<<idxdpth[validx]<<endl;
        if( validx == vect.size()-1 ){
    //        cout<<INT_MIN<<endl;
            return  INT_MIN;
        }

        vector<int> p1 = findNearVal(p0, valdpth+inc ); //查找给定数里面的最近点
        vector<int> p2 = findNearVal(p0, valdpth-inc ) ;

        if( p1.size()>0){
    //        circle(img, Point(p1[1],p1[0]),30, Scalar(255,0,255) );
            if( !judcircle(p0, p1, validx) ){
                vector<int> tmpvect(p1) ;
                tmpvect.push_back(valdpth+inc) ;
                vect2elm.push_back( tmpvect ) ;
            }
    //        for( int i=0;i<vect[validx].size();i++){
    //            int tmpx = vect[validx][i][0] ;
    //            int tmpy = vect[validx][i][1] ;
    //            Vec3b & pxl2 = img.at<Vec3b>( tmpx,tmpy) ;
    //            setPixel( pxl2, 0,0,255) ;
    //        }
        }

    //    cout<<"=================="<<endl;
        if( p2.size()>0){
    //        circle(img, Point(p2[1],p2[0]),30, Scalar(0,0,255) );
            if( !judcircle(p0, p2, validx) ){
                vector<int> tmpvect(p2) ;
                tmpvect.push_back(valdpth-inc) ;
                vect2elm.push_back( tmpvect ) ;
            }
        }
    //    circle(img, Point(p0[1],p0[0]),30, Scalar(0,0,255) );
    //    circle(img, Point(p[1],p[0]),30, Scalar(0,0,255) );

    //    cout<<"num:"<<vect2elm.size()<<endl;


        if( vect2elm.size() == 0 ){
    //        cout<<valdpth<<endl;
            return valdpth ;
        }
        else{
            vector<int> tmpvect = vector<int>{ vect2elm[0][0], vect2elm[0][1] } ;
            int tmpval = vect2elm[0][2] ;
            double disx = caldis2(p0, tmpvect) ;
            double disy = caldis2(p0, p) ;
            double valx = tmpval ;
            double valy = valdpth ;

            int fdpth = (valx-valy)*(disy/(disx+disy)) + valy ;
    //        cout<<fdpth<<endl;
            return fdpth ;
        }

    }

    Mat img ;
    string outimg ;

public :
    ContourVal(string imgpth, string outpth_ ){
        for( int i=0;i<maxn;i++){
            boolidxdpth[i] = false ;
            idxdpth[i] = 0 ;
        }
//        string imgpth = "C:\\Users\\cheng\\Desktop\\aa2a.png" ;
//        string outimg = "C:\\Users\\cheng\\Desktop\\aa4a.png" ;
        img = imread(imgpth, IMREAD_COLOR) ;
        outimg = outpth_ ;

        vector<vector<int> > edge ;
        int edgei,edgej ;

        cout<<"aaaaa"<<endl;
        for( int i=1266; i<4369; i++ ){
            for( int j=1129; j<7820; j++ ){
                Vec3b & pxl = img.at<Vec3b>( i,j) ;

                vector<vector<int> > tmpvect ;
//                cout<<i<<" "<<j<<endl;

                if( (pxl[0]==255) && (pxl[1]+pxl[2]==0) ){
//                    cout<<i<<" "<<j<<endl;
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

        cout<<"--------"<<endl;
        cout<<vect.size()<<endl;

        int tmplabel,tmpnum,tmpdepth,tmpinc ;

        tmplabel=27 ,tmpnum=16 ,tmpdepth=-15000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=11 ,tmpnum=8 ,tmpdepth=-10000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=12 ,tmpnum=3 ,tmpdepth=-8000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=9 ,tmpnum=3 ,tmpdepth=-1000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=14 ,tmpnum=1 ,tmpdepth=-4000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=32 ,tmpnum=2 ,tmpdepth=-2000 ,tmpinc = -1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=34 ,tmpnum=1 ,tmpdepth=-3000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=35 ,tmpnum=1 ,tmpdepth=-10000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;
        tmplabel=33 ,tmpnum=1 ,tmpdepth=-10000 ,tmpinc = 1000 ;
        dfs_idxdpth(tmplabel,tmpnum,vect,tmpdepth,tmpinc, vect[tmplabel][0] ) ;


        cout<<"====="<<endl;

        //对于区域内的所有黑点，dfs它，记录所有访问过的黑点，并且将他们命成白点
        //按照点的数量排序，显示数量少的k个群
    //

        int cnt = 0 ;
        for( int i=0;i<vect.size() ;i++){
            if( vect[i].size()<100){
//                for( int j=0;j<vect[i].size(); j++){
//                    Vec3b & pxl = img.at<Vec3b>( vect[i][j][0],vect[i][j][1]) ;
//                    setPixel(pxl, 0,0,255) ;
//                }
            }
            else if(!boolidxdpth[i]){
                for( int j=0;j<vect[i].size(); j++){
                    Vec3b & pxl = img.at<Vec3b>( vect[i][j][0],vect[i][j][1]) ;
                    setPixel(pxl, 255,0,0) ;
                }
                cnt ++ ;

                mydraw(img,  vect[i][0][0],vect[i][0][1]) ;
                circle(img, Point(vect[i][0][1],vect[i][0][0]),30, Scalar(0,0,255) );
                putText(img,  to_string(i),Point(vect[i][0][1],vect[i][0][0]), CV_FONT_HERSHEY_PLAIN, 1, CV_RGB(0,0,255),1 );
            }
            else{
                 for( int j=0;j<vect[i].size(); j++){
                    Vec3b & pxl = img.at<Vec3b>( vect[i][j][0],vect[i][j][1]) ;
                    setPixel(pxl, 0,255,0) ;
                }

                mydraw(img,  vect[i][0][0],vect[i][0][1]) ;
                circle(img, Point(vect[i][0][1],vect[i][0][0]),30, Scalar(0,0,255) );
                putText(img,  to_string(idxdpth[i]),Point(vect[i][0][1],vect[i][0][0]), CV_FONT_HERSHEY_PLAIN, 1, CV_RGB(0,0,255),1 );
            }
        }
        cout<<"num:"<<cnt<<endl;
    }

    void outpic(){
        std::vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//选择PNG格式
        compression_params.push_back(0);
    ////
        imwrite(outimg, img, compression_params) ;
    }

};

int main(){
    Data data ;

    string outpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\7numLine\\"+to_string(data.num)+".png" ;
    string imgpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\5cleanedOutputpic\\"+to_string(data.num)+".png" ;
    ContourVal conval(imgpth, outpth) ;


    cout<<"asdf"<<endl;
    conval.outpic() ;
    return 0 ;

}


