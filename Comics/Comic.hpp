#pragma once 
#include "opencv2/highgui.hpp"
namespace
{
	struct TrackbarObj
	{
		explicit TrackbarObj(int new_value, int new_max_value)
			:value(new_value), max_value(new_max_value) {}
		int value;
		int max_value;
	};
}
class Comic {
	cv::Mat src, src_gray;
	cv::Mat dst, detected_edges;

	TrackbarObj Thresholdfirst{ 0, 500 };
	TrackbarObj Thresholdsecond{ 0, 500 };
	TrackbarObj sigma{ 0, 100 };
	const int kernel_size = 3;
	const char* window_name = "Comics";
	void CannyThreshold();
	static void s_CannyThreshold(int, void* user)
	{
		auto self = reinterpret_cast<Comic*>(user);
		self->CannyThreshold();
	}
	bool set_original(const std::string& picture_file)
	{
		src = cv::imread(picture_file, cv::IMREAD_COLOR);
		return src.data;
	}
public:
	Comic() = default;
	bool init(const std::string& picture_file);
	void UI();

};