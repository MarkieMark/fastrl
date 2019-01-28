/*
 * Mark Benjamin 28th January 2019
 * (c) Mark Benjamin 2019
 */

#ifndef FASTRL_VISUALIZER_OO_STATE_PAINTER_HPP
#define FASTRL_VISUALIZER_OO_STATE_PAINTER_HPP

#include "object_state_painters.hpp"

class OOStatePainter : public StatePainter {
public:
    vector<pair<string, ObjectPainter *>> objectClassPainterList; // string is class name

    /**
     * Map of painters that define how to paint specific objects;
     * if an object appears in both specific & general lists, the specific painter is used
     */
    map<string, ObjectPainter *> specificObjectPainters;

    /**
     * Adds a class that will paint objects that belong to a given OO-MDPclass.
     * @param className the name of the class that the provided painter can paint
     * @param op the painter
     */
    void addObjectClassPainter(string className, ObjectPainter * op){
        objectClassPainterList.emplace_back(pair<string, ObjectPainter *>(className, op));
    }

    /**
     * Adds a painter that will be used to paint a specific object in states
     * @param objectName the name of the object this painter is used to paint
     * @param op the painter
     */
    void addSpecificObjectPainter(string objectName, ObjectPainter * op){
        specificObjectPainters.insert(pair<string, ObjectPainter *>(objectName, op));
    }

    void paint(QPainter * qp, State * s, float canvas_width, float canvas_height) override {
        if(s == nullptr || dynamic_cast<NullState *>(s) != nullptr){
            return;
        }
        if(dynamic_cast<OOState *>(s) == nullptr) {
            string message = "OOStatePainter cannot paint the state, because it is a ";
            message += typeid(s).name();
            message += " and does not implement OOState";
            throw runtime_error(message);
        }
        auto * os = dynamic_cast<OOState *>(s);
        //draw every object in class order when there is no specific painter
        for(auto op : objectClassPainterList) {
            vector<ObjectInstance *> objects = os->objectsOfClass(op.first);
            for(auto o : objects){
                if(specificObjectPainters.find(op.first) == specificObjectPainters.end()) {
                    op.second->paintObject(qp, os, o, canvas_width, canvas_height);
                }
            }
        }
        //draw each object when there is a painter to do so
        auto objects = os->objects();
        for(auto o : objects){
            //is there a specific object painter for this object?
            if(specificObjectPainters.find(typeid(o).name()) != specificObjectPainters.end()){
                specificObjectPainters.find(typeid(o).name())->second->paintObject(qp, os, o, canvas_width, canvas_height);
            }
        }
    }
};

#endif //FASTRL_VISUALIZER_OO_STATE_PAINTER_HPP
