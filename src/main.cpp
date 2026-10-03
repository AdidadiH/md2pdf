#include "hpdf.h"
#include <iostream>

int main() {
  HPDF_Doc pdf = HPDF_New(NULL, NULL); // create pdf obj

  if (!pdf) { // check if pdf obj was created
    std::cout << "ERROR: Cannot create PDF object." << std::endl;
    return 1;
  }

  // set attributes
  HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);
  HPDF_SetPageMode(pdf, HPDF_PAGE_MODE_USE_OUTLINE);

  HPDF_Page page = HPDF_AddPage(pdf); // create page

  // set attributes
  HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

  // save to file
  HPDF_SaveToFile(pdf, "test.pdf");

  HPDF_Free(pdf); // free pdf obj
  return 0;
}
