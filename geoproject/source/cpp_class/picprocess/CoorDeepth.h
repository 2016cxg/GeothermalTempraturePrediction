

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
#include "../processpic/picprocess.h"

using namespace std ;
using namespace cv;


//策略模式类模板实现，CoorDeepth类是策略模式的project类
class CoorDeepth{
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


    int calpoint(Mat& img, vector<int> p0, int inc=1000){
        vector<vector<int> > vect2elm ;
    //    vector<int> p0 = vector<int>{2800, 1233} ;
        int valdpth, validx ;
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

    CoorDeepth(string imgpth, string outpth_, picprocess &processpic ){
        img = imread(imgpth, IMREAD_COLOR) ;
        outimg = outpth_ ;

        processpic.retVal(vect, idxdpth, boolidxdpth) ;
//        cout<<vect.size()<<endl;
//        for( int i=0;i<10;i++){
//            cout<<i<<" "<<idxdpth[i]<<endl;
//        }
//
    }

    int calPos(vector<int> v, int inc=1000){
        int tmpi = v[0]; //3817
        int tmpj = v[1] ; //3075
        int dpth = calpoint(img, vector<int>{tmpi, tmpj}, inc) ;
        circle(img, Point(tmpj,tmpi ),30, Scalar(255,0,0) );
        putText(img,  to_string(dpth),Point(tmpj,tmpi ), CV_FONT_HERSHEY_PLAIN, 1, CV_RGB(255,0,0),1 );

        return dpth ;
    }

    void outpic(){
        std::vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//选择PNG格式
        compression_params.push_back(0);
    ////
        imwrite(outimg, img, compression_params) ;
    }

    void testRandomPos(){

    //    freopen("C:\\Users\\cheng\\Desktop\\out.txt","wb",stdout) ;

        srand (time(NULL));


    //    int tmpi = 3817;
    //    int tmpj = 3075 ;
    //    int dpth = calpoint(img, vector<int>{tmpi, tmpj} ) ;
    //    circle(img, Point(tmpj,tmpi ),30, Scalar(255,0,0) );
    //    putText(img,  to_string(dpth),Point(tmpj,tmpi ), CV_FONT_HERSHEY_PLAIN, 1, CV_RGB(255,0,0),1 );


        int il=1266, ir = 4369 ;
        int jl=1129, jr = 7820 ;

        for( int i=0;i<100;i++){
            int tmpi=rand()%(ir-il)+il ;
            int tmpj=rand()%(jr-jl)+jl ;

            int dpth = calpoint(img, vector<int>{tmpi, tmpj} ) ;
            cout<<tmpi<<" "<<tmpj<<" "<<dpth<<endl;
            circle(img, Point(tmpj,tmpi ),30, Scalar(255,0,0) );
            putText(img,  to_string(dpth),Point(tmpj,tmpi ), CV_FONT_HERSHEY_PLAIN, 1, CV_RGB(255,0,0),1 );
        }

    }

};


