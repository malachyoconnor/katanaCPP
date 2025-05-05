#include <iostream>
#include <filesystem>
#include <hpdf.h>
#include "reader_thread.h"

namespace fs = std::filesystem;
using namespace std;

constexpr int FILE_SIZE = 5;

int main() {
  cout << "HPDF Version: " << HPDF_GetVersion() << endl;

  vector<fs::path> chapterVector {};
  for (const auto& entry : fs::directory_iterator("Psyren")) {
    chapterVector.push_back(entry.path());
  }

  vector<fs::path> tempChapterVector = {};

  for (int i = 0; i < chapterVector.size(); i++) {
    if (i != 0 && i % FILE_SIZE == 0) {
      auto newThread = ReaderThread(tempChapterVector, "test" + to_string(i) + ".pdf");
      newThread.saveImagesToPdf();

      tempChapterVector.clear();
    }

    tempChapterVector.push_back(chapterVector[i]);
  }


  return 0;
}
