#include "data_handler.hpp"


data_handler::data_handler(){
    data_array = new std::vector<data *>;
    test_data = new std::vector<data *>;
    training_data = new std::vector<data *>;
    validation_data = new std::vector<data *>;
}
data_handler::~data_handler(){
    
}
void data_handler::read_feature_vector(std::string path){

    uint32_t header[4]; // magic, image num , rowsize, colsize
    unsigned char bytes[4];

    FILE *f=fopen(path.c_str(), "r");
    if (f){
        
        for (int i=0;i<4;i++){
            if(fread(bytes,sizeof(bytes),1,f)){
                header[i] = convert_to_little_indian(bytes);
            }
        }
            std::cout<<" getting file header done!"<<std::endl;

        int image_size = header[2]*header[3];
        
        for(int i =0;i<header[1];i++){
        
            data *d = new data();
            uint8_t element[1];

            for (int i = 0; i < image_size; i++)
            {
                if (fread(element,sizeof(element),1,f)){
                    d->append_to_feature_vector(element[0]);
                }
                else
                {
                    std::cout<<"Error reading element from file"<<std::endl;
                    exit(1);
                }
                
            }
            data_array->push_back(d); 
        }

        std::cout<<"successfully read and stored data"<<std::endl;
    }
    else{
        std::cout<<"could not open the file "<<std::endl;
        exit(1);

    }


}
void data_handler::read_feature_labels(std::string path){
    uint32_t header[2];
    unsigned char bytes[2];
    FILE *f = fopen(path.c_str(),"r");

    if (f){

        for(int i=0;i<2;i++){
            
            if(fread(bytes, sizeof(bytes),1, f)){
                header[i] = convert_to_little_indian(bytes);
            }
        }
        std::cout<<"getting lablel file data Done!"<<std::endl;
        for (int i=0;i<header[1];i++){
            uint8_t element[1];
            if(fread(element, sizeof(element),1,f)){
                data_array->at(i)->set_label(element[0]);
            }
            else{
                std::cout<<"error in reading label file information, closing application"<<std::endl;
                exit(1);
            }
        }
        std::cout<<"successfully read and stored label data"<<std::endl;    
    }
    else{
        std::cout<<"could not open the file, Quiting"<<std::endl;
        exit(1);
    }
}
void data_handler::split_data(){

    std::unordered_set<int> used_index;
    int train_size = data_array->size() * TRAINIG_SET_PERCENT;
    int test_size = data_array->size() * TEST_PERCENT;
    int validation_size = data_array->size() * VALIDATION_PERCENT;

    //training data
    int count = 0;
    while(count < train_size){
        int rand_int = rand() % data_array->size();
        if (used_index.find(rand_int) == used_index.end()){
            training_data->push_back(data_array->at(rand_int));
            used_index.insert(rand_int);
            count++;
        }
    }

    // test data 
    count = 0;
    while(count < test_size){
        int rand_int = rand() % data_array->size();
        if (used_index.find(rand_int) == used_index.end()){
            test_data->push_back(data_array->at(rand_int));
            used_index.insert(rand_int);
            count++;
        }
    }

    //validation data
    count = 0;
    while(count < validation_size){
        int rand_int = rand() % data_array->size();
        if (used_index.find(rand_int) == used_index.end()){
            validation_data->push_back(data_array->at(rand_int));
            used_index.insert(rand_int);
            count++;
        }
    }

    std::cout<<"training data size is :"<<training_data<<std::endl;
    std::cout<<"test data size is :"<<test_data<<std::endl;
    std::cout<<"validation data size is :"<<validation_data<<std::endl;

}
void data_handler::count_classes(){

    int count = 0;
    for(unsigned int i=0;i<data_array->size();i++){
        if (class_map.find(data_array->at(i)->get_label()) == class_map.end()){
            class_map[data_array->at(i)->get_label()] = count;
            data_array->at(i)->set_enumerated_label(count);
            count++;
        }
    }

    num_classes = count;
    std::cout<<"successfully extraxted "<<num_classes<<" unique classes"<<std::endl;
}

uint32_t data_handler::convert_to_little_indian(const unsigned char* bytes){
    return (uint32_t) (bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | bytes[3]);
}

std::vector<data *> *data_handler::get_training_data(){
    return training_data;
}
std::vector<data *> *data_handler::get_test_data(){
    return test_data;
}
std::vector<data *> *data_handler::get_validation_data(){
    return validation_data;
}


int main(){
    data_handler *dh = new data_handler();
    dh->read_feature_vector("../train-images.idx3-ubyte");
    dh->read_feature_labels("../train-labels.idx1-ubyte");
    dh->split_data();
    dh->count_classes();
}