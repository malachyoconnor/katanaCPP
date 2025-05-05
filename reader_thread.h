//
// Created by malac on 05/05/2025.
//

#ifndef READERTHREAD_H
#define READERTHREAD_H
#include <vector>
#include <thread>
#include <hpdf.h>
#include <filesystem>
#include <c++/13/optional>

#include "utils.h"

namespace fs = std::filesystem;

class ReaderThread {
  HPDF_Doc pdf_;
  std::optional<std::thread> thread_;
  std::vector<fs::path> chapters_;
  std::string output_name_;

  void writeChaptersToPdf() const {
    for (const fs::path &chapter: chapters_) {
      for (const auto &page_path: fs::directory_iterator(chapter)) {

        const HPDF_Page page = HPDF_AddPage(pdf_);
        const HPDF_Image image = HPDF_LoadJpegImageFromFile(pdf_, page_path.path().c_str());

        const unsigned int iw = HPDF_Image_GetWidth(image);
        const unsigned int ih = HPDF_Image_GetHeight(image);

        HPDF_Page_SetWidth(page, iw);
        HPDF_Page_SetHeight(page, ih);

        HPDF_Page_DrawImage(page, image, 0, 0, iw, ih);
      }
    }
  }

public:

  // TODO: I would like to pass chapters by reference, don't fully understand how to.
  ReaderThread(std::vector<fs::path> chapters, const std::string &output_name) {
    output_name_ = output_name;
    chapters_ = chapters;
    pdf_ = HPDF_New(error_handler, nullptr);

    if (!pdf_) {
      std::cout << "ERROR: Cannot create PdfDoc object" << std::endl;
      throw std::runtime_error("error: cannot create PdfDoc object\n");
    }
  }

  void saveImagesToPdf() {
    thread_ = std::thread([this] {
      this->writeChaptersToPdf();
    });
  }

  ~ReaderThread() {
    if (!thread_.has_value()) {
      std::cout << "saveImagesToPdf never called." << std::endl;
      HPDF_Free(this->pdf_);
      return;
    }

    if (thread_->joinable()) {
      thread_->join();
    }

    HPDF_SaveToFile(pdf_, output_name_.c_str());
    HPDF_Free(this->pdf_);
  }

};

#endif //READERTHREAD_H
