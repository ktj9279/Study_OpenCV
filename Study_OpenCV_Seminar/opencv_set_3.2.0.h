#pragma once
#pragma warning(disable:4819)

#include "opencv2\opencv.hpp"

#if _DEBUG
#pragma comment(lib, "opencv_world320d.lib")
#else NDEBUG
#pragma comment(lib, "opencv_world320.lib")
#endif