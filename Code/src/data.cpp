#include "data.hpp"

data::data(){
    feature_vector = new std::vector<uint8_t>;
}

data::~data(){

}

void data::set_feature_vector(std::vector<uint8_t> * vect){
    feature_vector = vect;
}   

void data::append_to_feature_vector(uint8_t value){
    feature_vector->push_back(value);
}

void data::set_label(uint8_t value){
    label = value;
}
void data::set_enumerated_label(int value){
    enum_label = value;
}

int data::get_feature_vector_size() const{
    return feature_vector->size();
}
int data::get_label() const{
    return label;
}
int data::get_enumerated_label() const{
    return enum_label;
}

// using uintVec = std::vector<uint8_t>;
std::vector<uint8_t> *data::get_feature_vector() const{
    return feature_vector;
}    