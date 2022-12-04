#include <iostream>
#include <vector>
#include <string>

#include "read.h"
#include <math.h>


// Used to sort pair vector in DrawFromPairs 
bool sortbysecdesc(const std::pair<std::pair<int, int>, int> &a, const std::pair<std::pair<int, int>, int> &b){
                        return a.second>b.second;
                }

class ImageHandler {
	
	public:		// Acsess specifier 
		std::string FileName; // Attribute (File name of Image) 
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
			std::cout << "The size of our own Image "<< OwnMap.size() << " x "<< OwnMap[0].size() << std::endl;
			return OwnMap;
		}

		void DrawCircle(int x, int y, int r) {
			
			// This functions just puts the circle on our own map
			for (int i {x-r}; i < x+r+1; i++) {
				for (int j {y-r}; j < y+r+1; j++) {
					if (this->dist(x, y, i, j) <= r && Image[i][j] == 1) { 
						OwnMap[i][j] = 1;
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
				
				DrawCircle(x, y, r);
				CountCircles++;
			}
			std::cout <<"Circle Count = " << CountCircles << " Process: ";
			PrintImage(OwnMap, "Random");
		}

		void DrawFromPairs() {
			std::vector<std::pair<std::pair<int, int>, int>> p = this->FindPairs();					
			std::sort(p.begin(), p.end(), sortbysecdesc);

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
				
			std::cout << "Circle Count = " << CountCircles << " Process: ";
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
			if (CheckEdges(x, y, r, size) && ZeroEdges(x, y, r)) {
				return GetMaximumRadius(x, y, r+1, Image.size());
			} else{
				return r-1;
			       } 
		}	

		bool ZeroEdges(int x, int y, int r) {
			// Checks for how much the radius can be incremented before hitting a zero on the image
			if (Image[x-r][y] != 0 && Image[x][y+r] != 0 && Image[x+r][y] != 0 && Image[x][y-r] != 0) {
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

			x_rand = 0 + (rand()%OwnMap.size());
			y_rand = 0 + (rand()%OwnMap.size());
				
			if (Image[x_rand][y_rand] == 0) { 
				SelectPoints();
				CountCircles++;
			}

			return 0;
		}

		std::vector<std::pair<std::pair<int, int>, int>> FindPairs() {
	                // This functions should find all pixelvalues pixel(i, j) that are non zeros and store them

	                std::vector<std::pair<std::pair<int, int>, int>> PixPairsRadius;

	                for(int i {0}; i < Image.size(); i++) {
	                        for(int j {0}; j < Image.size(); j++) {
	                                int r = GetMaximumRadius(i, j, 1, Image.size());
	                                if(Image[i][j] != 0) {
	                                        PixPairsRadius.push_back(std::make_pair(std::make_pair(i, j), r));
	                                        }
	                                }
	                        }

	                return PixPairsRadius;
	        }

		bool CheckHome(int x, int y, int r) {
			// This function only checks if the current point has been drawn on already and if the neighbouring pixels are available
			
			bool home = (OwnMap[x][y] == 0);
			return home;
		}
};


int main() {

	ImageHandler MyImage; // Create an object for the image
	MyImage.FileName = "../benchmark.0032.pxl";
	
	MyImage.Image = get_vect(MyImage.FileName);
	MyImage.PrintImage(MyImage.Image, "Original Image");
	
	MyImage.OwnMap = MyImage.CreateMap(MyImage.Image);

//	MyImage.GenerateRandomCircles(); // Use this in order to reproduce the image by random generation
	
	MyImage.DrawFromPairs(); // Use this in order to generate circles from pairs method
	
	return 0;
}
