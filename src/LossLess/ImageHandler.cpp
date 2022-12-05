#include <iostream>
#include "ImageHandler.h"

#include <fstream>
#include <vector>
#include <string>


void DoRandomProcess() {
	ImageHandler MyImage; // Create an object for the image
        MyImage.FileName = "../benchmark.0032.pxl";
	MyImage.BackGround = 0;
	MyImage.DiskColor = 1;


        MyImage.Image = get_vect(MyImage.FileName);
        MyImage.PrintImage(MyImage.Image, "Original Image");

        MyImage.OwnMap = MyImage.CreateMap(MyImage.Image);
	MyImage.GenerateRandomCircles();

}

void DoPairProcess() {
	ImageHandler MyImage; // Create an object for the image
        MyImage.FileName = "../benchmark.0032.pxl";
	MyImage.BackGround = 0;
	MyImage.DiskColor = 1;
	MyImage.WriteTo = "output-disk-data.dat";

        MyImage.Image = get_vect(MyImage.FileName);
        MyImage.PrintImage(MyImage.Image, "Original Image");

        MyImage.OwnMap = MyImage.CreateMap(MyImage.Image);
	MyImage.DrawFromPairs();
}
	
int main() {

        DoRandomProcess();
	DoPairProcess();

        return 0;
}

