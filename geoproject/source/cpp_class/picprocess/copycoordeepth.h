

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
    CoorDeepth(string imgpth, string outpth_ ){
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

        sort( vect.begin(), vect.end(), cmp ) ;
    //    for( int i=0;i<vect.size() ;i++){
    //        cout<<vect[i].size()<<endl;
    //    }


        dfs_idxdpth(25,16,vect,-17000,1000, vect[25][0] ) ;
        dfs_idxdpth(21,9,vect,-5000,-1000, vect[21][0] ) ;
        dfs_idxdpth(55,5,vect,-11000,1000, vect[55][0] ) ;
        dfs_idxdpth(53,11,vect,-14000,1000, vect[53][0] ) ;
        dfs_idxdpth(43,1,vect,-5000,1000, vect[43][0] ) ;
        dfs_idxdpth(85,2,vect,-8000,-1000, vect[85][0] ) ;
        dfs_idxdpth(20,1,vect,-9000,-1000, vect[20][0] ) ;
        dfs_idxdpth(0,7,vect,-8000,-1000, vect[0][0] ) ;
        dfs_idxdpth(9,3,vect,-5000,-1000, vect[9][0] ) ;
        dfs_idxdpth(44,4,vect,-13000,1000, vect[44][0] ) ;
        dfs_idxdpth(15,3,vect,-6000,-1000, vect[15][0] ) ;
        dfs_idxdpth(61,3,vect,-14000,1000, vect[61][0] ) ;
        dfs_idxdpth(10,3,vect,-5000,-1000, vect[10][0] ) ;
        dfs_idxdpth(40,2,vect,-14000,1000, vect[40][0] ) ;
        dfs_idxdpth(23,1,vect,-3000,1000, vect[23][0] ) ;
        dfs_idxdpth(19,4,vect,-2000,-1000, vect[19][0] ) ;
        dfs_idxdpth(11,4,vect,-1000,-1000, vect[11][0] ) ;
        dfs_idxdpth(8,3,vect,-3000,-1000, vect[8][0] ) ;
        dfs_idxdpth(80,1,vect,-9000,-1000, vect[80][0] ) ;
        dfs_idxdpth(76,1,vect,-9000,-1000, vect[76][0] ) ;
        dfs_idxdpth(88,1,vect,-11000,-1000, vect[88][0] ) ;
        dfs_idxdpth(18,1,vect,-9000,-1000, vect[18][0] ) ;
        dfs_idxdpth(12,1,vect,-7000,-1000, vect[12][0] ) ;
        dfs_idxdpth(51,1,vect,-5000,-1000, vect[51][0] ) ;
        dfs_idxdpth(34,1,vect,-7000,-1000, vect[34][0] ) ;
        dfs_idxdpth(16,1,vect,-10000,-1000, vect[16][0] ) ;
        dfs_idxdpth(3,1,vect,-6000,-1000, vect[3][0] ) ;
        dfs_idxdpth(14,1,vect,-6000,-1000, vect[14][0] ) ;
        dfs_idxdpth(5,1,vect,-13000,-1000, vect[5][0] ) ;
        dfs_idxdpth(1,1,vect,-13000,-1000, vect[1][0] ) ;
        dfs_idxdpth(4,1,vect,-4000,-1000, vect[4][0] ) ;

    //    dfs_idxdpth(8,4,vect,-3000,-1000, vect[8][0] ) ;
    //    dfs_idxdpth(71,4,vect,-5000,1000, vect[71][0] ) ;
    //    cout<<"====="<<endl;

        //对于区域内的所有黑点，dfs它，记录所有访问过的黑点，并且将他们命成白点
        //按照点的数量排序，显示数量少的k个群
    //
        for( int i=0;i<vect.size() ;i++){
            if( vect[i].size()<100){
    //            for( int j=0;j<vect[i].size(); j++){
    //                Vec3b & pxl = img.at<Vec3b>( vect[i][j][0],vect[i][j][1]) ;
    //                setPixel(pxl, 0,0,255) ;
    //            }
            }
            else if(!boolidxdpth[i]){
                for( int j=0;j<vect[i].size(); j++){
                    Vec3b & pxl = img.at<Vec3b>( vect[i][j][0],vect[i][j][1]) ;
                    setPixel(pxl, 255,0,0) ;
                }

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
        for( int i=0;i<edge.size();i++){
            Vec3b & pxl = img.at<Vec3b>( edge[i][0],edge[i][1]) ;
            setPixel(pxl, 0,255,0) ;
        }


        vect.push_back( edge ) ;
        cout<<vect.size()<<endl;
        for( int i=0;i<10;i++){
            cout<<i<<" "<<idxdpth[i]<<endl;
        }
    }

    int calPos(vector<int> v){
        int tmpi = v[0]; //3817
        int tmpj = v[1] ; //3075
        int dpth = calpoint(img, vector<int>{tmpi, tmpj} ) ;
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


        // 开一个bool数组，给一个点p0，计算最近的点p，令这个点的数值是x，
        // 对bool数组里面下标对应的数值是x的进行标记不能访问
        // 在x+1000里面找一个最近的点p1
        // 在x-1000里面找一个最近的点p2
        // 判断p0,px是不是比p0,p1同向并且更短，如果不是，加入备用数组
        // 同样判断p2，如果不是，加入备用数组
        // 判断备用数组大小，如果是1，就用这个点和p来计算深度
        // 如果数组大小未0，那么就把p0点数值变成p的数值

    //
//        std::vector<int> compression_params;
//        compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);//选择PNG格式
//        compression_params.push_back(0);
//    ////
//        imwrite(outimg, img, compression_params) ;

//
//        return 0 ;
    }
    // 给定一个标记线x，需要标记的条数y
    // 开一个映射记录下标和标记，对x标记深度
    // dfs 标记条数y，输入线段集合grp、对应x的深度
    //    记录x和深度，在grp中删除x下标（bol数组标记不能访问）
    //    获取下标x的第一个元素k，在grp剩下能访问的下标里面找最短的距离k最近的点k1，记录k1对应的标记x1
    //    dfs(x1,y+inc)
    // 显示标记了的线段集合


    //

};


