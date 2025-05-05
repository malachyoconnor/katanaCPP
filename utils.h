//
// Created by malac on 05/05/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <hpdf.h>

// Silly little error handler for use when creating PDFS.
inline void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
  std::cout << "ERROR:" << error_no << " "<< detail_no << std::endl;
}


#endif //UTILS_H
