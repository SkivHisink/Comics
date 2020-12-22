#include "Comic.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	cv::CommandLineParser parser(argc, argv, "{@input | example.jpg | input image}");
	Comic comic;
	if (!comic.init(parser.get<cv::String>("@input")))
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	comic.UI();
	return 0;
}