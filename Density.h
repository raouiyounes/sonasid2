/*
 * Density.h
 *
 *  Created on: Jul 25, 2016
 *      Author: younes
 */

#ifndef DENSITY_H_
#define DENSITY_H_

#include "Image.h"
#include <vector>
#include <eigen3/Eigen/Dense>

using namespace std;
using namespace Eigen;
using namespace cv;
namespace sonasid {

class Density: public Image {
	MatrixXd PtsAnnotation;

public:
	vector<int> anot_x_coor;
	vector<int> anot_y_coor;
	vector<int> anot_x1;
	vector<int> anot_y1;
	
	int numberof_annot;
	char *img_str;
	Mat img;
	int index;
	Density();
	void getXY();
	virtual ~Density();
	friend void onMouse( int e, int x, int y, int d, void *ptr );
	MatrixXd readAnnotations();
	 vector<float > computeF0();
  void  CallBackFunc(int event, int x, int y, int flags, void* userdata);

};

} /* namespace sonasid */

#endif /* DENSITY_H_ */
