#pragma once
#include "../../core/Model.h"

class CModel
{
public:

    Model model{};

    CModel(const std::string& filepath);

    ~CModel();
};