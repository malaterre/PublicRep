Create 4:2:2

$ convert -size 512x512 xc:#ff0000 red.jpg # default to 4:4:4
$ ffmpeg -i red.jpg -pix_fmt  yuvj422p red422.jpg

To check hash:

ffmpeg -i red422.jpg -f framehash -hash md5 -

Reference:

* https://superuser.com/questions/1316990/using-ffmpeg-to-decode-ybr-full-422-dicom-image

ffmpeg:

ffmpeg -y -i input.jpg -pix_fmt yuvj422p output.yuv
