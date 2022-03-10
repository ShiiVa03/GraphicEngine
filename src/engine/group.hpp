#ifndef GROUP_H
#define GROUP_H


#include "transformations/translation.hpp"
#include "transformations/rotation.hpp"
#include "transformations/scalation.hpp"

#include "model.hpp"

#include <vector>

enum class Transformation {
    TRANSLATION,
    ROTATION,
    SCALATION
};

enum class Transformation transformationStringToEnum(std::string transformation);

class Group{
    public:
        Translation translation;
        Rotation rotation;
        Scalation scalation;
        std::vector<Transformation> ordered_transformations;

        std::vector<Model> models;

        std::vector<Group> groups;

        Group();

        void add_translation(Translation translation);
        void add_rotation(Rotation rotation);
        void add_scalation(Scalation scalation);

        void add_model(Model& model);

        void add_group(Group& group);
        
};

#endif
