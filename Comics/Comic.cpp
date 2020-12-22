#include "Comic.hpp"
#include <iostream>
#include "opencv2/imgproc.hpp"

bool Comic::init(const std::string& picture_file) {
	if (picture_file.empty() || !set_original(picture_file)) {
		return false;
	}
	dst.create(src.size(), src.type());
	namedWindow(window_name, cv::WINDOW_AUTOSIZE);
	cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
	cv::createTrackbar("Threshold1:", window_name, &Thresholdfirst.value, Thresholdfirst.max_value, s_CannyThreshold, this);
	cv::createTrackbar("Threshold2:", window_name, &Thresholdsecond.value, Thresholdsecond.max_value, s_CannyThreshold, this);
	cv::createTrackbar("Sigma:", window_name, &sigma.value, sigma.max_value, s_CannyThreshold, this);
	CannyThreshold();
	return true;
}

void Comic::CannyThreshold()
{
	GaussianBlur(src_gray, detected_edges, cv::Size(kernel_size, kernel_size), 100.0f / static_cast<float>(sigma.value));
	Canny(detected_edges, detected_edges, Thresholdfirst.value, Thresholdsecond.value, kernel_size);
	dst = cv::Scalar::all(0);
	src.copyTo(dst, detected_edges);
	cv::subtract(src, dst, dst);
	imshow(window_name, dst);
}

void Comic::UI()
{
	bool end = false;
	while (!end)
	{
		cv::Rect window_size = cv::getWindowImageRect(window_name);
		if (window_size.x == -1)
		{
			break;
		}
		std::cout << "Write arg for next step:" << std::endl << "1) Save" << std::endl << "2) Exit" << std::endl;
		int key = cv::waitKey();
		switch (key)
		{
		case '1':
		{
			std::cout << "File: ";
			std::string answer;
			std::getline(std::cin, answer);
			try {
				imwrite(answer, dst);
				std::cout << "Successful saved" << std::endl;
			}
			catch (cv::Exception exception) {
				std::cout << exception.what() << std::endl;
			}
			break;
		}
		case '2': {
			end = true;
			break;
		}
		default: {
			if (key != -1)
				std::cout << "Incorrect command. Try again." << std::endl;
			break;
		}
		}
	}
}