#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "read.h"
#include <math.h>


// Used to sort pair vector in DrawFromPairs 
bool sortbysecdesc(const std::pair<std::pair<int, int>, int> &a, const std::pair<std::pair<int, int>, int> &b){
                        return a.second>b.second;
               }


class ImageHandler {
	
	public:		// Acsess specifier 
		std::string FileName; // Attribute (File name of Image) 
		std::string WriteTo; // Specify the file that should be written to
		int BackGround; // Assume a back ground color 0 or 1
		int DiskColor; // Give color to the disk

		std::vector<std::vector<int>> OwnMap;
		std::vector<std::vector<int>> Image;

		int CountCircles {0};

		void PrintImage(std::vector<std::vector <int>> Image, std::string title) {
			std::cout << title << std::endl;
			for (int i {0}; i < Image.size(); i++) {
				for (int j {0}; j < Image[i].size(); j++) {
					std::cout << Image[i][j];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		std::vector<std::vector<int>> CreateMap(std::vector<std::vector <int>> Image){		
			int size = Image.size();
			std::vector<std::vector <int>> OwnMap(size, std::vector<int> (size, 0));
			return OwnMap;
		}

		void DrawCircle(int x, int y, int r) {			
			// This functions just puts the circle on our own map

			for (int i {x-r}; i < x+r+1; i++) {
				for (int j {y-r}; j < y+r+1; j++) {
					if (this->dist(x, y, i, j) <= r && Image[i][j] == DiskColor) { 
						OwnMap[i][j] = DiskColor;
					}
				}
			}
		}

		void GenerateRandomCircles() {
			// Draws Random circles until our own map is equal to the Image
			
			while (OwnMap != Image) {

				this->SelectPoints();	
				int x = this->x_rand;
				int y = this->y_rand;
				int r = this->GetMaximumRadius(x, y, 1, Image.size());
				
				if (CheckHome(x, y, r)) {
					DrawCircle(x, y, r);

					CountCircles++;
				}
			}
			std::cout <<"Circle Count = " << CountCircles << " Process: ";
			PrintImage(OwnMap, "Random");
		}

		void DrawFromPairs() {
			// Draws Circles using the pairs starting with largest radius until the map is equal to the image or all pairs have been used.
			// And writes data to output file.
			
			std::vector<std::pair<std::pair<int, int>, int>> p = this->FindPairs();					
			std::sort(p.begin(), p.end(), sortbysecdesc);
			int TrueCount = CountTrueCircles(p);

			OwnMap = CreateMap(Image); // Renew map for visualization purpose only

			std::fstream myfile;
                        myfile.open(WriteTo, std::ios_base::out);
			myfile << OwnMap.size() << "\t" << OwnMap[0].size() << "\n" << BackGround << "\n" << "\n" << TrueCount << "\n";
				
			for (auto pair: p) {				

				int x = pair.first.first;
				int y = pair.first.second;
				int r = pair.second;

				if (this->CheckHome(x, y, r)){
					DrawCircle(x, y, r);
					myfile << x << "\t" << y << "\t" << r << "\t" << DiskColor << "\n";
				}

				if (Image == OwnMap) {
					myfile.close();
					break;
				}
			}
						
			std::cout << "Circle Count = " << TrueCount << " Process: ";
			PrintImage(OwnMap, "Pairs");
		}
	
	private:
		int x_rand;
		int y_rand;

		float dist(int x1, int y1, int x2, int y2) {
			return sqrt(pow((x1-x2), 2) + pow((y1-y2), 2));
		}


		int GetMaximumRadius(int x, int y, int r, int size) {
			// Gets maximum radius for random generated x and y coordinate
			
			if (CheckEdges(x, y, r, size) && ZeroEdges(x, y, r) && CheckDiagonals(x, y, r)) {
				return GetMaximumRadius(x, y, r+1, Image.size());
			} else{
				return r-1;
			       }	
		}	

		bool ZeroEdges(int x, int y, int r) {
			// Checks for how much the radius can be incremented before hitting a zero on the image
			
			if (Image[x-r][y] != BackGround && Image[x][y+r] != BackGround && 
				Image[x+r][y] != BackGround && Image[x][y-r] != BackGround) {
				return true;
			} else {return false;}
		}

		bool CheckDiagonals(int x, int y, int r) {
			// Checks if the pixels on the diagonals are not background
			
			int radius = floor(r*(sqrt(2)/2));
			int up_x = x-radius;
			int down_x = x+radius;
			int y_right = y+radius;
			int y_left = y-radius;

			if (Image[up_x][y_right] != BackGround && Image[up_x][y_left] != BackGround 
			    && Image[up_x][y_right] != BackGround && Image[down_x][y_left] != BackGround) {
				return true;
			} else {return false;}
			
		}

		
		bool CheckEdges(int x, int y, int r, int size) {
			// Checks if radius is within the image boundaries
			
			if (x-r > 0 && x+r < size && y-r > 0 && y+r < size) {
				return true;
			} else {return false;}
		}

		int SelectPoints() {	
			// Selects random points that are not background color 
			
			x_rand = 0 + (rand()%OwnMap.size());
			y_rand = 0 + (rand()%OwnMap.size());
				
			if (Image[x_rand][y_rand] == BackGround) { 
				SelectPoints();
				CountCircles++;
			}

			return 0;
		}

		std::vector<std::pair<std::pair<int, int>, int>> FindPairs() {
	                // This functions should find all pixelvalues pixel(i, j) that are non zeros and store them as well as their maximum radius.

	                std::vector<std::pair<std::pair<int, int>, int>> PixPairsRadius;

	                for(int i {0}; i < Image.size(); i++) {
	                        for(int j {0}; j < Image.size(); j++) {
	                                int r = GetMaximumRadius(i, j, 1, Image.size());
	                                if(Image[i][j] != BackGround) {
	                                        PixPairsRadius.push_back(std::make_pair(std::make_pair(i, j), r));
	                                        }
	                                }
	                        }

	                return PixPairsRadius;
	        }

		bool CheckHome(int x, int y, int r) {
			// This function only checks if the current point has been drawn on already
			
			bool home = (OwnMap[x][y] == BackGround);
			return home;
		}

		int CountTrueCircles(std::vector<std::pair<std::pair<int, int>, int>> p){
			// Counts Circles that are truly being used i.e exluding repition
			
			for (auto pair: p) {

                                int x = pair.first.first;
                                int y = pair.first.second;
                                int r = pair.second;

                                if (this->CheckHome(x, y, r)){
                                        DrawCircle(x, y, r);
                                        CountCircles++;

                                }

                                if (OwnMap == Image) {
                                        break;
                                }
                        }
			return CountCircles;
		}

};

#endif
