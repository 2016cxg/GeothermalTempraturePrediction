/*
二值化图片，提取出等高线，其它的地方变成白色，只有等高线变成黑色

*/

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace std ;
using namespace cv;

class BinaryContourLine{
private:

    void convertPixel(Vec3b & pxl1, int val ){
        pxl1.val[0] = val ;
        pxl1.val[1] = val ;
        pxl1.val[2] = val ;
    }


public:

    void processBinary(string deepthpic, int rk ){
        string srk = to_string(rk) ;

        string imgpth = deepthpic+ "\\1pic\\"+srk+".png";
        cout<<imgpth<<endl;
    //    string imgpth = "C:\\Users\\cheng\\Desktop\\0.jpg" ;
        string outpth = deepthpic+ "\\2outputpic\\"+srk+".png" ;

        cout<<outpth<<endl;

        Mat img = imread(imgpth, IMREAD_COLOR) ;
        Mat tmpimg = imread(imgpth, IMREAD_COLOR) ;

        int px[] = { -1,-1,-1,0,0,1,1,1 } ;
        int py[] = { -1,0,1,-1,1,-1,0,1 } ;

        for( int i=1265; i<4369; i++ ){
            for( int j=1128; j<7872; j++ ){
                Vec3b & pxl = img.at<Vec3b>( i,j) ;
                if( pxl[0]<90 && pxl[1]<40 && pxl[2]<10){
                    Vec3b & pxl1 = tmpimg.at<Vec3b>( i,j) ;
                    pxl1.val[0] = 0 ;
                    pxl1.val[1] = 0 ;
                    pxl1.val[2] = 0 ;

                    for( int idx =0; idx<8; idx++){
                        int tmpx = i+px[idx] ;
                        int tmpy = j+py[idx] ;

                        Vec3b & tmppxl = tmpimg.at<Vec3b>( tmpx,tmpy) ;

                        tmppxl.val[0] = 0 ;
                        tmppxl.val[1] = 0 ;
                        tmppxl.val[2] = 0 ;
                    }
                }
                else{
                    Vec3b & tmppxl = tmpimg.at<Vec3b>( i,j) ;
                    if( tmppxl[0] == 0 && tmppxl[1] == 0 && tmppxl[2] == 0 ){

                    }
                    else{
                        tmppxl.val[0] = 255 ;
                        tmppxl.val[1] = 255 ;
                        tmppxl.val[2] = 255 ;
                    }
                }
            }
        }


        std::vector<int> compression_params;
        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//选择PNG格式
        compression_params.push_back(0);

        imwrite(outpth, tmpimg, compression_params) ;

        return ;

    }

};
