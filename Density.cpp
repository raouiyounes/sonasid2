/*
 * Density.cpp
 *
 *  Created on: Jul 25, 2016
 *      Author: younes
 */

#include "Density.h"
#include <string>
#include <vector>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <fstream>
#include <map>
#include <eigen3/unsupported/Eigen/MatrixFunctions>
#define pi 3.14
using namespace std;
using namespace Eigen;
namespace sonasid {
Mat img = cv::imread("b.jpg", 0); // force grayscale
Mat thresh=Mat::zeros(img.size(),CV_8UC1);
ofstream annotation("file.txt");
 vector<int>  anot_xx;
vector<int>  anot_yx;
int numberof_annot_glob=0;
void onMouse(int e, int x, int y, int d, void *ptr );

Density::Density() {
	// TODO Auto-generated constructor stub
	index=0;
}

 void Density::getXY(){
	Mat img = cv::imread("/home/younes/Documents/newcode/test2/test.jpeg"); // force grayscale
	Mat thresh=Mat::zeros(img.size(),CV_8UC1);
	MatrixXd anot_coord(5,2);
	Mat binary;
	Mat img_loc=this->img;
      Point p;
    threshold(img,binary,50,255,THRESH_TOZERO);
namedWindow("thresh");   
imshow("thresh",img);

setMouseCallback( "thresh", onMouse, 0 );

cvWaitKey(4000);

numberof_annot=numberof_annot_glob;

MatrixXd annot(2,2);

for(int i=0;i<anot_xx.size();i++){
anot_x_coor.push_back(anot_xx.at(i));
anot_y_coor.push_back(anot_yx.at(i));
}
}


Density::~Density() {
	// TODO Auto-generatint anotate;

}
vector<float> Density::computeF0(){

int anotate;
MatrixXd patch(3,3);
Mat imgMat=imread("/home/younes/Documents/newcode/test2/test.jpeg");
float pixelValue;
vector<int> x_patch,y_patch;
VectorXd pixel(2);
MatrixXd sigma(2,2);
int i,j;  //dimensions of the image
float std_x_patch,std_y_patch;
vector<VectorXd> pixel_coord;
vector<MatrixXd> covariance;


// calcul de la covariance


for(i=0;i<imgMat.rows;i++)
	for(j=0;j<imgMat.cols;j++){

if(i-1>=0 && i+1<=imgMat.rows && j-1>=0 && j+1<=imgMat.rows){

x_patch.push_back(i-1);
x_patch.push_back(i);
x_patch.push_back(i+1);
y_patch.push_back(j-1);
y_patch.push_back(j);
y_patch.push_back(j+1);
std_x_patch=0.0,std_y_patch=0.0;

float m_x_patch=(x_patch.at(0)+x_patch.at(1)+x_patch.at(2))/3;
float m_y_patch=(y_patch.at(0)+y_patch.at(1)+y_patch.at(2))/3;

for(int t=0;t<3;t++){
	std_x_patch+=pow((x_patch.at(t)-m_x_patch),2);
	std_y_patch+=pow((y_patch.at(t)-m_y_patch),2);
}    
pixel(0)=i;
pixel(1)=j;
sigma(0,0)=sqrt(std_x_patch);
sigma(0,1)=0.0;
sigma(1,0)=0.0;
sigma(1,1)=sqrt(std_y_patch);
 pixel_coord.push_back(pixel);
 covariance.push_back(sigma);
}
}
 vector<vector<double> > P0;


 MatrixXd coefficient(2,2);
 MatrixXd coefficient_exp(2,2);
 MatrixXd value_of_exp(2,2);
MatrixXd N(imgMat.rows,imgMat.cols);
 VectorXd X(2); 
cout<<"eeeeeeeeeeeeee"<<numberof_annot;
  MatrixXd P(numberof_annot,2);
float sigma_1=5.2;
 MatrixXd Gaussian_i(2,2);https://openclassrooms.com/courses/deboguer-son-programme-avec-gdb

for(int j=0;j<numberof_annot;j++){
  P(j,0)=anot_x_coor.at(j);
  P(j,1)=anot_y_coor.at(j);           
}

vector<float> F0_mat;
vector<MatrixXd> F000;
 MatrixXd F00(2,2);
 int k=0;
 float Gaussian_i2=0.0;
 // calculer la gaussienne
 float f002=0.0;            

 float coefficient_exp2=0.0;
 float value_of_exp2=0.0;
 int ll=0;
 for(i=0;i<imgMat.rows;i++)
  for(j=0;j<imgMat.cols;j++){
    if(i-1>=0 && i+1<=imgMat.rows && j-1>=0 && j+1<=imgMat.rows){

   f002=0.0;
    for(int k=0;k<numberof_annot;k++){
      VectorXd temp_P(2);
      temp_P(0)=P(k,0);
      temp_P(1)=P(k,1);
    X= (pixel_coord.at(ll)-temp_P);

     MatrixXd cova(2,2);
     cova=covariance.at(k);
     value_of_exp2=-0.5*X.transpose()*cova.inverse()*X;
   coefficient_exp2=exp(value_of_exp2);

   Gaussian_i2=sqrt((1/(2*pi)*cova.determinant()))*coefficient_exp2;
  
   f002=f002+Gaussian_i2;
  }  
  ll++;
F0_mat.push_back(f002/5);
    }  
}

 
return F0_mat;
}

void onMouse( int event, int x, int y, int, void* )
{
    if( event != CV_EVENT_LBUTTONDOWN )
            return;
    Point pt = Point(x,y);
    std::cout<<"x="<<pt.x<<"\t y="<<pt.y;
    annotation<<pt.x<<" "<<pt.y<<endl;
    anot_xx.push_back(x);
    anot_yx.push_back(y);
numberof_annot_glob++;

} 

void mouseEvent (int evt, int x, int y, int flags, void* param)
{                    
     if (evt == CV_EVENT_LBUTTONDOWN)
     { 
          printf("%d %d\n",x ,y );  
     }         
}

MatrixXd Density::readAnnotations(){
	int numberof_annot;
	MatrixXd annot_loc(numberof_annot,2);
	ifstream myfile ("file.txt");
	stringstream ss;
	string s;
	int j=0;
	string line;
	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line) && j++<numberof_annot)
	    {
ss<<line;
for(int col=0;col<2;col++){
getline( ss,s,' ');
cout<<atoi(s.c_str());
annot_loc(j,col)=atoi(s.c_str());
cout<<annot_loc(j,col);
ss<<"";
}
	    }
	    myfile.close();
	  }

return annot_loc;
}


}
