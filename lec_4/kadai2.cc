#include<vector>
#include "image.hpp"
using namespace std;

typedef unsigned char uchar;

int main(void){
    Image sample("sample.png");
    Image binary_image(sample.w,sample.h, 3);
    vector<int> hist(256,0);
    double total_sum=0;

    for(int y=0; y<sample.h; y++){
        for(int x=0 ; x<sample.w; x++){
            int sum=0;
            for( int c=0; c<sample.ch; c++){
                uchar v=sample.GetPixel(y, x, c);
                sum=sum+v;  
            }
            uchar gray = sum / sample.ch;
            total_sum+=gray;
            hist[gray]++;
        }
    }

    double mt=total_sum/sample.w/sample.h;
    double m1,m2;
    double dist;
    double dist_max=0;
    double t_best=0;

    for(int t=0; t<255; t++){
        double white_sum=0;
        double black_sum=0;
        double white_num=0;
        double black_num=0;
        for(int i=0; i<=t; i++){
            white_sum+=hist[i]*i;
            white_num+=hist[i];
        }
        for(int i=t+1; i<256; i++){
            black_sum+=hist[i]*i;
            black_num+=hist[i];
        }
        if(white_num==0 || black_num==0){
            continue;
        }
        m1=white_sum/white_num;
        m2=black_sum/black_num;
        
        dist=(white_num*(m1-mt)*(m1-mt)+black_num*(m2-mt)*(m2-mt))/(white_num+black_num);
        if(dist_max<dist){
            dist_max=dist;
            t_best=t;
        }
    }

    for(int y=0; y<sample.h; y++){
        for(int x=0 ; x<sample.w; x++){
            int sum=0;
            for( int c=0; c<sample.ch; c++){
                uchar v=sample.GetPixel(y, x, c);
                sum=sum+v;  
            }
            uchar gray = sum / sample.ch;

            for(int c=0; c<sample.ch; c++){
                if(gray<=t_best){
                    binary_image.SetPixel(y, x, c, 0);
                }else{
                    binary_image.SetPixel(y, x, c, 255);
                }
            }
            
        }
    }

    cout << t_best << endl;
    binary_image.save("binary.png");

    return 0;
}