#!/bin/sh -x
set -e

wget -c -O original.jpg 'https://cloud.githubusercontent.com/assets/1139185/23364727/3da8c474-fcce-11e6-9f39-7e074e78aa33.jpg'

# retrieve APP2 only:
djpeg -outfile original.ppm -icc profile.icm original.jpg

# recreate original file only with APP2
jpegtran -icc profile.icm -outfile img_app2.jpg -copy none original.jpg

# without app2 this time:
jpegtran -outfile img.jpg -copy none original.jpg

# apply icc profile:
jpgicc img_app2.jpg img_jpgicc.jpg

# craft template:
gdcmimg original.jpg template.dcm

patientid=ICC1
studyid=S1
seriesnum=1
instnum=1
studydate=$(date '+%Y%m%d')
studytime=$(date '+%H%M%S')

opt="-df template.dcm -k InstanceNumber=$instnum -k SeriesNumber=$seriesnum -k StudyID=$studyid -k PatientID=$patientid -k StudyDate=$studydate -k StudyTime=$studytime --invent-type1 --insert-type2"

img2dcm --vl-photo $opt img.jpg img.dcm
img2dcm --vl-photo $opt img.jpg img_iccprofile.dcm
img2dcm --vl-photo $opt img_jpgicc.jpg img_jpgicc.dcm
img2dcm --vl-photo --keep-appn $opt img_app2.jpg img_app2.dcm
img2dcm --vl-photo --keep-appn $opt img_app2.jpg img_app2_iccprofile.dcm

#gdcmimg --template dcmtk.1.dcm img.jpg img.dcm
#gdcmimg --template dcmtk.1.dcm img_jpgicc.jpg img_jpgicc.dcm
#gdcmimg --template dcmtk.1.dcm img_app2.jpg img_app2.dcm
#gdcmimg --template dcmtk.1.dcm img_app2.jpg img_app2_iccprofile.dcm

dcmodify --no-backup --insert-from-file 0028,2000=profile.icm img_iccprofile.dcm
dcmodify --no-backup --insert-from-file 0028,2000=profile.icm img_app2_iccprofile.dcm


#
##dciodvfy icc.1.dcm
rm icc.tar.gz 
tar cvfz icc.tar.gz img.dcm img_iccprofile.dcm img_jpgicc.dcm img_app2.dcm  img_app2_iccprofile.dcm README.txt
