#include <iostream>
#include "ImageHandler.h"
#include <omp.h>
#include <unistd.h>
#include <chrono>


void DoRandomProcess(std::string path) {
        /*
         * Uses the method DrawFromPairs of the ImageHandler class
         */
        ImageHandler MyImage; // Create an object for the image
        MyImage.FileName = path;
        MyImage.BackGround = 0;
        MyImage.DiskColor = 1;

        MyImage.Image = get_vect(MyImage.FileName);
        MyImage.PrintImage(MyImage.Image, "Original Image");

        MyImage.OwnMap = MyImage.CreateMap(MyImage.Image);
        MyImage.GenerateRandomCircles();

}

void DoPairProcess(std::string path) {
        /*
         * Uses the method DrawFromPairs of the ImageHandler class
         */
        ImageHandler MyImage; // Create an object for the image
        MyImage.FileName = path;
        MyImage.BackGround = 0;
        MyImage.DiskColor = 1;
        MyImage.WriteTo = "output-disk-data.dat";

        MyImage.Image = get_vect(MyImage.FileName);
        MyImage.PrintImage(MyImage.Image, "Original Image");

        MyImage.OwnMap = MyImage.CreateMap(MyImage.Image);
        MyImage.DrawFromPairs();
}


int main(int argc, char** argv) {
        
        // Used for mp with dual processing.
        omp_set_num_threads(2);
        std::string path = argv[1];

        auto t0 = std::chrono::high_resolution_clock::now();
        std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> t1;
        std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>> t2;

        #pragma omp parallel
        {
        if(omp_get_thread_num() == 0){
                DoPairProcess(path);
                t1 = std::chrono::high_resolution_clock::now();
                }

        if(omp_get_thread_num() == 1){
                DoRandomProcess(path);
                t2 = std::chrono::high_resolution_clock::now();
                }
        }
        auto time_pair = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()/std::pow(10, 6);
        std::cout << "Time to do pairs = " << time_pair << "ms" << std::endl;
                auto time_random = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t0).count()/std::pow(10, 6);
        std::cout << "Time to do Random = " << time_random << "ms" << std::endl;

        return 0;
}
