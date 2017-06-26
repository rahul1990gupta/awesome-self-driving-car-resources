#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

int main() {

    Mat src = imread("/home/ubuntu/notebook/task1/images/shield.jpg", 0);

    if (!src.data) {
        printf("failed opening shield.jpg\n");
        exit(1);
    }

    Mat dst;

    bilateralFilter(src, dst, -1, 50, 7);
    Canny(dst, dst, 35, 200, 3);

    imwrite("/home/ubuntu/notebook/out_cpu.png", dst);

    return 0;
}

