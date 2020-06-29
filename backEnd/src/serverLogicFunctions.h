//
// Created by amagood on 2020/5/9.
//

#ifndef MY_PROJECT_SERVERLOGICFUNCTIONS_H
#define MY_PROJECT_SERVERLOGICFUNCTIONS_H

#include "json.hpp"
using json = nlohmann::json;

json getProductById(int id);
json getProductDetailsById(int id);
json getCategoryById(int id);
json getEvaluationById(int id);
int  createEvaluationByIds(std::vector<int> productIds);  ///returns id of the new evaluation (< 0 if anything went wrong)
bool deleteEvaluationById(int id);  ///false if failed
json getAllCategories();
#endif //MY_PROJECT_SERVERLOGICFUNCTIONS_H
