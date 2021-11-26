Create 4:2:2

$ convert -size 512x512 xc:#ff0000 red.jpg # default to 4:4:4
$ ffmpeg -i red.jpg -pix_fmt  yuvj422p red422.jpg

To check hash:

ffmpeg -i red422.jpg -f framehash -hash md5 -

Reference:

* https://superuser.com/questions/1316990/using-ffmpeg-to-decode-ybr-full-422-dicom-image

ffmpeg:

ffmpeg -y -i input.jpg -pix_fmt yuvj422p output.yuv

---

TODO:

https://stackoverflow.com/questions/16390783/how-to-compress-yuyv-raw-data-to-jpeg-using-libjpeg
cinfo->raw_data_in = true;

https://pmeerw.net/blog/programming/uyvy-jpeg.html

https://github.com/GracieZhou/test/blob/master/CODE/android/vendor/mstar/supernova/projects/msrv/control/src/MSrv_Control_common.cpp
https://android.googlesource.com/platform/frameworks/base.git/+/android-4.2.2_r1/core/jni/android/graphics/YuvToJpegEncoder.cpp
https://gitlab.tubit.tu-berlin.de/justus.beyer/streamagame_platform_frameworks_base/blob/1a94c7db9fc78e8e7a9d48546622776d27a79a6a/core/jni/android/graphics/YuvToJpegEncoder.cpp
https://stackoverflow.com/questions/16390783/how-to-compress-yuyv-raw-data-to-jpeg-using-libjpeg

https://compression.fiches-horaires.net/la-compression-avec-perte-1/le-compression-jpeg/
