#include <stdio.h>
#include <iostream>
#include <fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/imgproc/imgproc_c.h>
#include <eigen3/Eigen/Dense>
 #include <cv.h>
#include <highgui.h>
#include "Density.h"
#include "ClassifierSona.h"
using namespace Eigen;
using namespace cv;
using namespace std;
typedef vector<std::vector<double> > struct1;
namespace sonasid{ 



class Circles{
  IplImage *image_matrix;
struct1 descriptor_vect;
public: 
  int  number_of_line;
  Circles(char *image_path){
    image_matrix=cvLoadImage(image_path);
  }
public:
int SURFExtractor(int nb_of_features){
namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
cvShowImage( "Hough Circnb_of_featuresle Transform Demo",  image_matrix );
  cvWaitKey(0);
	//  Mat img_1 = image_data;
	 	  //-- Step 1: Detect the keypoints using SURF Detector
	  int minHessian = 400;
	 SURF detector( minHessian );
	 	   int Threshl=40;
	   int Octaves=2;
	   float PatternScales=1.0f;
	  CvMat* prevgray = 0, *image = 0, *gray =0;
//IplImage* image_matrix=cvLoadImage("test_image.jpg");
image = cvCreateMat(image_matrix->height, image_matrix->width, CV_8UC1);
	  CvMemStorage* storage = cvCreateMemStorage(0);
	  cvCvtColor(image_matrix, image, CV_BGR2GRAY);
	  //Define sequence for storing surf keypoints and descriptors
	  CvSeq *imageKeypoints = 0, *imageDescriptors = 0;
	  int i,j;
	  ofstream file("surf.txt");
vector<double> descriptor_row;
	  CvSURFParams params = cvSURFParams(500, 1);
	  cvExtractSURF( image, 0, &imageKeypoints, &imageDescriptors, storage, params );
	  for( i = 0; i < imageDescriptors->total; i++ )
	  {
	float* r = (float*)cvGetSeqElem( imageDescriptors, i);
	j=0;
int dim=50;

//cout<<nb_of_features;
	// changer dim pour obtenir plus de features
	while(j<nb_of_features){
	  	  descriptor_row.push_back(*r);
	  r++;
	  	j++;
	file<<*r<<" ";
	}
	file<<"\n";
	descriptor_vect.push_back(descriptor_row);
	number_of_line++;
	descriptor_row.clear();
     }
  return 0;
}

 
};
}
  using namespace sonasid;
int main(){
 Density *dst=new Density();
 dst->numberof_annot=0;
dst->getXY();
for(int i=0;i<dst->anot_x_coor.size();i++)
cout<<"  "<<dst->anot_x_coor.at(i);
vector<float > F0;


F0=dst->computeF0();
float s=0.0;
for(int i=0;i<F0.size();i++)
s+=F0.at(i);

cout<<"zzzzzzzz"<<s;


 
 
vector<Mat>  db;
ClassifierSona  *classif=new ClassifierSona();

db=classif->loadDb();








return 0;
} 

