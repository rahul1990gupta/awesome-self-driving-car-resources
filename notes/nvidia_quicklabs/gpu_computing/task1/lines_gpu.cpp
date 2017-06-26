#include <opencv2/opencv.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <stdio.h>

using namespace cv;

int main() {

    Mat src = imread("/home/ubuntu/notebook/task1/images/shield.jpg", 0);

    if (!src.data) {
        printf("failed opening shield.jpg\n");
        exit(1);
    }

    Mat dst;
    gpu::GpuMat d_src(src);

    gpu::GpuMat d_dst;
    gpu::bilateralFilter(d_src, d_dst, -1, 50, 7);
    gpu::Canny(d_dst, d_dst, 35, 200, 3);

    d_dst.download(dst);

    imwrite("/home/ubuntu/notebook/out_gpu.png", dst);

    return 0;
}

