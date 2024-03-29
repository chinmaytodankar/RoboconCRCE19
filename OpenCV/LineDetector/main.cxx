#include <iostream>

#include "include/LineDetector.hxx"
#include "include/Window.hxx"

#include "include/SwitchCamera.hxx"

// Note that the code is primarily sourced from
// http://einsteiniumstudios.com/beaglebone-opencv-line-following-robot.html

// Simple Video Line Detector

//int main()
//{
//   // Get Default Camera
//   Camera::SwitchCameraCV<Camera::Type::NON_PI> camera{0};
//
//   camera.Format(CV_8UC3);
//   camera.Resolution(160, 120);
//
//   if (!camera.open())
//   {
//      std::cerr << "Unable to Access Camera";
//      return EXIT_FAILURE;
//   }
//
//   Detector::Properties props;
//   props
//       .FindColour(Detector::Colour::WHITE)
//       // TODO: Find CLAHE Algorithm Values
//       .CLAHEClipLimit(1)
//       .CLAHETilesGrid({8, 8});
//   // ROI is Upper Half By Default
//   //.ROIHalf(camera.Resolution());
//
//   Detector::Line line{props};
//
//   while (camera.isOpened())
//   {
//      cv::Mat img;
//      camera.read(img);
//
//      Detector::Point centroid;
//      if (line.Centroid(img, &centroid))
//      {
//         std::cout << "Object detected at " << centroid;
//         cv::circle(img, centroid, 5, cv::Scalar{0, 0, 255});
//      }
//      else
//         std::cerr << "No Object Detected";
//
//      UI::Window window{"img", false};
//      window.show(img);
//      if (UI::Window::waitKey(5) == 'q')
//         break;
//   }
//   return EXIT_SUCCESS;
//}

// Simple Timer and Line Detector

// #include <chrono>
// int main()
//{
//   // Get Default Camera
//   Camera::SwitchCameraCV<Camera::Type::NON_PI> camera{0};
//
//   camera.Format(CV_8UC3);
//   camera.Resolution(160, 120);
//
//   if (!camera.open())
//   {
//      std::cerr << "Unable to Access Camera";
// return EXIT_FAILURE;
//   }
//
//   Detector::Properties props;
//
//   // Get Colour Values for Yellow from
//   // https://stackoverflow.com/questions/9179189/detect-yellow-color-in-opencv
//   // .setColourBounds(cv::Scalar{20, 70, 70}, cv::Scalar{30, 255, 255})
//   // Get Colour Values for Purple from
//   // https://stackoverflow.com/questions/17474020/finding-exact-hsv-values-of-colors
//   //.setColourBounds2(cv::Scalar(140, 0, 210), cv::Scalar(180, 255, 255))
//   //.setColourBounds(cv::Scalar{40, 50, 30}, cv::Scalar{140, 255, 255})
//   props.FindColour(Detector::Colour::WHITE)
//   //ROI is Upper Half By Default
//// TODO: Find CLAHE Algorithm Values
//.CLAHEClipLimit(4).CLAHETilesGrid({8, 8})
//       .ROIHalf(camera.Resolution());
//
//   Detector::Line line{props};
//
//   cv::Mat    img;
//   UI::Window window{"img"};
//
//   Detector::Point centroid;
//
//   std::size_t count = 0;
//
//   while (camera.isOpened())
//   {
//      {
//         auto const prev_time = std::chrono::system_clock::now().time_since_epoch();
//         camera.read(img);
//         auto const cur_read_time = std::chrono::system_clock::now().time_since_epoch();
//
//         auto const millis_read_time =
//             std::chrono::duration_cast<std::chrono::milliseconds>(cur_read_time - prev_time)
//                 .count();
//
//         if (std::empty(img))
//            break;
//
//         if (line.Centroid(img, &centroid))
//            cv::circle(img, centroid, 3, {0, 0, 255});
//         else
//         {
//            std::cout << "Object not Detected";
//            continue;
//         }
//         auto const cur_time = std::chrono::system_clock::now().time_since_epoch();
//
//         auto const millis_spent =
//             std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - prev_time).count();
//
//         if (millis_spent > 40)
//         {
//            std::cout << "Time Processing " << (millis_spent - millis_read_time) << " NoOfReads "
//            << count
//                      << " Read Portion " << millis_read_time << '\n';
//            count = 0;
//         }
//         else
//         {
//            ++count;
//         }
//      }
//      window.show(img);
//      window.move(800, 0);
//
//      if (window.waitKey(5) == 'q')
//         break;
//   }
//
//   return 0;
//}

// Simple Image Line Detector

// int main()
//{
//   auto const img = cv::imread("path/to/image.ext").getUMat(cv::ACCESS_READ);
//
//   Detector::Properties props;
//   props
//       .FindColour(Detector::Colour::WHITE)
//       // TODO: Find CLAHE Algorithm Values
//       .CLAHEClipLimit(4)
//       .CLAHETilesGrid({8, 8});
//
//   Detector::Line const line{props};
//
//   Detector::Point centroid;
//
//   if (line.Centroid(img, &centroid))
//      cv::circle(img, centroid, 5, /*Red*/ {0, 0, 255});
//   else
//      return EXIT_FAILURE; // No Centroid Detected
//
//   UI::Window window{"Result"};
//   window.show(img);
//   UI::Window::waitKey();
//
//   UI::Window::destroyAllWindows();
//
//   return EXIT_SUCCESS;
//}

// Simple Line Detector using Raspberry Pi

//#include "include/EasyTransferI2CPi.hxx"
//#include <wiringPi.h>
//
// auto constexpr const I2C_DEV_ADD = 9;
//
// int main()
//{
//   try
//   {
//      wiringPiSetup();
//
// Pi::EasyTransferI2C device{I2C_DEV_ADD};
//
//      // Get Default Camera
//      Camera::SwitchCameraCV<Camera::Type::NON_PI> camera{0};
//
//      // TODO: Verify Resolution
//      camera.Format(CV_8UC3).Resolution(160, 120);
//
//      if (!camera.isOpened())
//      {
//         std::cerr << "Unable to Access Camera";
// return EXIT_FAILURE;
//      }
//
//      Detector::Properties props;
//
//      // Get Colour Values for Yellow from
//      // https://stackoverflow.com/questions/9179189/detect-yellow-color-in-opencv
//      // .setColourBounds(cv::Scalar{20, 70, 70}, cv::Scalar{30, 255, 255})
//      // Get Colour Values for Purple from
//      // https://stackoverflow.com/questions/17474020/finding-exact-hsv-values-of-colors
//      //.setColourBounds(cv::Scalar{40, 50, 30}, cv::Scalar{140, 255, 255})
//      //.addColourBounds(cv::Scalar{0, 0, 210}, cv::Scalar{40, 255, 255})
//      //    .addColourBounds(cv::Scalar(140, 0, 210), cv::Scalar(180, 255, 255))
//      props.FindColour(Detector::Colour::WHITE)
//// TODO: Find CLAHE Algorithm Values
//.CLAHEClipLimit(4).CLAHETilesGrid({8, 8})
//      //ROI Is Upper Half By Default
//      .ROIHalf(camera.Resolution());
//
//      Detector::Line line{props};
//
//      cv::Mat    img;
//      UI::Window window{"img"};
//
//      std::cout << "Start";
//
//      // window.show(cv::Mat::zeros({700, 700}, CV_8UC1));
//      while (camera.isOpened())
//      {
//         if (!camera.read(img))
//            break;
//
//         Detector::Point centroid;
//         if (line.Centroid(img, &centroid))
//         {
//            cv::circle(img, centroid, 5, {0, 0, 255});
//            device.write(centroid.x);
//            std::cout << "The LineCenter is " << centroid << '\n';
//         }
//         else
//         {
//            std::cerr << "Unable to Detect Image\n";
//            img = cv::Mat::zeros(img.rows, img.cols, img.type());
//         }
//
//         window.show(img);
//         window.move(800, 0);
//         if (window.waitKey(5) == 'q')
//         {
//            break;
//         }
//      }
//   }
//   catch (...)
//   {
//      std::cout << "Exception occured";
//   }
//
//   return 0;
//}

#include "include/EasyTransferI2CPi.hxx"
#include <wiringPi.h>

auto constexpr const I2C_DEV_ADD = 9;

int main()
{
   wiringPiSetup();

   Pi::EasyTransferI2C device{I2C_DEV_ADD};

   std::cout << "Start";
   struct X
   {
      int i ;
   };
   X x;
   x.i = 0;
   // window.show(cv::Mat::zeros({700, 700}, CV_8UC1));
   while (true)
   {
      x.i++;
      device.write(x);
   }

   return 0;
}