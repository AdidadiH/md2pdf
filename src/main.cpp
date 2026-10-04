#include "CLI11.hpp"
#include "hpdf.h"
#include <fstream>
#include <iostream>
#include <string>

#define TEXT_BOX_PADDING 50

int main(int argc, char **argv) {
  // init CLI11
  CLI::App app{"Simple Markdown File to A4 PDF converter"};

  argv = app.ensure_utf8(argv);

  std::string mdFile;
  std::string pdfFile;

  app.add_option("-f,--file", mdFile, "Markdown input file path")
      ->required()
      ->check(CLI::ExistingFile);
  app.add_option("-o,--output", pdfFile, "PDF output file path")
      ->check(CLI::NonexistentPath);

  CLI11_PARSE(app, argc, argv);

  // check params
  {
    auto const pos =
        mdFile.rfind(".md"); // check if Markdown file has invalid extension
    if (pos >= mdFile.size()) {
      std::cout << "Incorrect file extension for -f: \"" << mdFile
                << "\".\n\n    See --help for more\n"
                << std::endl;
      return 1;
    }
  }
  if (!(!pdfFile.empty() && !(pdfFile.rfind(".pdf") >=
                              pdfFile.size()))) { // check if no pdf path given
                                                  // or given without name
    pdfFile = mdFile.substr(0, mdFile.rfind(".")) +
              ".pdf"; // generate pdf file path based on Markdown File Path
  }

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

  // get page attributes
  HPDF_REAL height = HPDF_Page_GetHeight(page);
  HPDF_REAL width = HPDF_Page_GetWidth(page);

  // load font
  HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);
  HPDF_Page_SetFontAndSize(page, font, 12);

  // convert md to pdf
  std::ifstream md(mdFile);

  HPDF_Page_BeginText(page);

  HPDF_Page_MoveTextPos(page, 50, height - 50);
  std::string line;
  std::string content;
  while (getline(md, line)) {
    content += line + "\n";
  }
  HPDF_Page_TextRect(page, TEXT_BOX_PADDING, height - TEXT_BOX_PADDING,
                     width - TEXT_BOX_PADDING, TEXT_BOX_PADDING,
                     content.c_str(), HPDF_TALIGN_LEFT, NULL);

  HPDF_Page_EndText(page);

  md.close();

  // save to file
  HPDF_SaveToFile(pdf, pdfFile.c_str());

  std::cout << pdfFile << std::endl;

  HPDF_Free(pdf); // free pdf obj
  return 0;
}
