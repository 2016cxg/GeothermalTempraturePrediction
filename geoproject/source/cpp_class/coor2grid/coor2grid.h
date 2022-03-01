/*
输入：地理坐标，
返回：在图片上的坐标
*/

#include<iostream>
#include<vector>
#include<fstream>

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



#ifndef COOR2GRID_H
#define COOR2GRID_H

class Coor2grid{
private:
    vector<int> calpos(vector<vector<int> > &tmpvect, float base, float x ){
        int pos = int(x-base) ;
        float dcm = x-base-pos ;

        int a = (tmpvect[pos+1][0]-tmpvect[pos][0])*dcm + tmpvect[pos][0] ;
        int b = (tmpvect[pos+1][1]-tmpvect[pos][1])*dcm + tmpvect[pos][1] ;
//        cout<<a<<" "<<b<<endl;
        return vector<int>{a,b} ;
    }

    vector<vector<vector<int> > > vect ;
    string settings, outputs ;
    float basehrz, basevtc ;

public:

    Coor2grid(string settings_, string outputs_){
        settings = settings_ ;
        outputs = outputs_ ;
//        string gridfile("settings\\gridfile.txt") ;

        ifstream myin(settings+"\\"+"gridfile.txt") ;
//        cout<<"asdfasdfadsf"<<endl;

        myin>>basehrz>>basevtc ;
//        cout<<basehrz<<" "<<basevtc<<endl;

        for( int i=0;i<4;i++){
            vector<vector<int> > tmpvect ;
            int num ;
            myin>>num ;
            int tmpa,tmpb ;
            while(num--){
                myin>>tmpa>>tmpb ;
                tmpvect.push_back( vector<int>{tmpa,tmpb} ) ;
            }

            vect.push_back( tmpvect ) ;
//            cout<<vect[i].size()<<endl;
        }
//        cout<<"===="<<endl;
    }

    vector<int> trasCoor2GridOutPic(vector<double> xy){
        double x = xy[0], y =xy[1] ;
        //vect0到3 是左右上下刻度
        vector<int> vleft = calpos(vect[0], basehrz, x) ;
        vector<int> vright= calpos(vect[1], basehrz, x) ;

        vector<int> vup = calpos(vect[2], basevtc, y) ;
        vector<int> vdown= calpos(vect[3], basevtc, y) ;
    //    cout<<vleft[0]<<" "<<vleft[1]<<endl;

        string imgpth = settings + "\\aa4.png" ;
        string outimg = outputs + "\\aa5.png" ;
        Mat img = imread(imgpth, IMREAD_COLOR) ;

        line(img, Point(vleft[1],vleft[0]), Point(vright[1],vright[0]), Scalar(100,100,100),2 ) ;
        line(img, Point(vup[1],vup[0]), Point(vdown[1],vdown[0]), Scalar(100,100,100),2 ) ;

        double A = (vleft[1]-vright[1])*1.0/(vleft[0]-vright[0]) ;
        double B = (vleft[1]-A*vleft[0]) ;

        double a = (vup[1]-vdown[1])*1.0/(vup[0]-vdown[0]) ;
        double b = (vup[1]-a*vup[0]) ;
        int fx = (b-B)*1.0/(A-a) ;
        int fy = (B*a-A*b)*1.0/(a-A) ;
//        cout<<A<<" "<<B<<" "<<a<<" "<<b<<endl;
//
//        cout<<fx<<" "<<fy<<endl;

        circle(img, Point(fy,fx),30, Scalar(0,0,255) );
    //    circle(img, Point(fx,fy),30, Scalar(0,0,255) );


        vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//选择PNG格式
        compression_params.push_back(0);
    ////
        imwrite(outimg, img, compression_params) ;

        return vector<int>{fx, fy} ;
    }

    vector<int> trasCoor2Grid(vector<double> xy){
        double x = xy[0], y =xy[1] ;
        //vect0到3 是左右上下刻度
        vector<int> vleft = calpos(vect[0], basehrz, x) ;
        vector<int> vright= calpos(vect[1], basehrz, x) ;

        vector<int> vup = calpos(vect[2], basevtc, y) ;
        vector<int> vdown= calpos(vect[3], basevtc, y) ;

        double A = (vleft[1]-vright[1])*1.0/(vleft[0]-vright[0]) ;
        double B = (vleft[1]-A*vleft[0]) ;

        double a = (vup[1]-vdown[1])*1.0/(vup[0]-vdown[0]) ;
        double b = (vup[1]-a*vup[0]) ;
        int fx = (b-B)*1.0/(A-a) ;
        int fy = (B*a-A*b)*1.0/(a-A) ;

        return vector<int>{fx, fy} ;
    }

};

#endif // MYCLASS_H
