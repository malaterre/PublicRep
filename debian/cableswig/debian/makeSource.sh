#! /bin/sh

set -e

VERSION=0.1.0
ITKBRANCHTAG=ITK-3-20
DATE=20110226
export CVSROOT=:pserver:anonymous@public.kitware.com:/cvsroot/CableSwig

cvsdirname=`pwd`
dirname=cableswig-${VERSION}+cvs${DATE}.orig
tarname=cableswig_${VERSION}+cvs${DATE}.orig.tar.gz

cvs -z3 export -r ${ITKBRANCHTAG} -D ${DATE} -d ${dirname} CableSwig

# Remove files with (a) no license, or (b) non-free license.
#
rm -rf ${dirname}/GCC
rm -rf ${dirname}/GCC_XML


# Build tarball
#
rm -rf ../${dirname}
mv ${dirname} ..
cd ..
tar czf ${tarname} ${dirname}
