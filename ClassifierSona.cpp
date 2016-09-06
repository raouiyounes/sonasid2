/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#include "ClassifierSona.h"
#include <iostream>
#include<stdio.h>
ClassifierSona::ClassifierSona()
{
#include <iostream> 
}

ClassifierSona::ClassifierSona(const ClassifierSona& other)
{ 

}

ClassifierSona::~ClassifierSona()
{

}

ClassifierSona& ClassifierSona::operator=(const ClassifierSona& other)
{

}
#include <iostream>
bool ClassifierSona::operator==(const ClassifierSona& other)
{

}

vector<Mat> ClassifierSona::loadDb()
{
     Mat im;
       vector<Mat> ims;
       int i;
       char buffer[200];
       for (i=1;i<5;i++)
       {
           sprintf(buffer,  "/home/younes/Documents/newcode/test2/imageDb/im%d.JPG",i);
           im=imread(buffer);
           ims.push_back(im);
       }
       return ims;
  
}





