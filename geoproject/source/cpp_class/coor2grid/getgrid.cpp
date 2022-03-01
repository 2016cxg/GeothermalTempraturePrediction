
/*
输入：一张深度图
输出：gridfile，保存每个网格点的坐标，以及网格点开始的坐标的数值


寻找划分坐标的点,就是坐标网格线的点
输出划分网格点到gridfile.txt
*/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv/cv.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std ;
using namespace cv;


//输入一张深度图片
int main(){
    ofstream myout("settings\\gridfile.txt") ;

    string imgpth = "settings\\aa4.png" ;
    string outimg = "outputs\\aa5.png" ;
    Mat img = imread(imgpth, IMREAD_COLOR) ;

    vector<vector<int> > posvleft, posvright ;//左边的网格线点，右边网格线点
    for( int i=1200; i<4500; i++ ){
        int j = 501 ;
        Vec3b & pxl = img.at<Vec3b>( i,j-2) ;

        if( pxl[0]+pxl[1]+pxl[2] == 0 ){
            posvleft.push_back( vector<int>{i,j} ) ;
            circle(img, Point(j,i),30, Scalar(0,0,255) );

            i+=10 ;

            int sz = posvleft.size() ;
            cout<<sz<<endl;
            if( posvleft.size()>1 ){
                cout<<posvleft[sz-1][0]-posvleft[sz-2][0]<<endl;
            }
        }

    }
    posvleft.insert( posvleft.begin(), vector<int>{posvleft[0][0]-602, posvleft[0][1]} ) ;
    circle(img, Point(posvleft[0][1],posvleft[0][0]),30, Scalar(0,0,255) );
    cout<<posvleft.size()<<endl;
    for( int i=1200; i<4900; i++ ){
        int j = 7871 ;
        Vec3b & pxl = img.at<Vec3b>( i,j+3) ;

        if( pxl[0]+pxl[1]+pxl[2] == 0 ){
            posvright.push_back( vector<int>{i,j} ) ;
            circle(img, Point(j,i),30, Scalar(0,0,255) );

            i+=10 ;
            int sz = posvright.size() ;
            if( posvright.size()>1 ){
                cout<<posvright[sz-1][0]-posvright[sz-2][0]<<endl;
            }
        }

    }
    cout<<posvright.size()<<endl;
    for( int i =0;i<7;i++){
        int j=i ;
        line(img, Point(posvleft[i][1],posvleft[i][0]), Point(posvright[j][1],posvright[j][0]), Scalar(100,100,100),2 ) ;
    }

    double basehrz = 36 ;
    double basevtc = 75 ;
    reverse(posvleft.begin(),posvleft.end()) ;
    reverse(posvright.begin(),posvright.end()) ;

    myout<<basehrz<<" "<<basevtc<<endl;
    myout<<posvleft.size()<<endl;
    for( int i=0;i<posvleft.size();i++){
        myout<<posvleft[i][0]<<" "<<posvleft[i][1]<<endl;
    }
    myout<<posvright.size()<<endl;
    for( int i=0;i<posvright.size();i++){
        myout<<posvright[i][0]<<" "<<posvright[i][1]<<endl;
    }



    vector<vector<int> > posvup, posvdown ;//上边网格线点，下边网格线点
    int i=1001 ;
    for( int j=700; j<7700; j++ ){
//        int j = 501 ;
        Vec3b & pxl = img.at<Vec3b>( i-2,j) ;

        if( pxl[0]+pxl[1]+pxl[2] == 0 ){
            posvup.push_back( vector<int>{i,j} ) ;
            circle(img, Point(j,i),30, Scalar(0,0,255) );
//            cout<<"sdf"<<endl;

            j+=10 ;

            int sz = posvup.size() ;
//            cout<<sz<<endl;
            if( posvup.size()>1 ){
                cout<<posvup[sz-1][1]-posvup[sz-2][1]<<endl;
            }
        }

    }
    posvup.erase( posvup.begin() ) ;
    cout<<posvup.size()<<endl;
    cout<<"asd"<<endl;
    i=4845 ;
    for( int j=700; j<7700; j++ ){
//        int j = 501 ;
        Vec3b & pxl = img.at<Vec3b>( i+2,j) ;

        if( pxl[0]+pxl[1]+pxl[2] == 0 ){
            posvdown.push_back( vector<int>{i,j} ) ;
            circle(img, Point(j,i),30, Scalar(0,0,255) );
//            cout<<"sdf"<<endl;

            j+=10 ;

            int sz = posvdown.size() ;
//            cout<<sz<<endl;
            if( posvdown.size()>1 ){
                cout<<posvdown[sz-1][1]-posvdown[sz-2][1]<<endl;
            }
        }

    }
    cout<<posvdown.size()<<endl;

    myout<<posvup.size()<<endl;
    for( int i=0;i<posvup.size();i++){
        myout<<posvup[i][0]<<" "<<posvup[i][1]<<endl;
    }
    myout<<posvdown.size()<<endl;
    for( int i=0;i<posvdown.size();i++){
        myout<<posvdown[i][0]<<" "<<posvdown[i][1]<<endl;
    }


    return 0 ;
}

