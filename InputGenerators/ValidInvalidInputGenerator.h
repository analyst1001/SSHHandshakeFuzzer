#include "./InputGenerator.h"

#ifndef VALINVALINPUTGEN_H
#define VALINVALINPUTGEN_H
class ValidInvalidInputGenerator : public InputGenerator {
    private:
        bool generateValid;

    public:
	ValidInvalidInputGenerator();
        void setGenerateValid(bool valid);
        bool getGenerateValid();
};
#endif
