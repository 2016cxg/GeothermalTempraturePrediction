



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
因为3cleanedpic中的图片的黑色他们的数值存在不是0和255的情况，需要把他们都变成0或者255两个数值
3cleanedpic 2 4binarypic
*/

using namespace std ;
using namespace cv;



void setPixel(Vec3b & pxl1, int val1, int val2, int val3 ){
    pxl1.val[0] = val1 ;
    pxl1.val[1] = val2 ;
    pxl1.val[2] = val3 ;

}

int main(){
    Data data ;

    string imgpth="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\3cleanedpic\\"+to_string(data.num)+".png" ;
    string outimg="D:\\workplace\\geoproject\\pictureproject\\data\\deepth\\4binarypic\\"+to_string(data.num)+".png" ;

    Mat img = imread(imgpth, IMREAD_COLOR) ;
//    string outimg = outpth_ ;

//        vector<vector<int> > edge ;
//        int edgei,edgej ;

    cout<<"aaaaa"<<endl;
    for( int i=1266; i<4469; i++ ){
        for( int j=1129; j<7820; j++ ){
            Vec3b & pxl = img.at<Vec3b>( i,j) ;

            if( pxl[0] < 150 &&  pxl[1] < 150 && pxl[2] < 150 ){
                setPixel( pxl, 0, 0, 0) ;
            }
            else{
                setPixel( pxl, 255, 255, 255) ;
            }
        }
    }



    std::vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//选择PNG格式
    compression_params.push_back(0);
////
    imwrite(outimg, img, compression_params) ;

    return 0 ;
}


