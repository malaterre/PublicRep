#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */
#include "dcmtk/dcmdata/dctk.h"

int main()
{
  static const char geiis[] = "GEIIS";
  OFString geiis_good = geiis;
  geiis_good += ' ';
  OFString geiis_bad = geiis;
  geiis_bad += '\0';
  OFCondition cond = DcmLongString::checkStringValue(geiis_good);
  std::cout << cond.text() << std::endl;

  cond = DcmLongString::checkStringValue(geiis_bad);
  std::cout << cond.text() << std::endl;

  cond = DcmLongString::checkStringValue(geiis_bad, "1-n");
  std::cout << cond.text() << std::endl;

  // http://dicom.nema.org/medical/dicom/current/output/chtml/part05/sect_6.2.html#para_5184abc4-043b-422d-8d27-8955f439cdb8
  cond = DcmLongString::checkStringValue(geiis_bad, "1-n", "ISO_IR 192");
  std::cout << cond.text() << std::endl;

  return 0;
}
