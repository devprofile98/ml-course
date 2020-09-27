#ifndef __DATA_H
#define __DATA_H


#include <vector>
#include<stdio.h>
#include<stdint.h>


class data{

    std::vector<uint8_t> *feature_vector;
    uint8_t label;
    int enum_label;

public:
    data();
    ~data();
    void set_feature_vector(std::vector<uint8_t> *);
    void append_to_feature_vector(uint8_t);
    void set_label(uint8_t); 
    void set_enumerated_label(int);

    int get_feature_vector_size() const;
    int get_label() const;
    int get_enumerated_label() const;

    using uintVec = std::vector<uint8_t>;
    uintVec *get_feature_vector() const;         

};

#endif