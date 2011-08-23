$ gccxml -fxml=/tmp/p.xml /usr/include/aspell.h

# CXX
xsltproc aspell.xsl aspell.xml  > /tmp/out.cxx

# HPP
xsltproc aspell2.xsl aspell.xml  > /tmp/out.hpp  
