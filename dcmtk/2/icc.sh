#!/bin/sh -x
set -e

wget -c -O icc.jpg 'https://cloud.githubusercontent.com/assets/1139185/23364727/3da8c474-fcce-11e6-9f39-7e074e78aa33.jpg'

djpeg -outfile icc.ppm -icc profile.icm icc.jpg

gdcmimg icc.jpg template.dcm

patientid=ICC1
studyid=S1
seriesnum=1
instnum=1
studydate=$(date '+%Y%m%d')
studytime=$(date '+%H%M%S')

img2dcm -df template.dcm -k InstanceNumber=$instnum -k SeriesNumber=$seriesnum -k StudyID=$studyid -k PatientID=$patientid -k StudyDate=$studydate -k StudyTime=$studytime --invent-type1 --insert-type2 --vl-photo icc.jpg icc.1.dcm
img2dcm --invent-type1 --insert-type2 --vl-photo --keep-appn icc.jpg icc.2.dcm
dcmodify --insert-from-file 0028,2000=profile.icm icc.2.dcm

dciodvfy icc.1.dcm
