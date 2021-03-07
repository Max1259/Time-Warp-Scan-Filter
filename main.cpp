#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

    cv::Mat img, img2, total;
    std::vector<cv::Mat> images, live;
    cv::VideoCapture vid;
    char dir;
    int delay = 1;
    String filepath = "C:\\Users\\maxho\\Pictures\\Code\\";

    vid.open(0);

    while (1) {

        images.clear();
        vid >> img;

        cout << "\nHorizontal or Vertical (h/v): " << endl;
        cin >> dir;

        if (dir == 'h') {

            for (int i = 0; i < img.size().width - 1; i++) {

                img.release();
                vid >> img;
                cv::resize(img, img, cv::Size(), 1, 1);
                cv::flip(img,img,1);

                live.clear();

                img2 = img(cv::Rect(i, 0, img.size().width-i-1, img.size().height));
                images.push_back(img.col(i));

                for (int j = 0; j < images.size(); j++) {
                    live.push_back(images[j]);
                }

                live.push_back(img2);

                cv::hconcat(live, total);

                line(total, cv::Point(i,0), cv::Point(i,total.size().height - 1), cv::Scalar::all(255), 1);
                cv::imshow("out1", total);

                if (cv::waitKey(delay) >= 0) break;
            }
        }
        else if (dir == 'v') {

            for (int i = 0; i < img.size().height - 1; i++) {

                img.release();
                vid >> img;
                cv::resize(img, img, cv::Size(), 1, 1);
                cv::flip(img, img, 1);

                live.clear();

                img2 = img(cv::Rect(0, i, img.size().width, img.size().height - i - 1));
                images.push_back(img.row(i));

                for (int j = 0; j < images.size(); j++) {
                    live.push_back(images[j]);
                }

                live.push_back(img2);

                cv::vconcat(live, total);

                line(total, cv::Point(0, i), cv::Point(total.size().width - 1, i), cv::Scalar::all(255), 1);
                cv::imshow("out1", total);

                if (cv::waitKey(delay) >= 0) break;
            }
        }
        
        char select, repeat;
        std::string filename;
        cout << total.type() << endl;
        cout << total.type() << endl;

        cout << "\nSave image? (y/n): ";
        cin >> select;

        if (select == 'y') {

            cout << "\nEnter filename: " << endl;
            cin >> filename;

            vector<int> compression_params;
            compression_params.push_back(IMWRITE_JPEG_QUALITY);
            compression_params.push_back(100);

            bool status = cv::imwrite(filepath + filename + ".bmp", total, compression_params);

            if (status) {
                cout << "\nSaved" << endl;
            }
            else {
                cout << "\nError" << endl;
            }

            cout << "\nTry again? (y/n): ";
            cin >> repeat;

            if (repeat == 'n') exit(1);
        }
        else if (select == 'n') {

            cout << "\nTry again? (y/n): ";
            cin >> repeat;

            if (repeat == 'n') exit(1);
        }
    }
    return 0;
}