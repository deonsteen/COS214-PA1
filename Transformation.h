#ifndef COS214_PA1_TRANSFORMATION_H
#define COS214_PA1_TRANSFORMATION_H

#include <string>
#include <vector>

class Transformation
{

protected:
    std::string name;

public:
    Transformation(std::string name);
    virtual ~Transformation();

    virtual Transformation *clone() const = 0;
    virtual std::vector<std::string> apply(const std::vector<std::string> &records) = 0;
    std::string getName() const;
};

#endif // COS214_PA1_TRANSFORMATION_H
