#ifndef CBFSIMPL_H
#define CBFSIMPL_H

#include <memory>
#include "search_modules/searchMod.h"
using std::shared_ptr;

template <typename T>
struct CBFSImpl{
private:
    shared_ptr<map<LABEL_TYPE, PriorityQueue<T>>> contours;
    map<LABEL_TYPE, PriorityQueue<T>>::iterator current_contour_iter;;
public:
    shared_ptr<map<LABEL_TYPE, PriorityQueue<T>>> contours(){
        return make_shared<map<LABEL_TYPE, PriorityQueue<T>>>(contours);
    }
    map<LABEL_TYPE, PriorityQueue<T>>::iterator current_contour_iter(){
        return current_contour_iter;
    }
    CBFSImpl(){         
        contours = make_shared<map<LABEL_TYPE, PriorityQueue<T>>>();    
        PriorityQueue<OneRjSumCjNode> contour_0(OneRjSumCjNode::cmpr);
        assertm("Job element class should implement dummy()", decltype(&T::dummy))
        contour_0.push(T::dummy());
        contours->insert(make_pair(0, contour_0));
        current_contour_iter = graph.contours->begin();
    }
    bool empty(){
        return contours->empty();
    }
    T search_next(){
        T current_element = current_contour_iter->second.top();
        current_contour_iter->second.extract();
        return current_element;        
    }
    void push(const T &element) = 0;
    void push(LABEL_TYPE label, const T &element){
        map<LABEL_TYPE, PriorityQueue<T>>::iterator target_contour_iter = contours->find(label);
        if(target_contour_iter == contours->end())
        {
            PriorityQueue<OneRjSumCjNode> pq_insert(OneRjSumCjNode::cmpr);
            pq_insert.push(*it);
            #if DEBUG_LEVEL >=2
                cout << "inserting node to contour " << label << ": " << *it  << endl;
            #endif
            contours->insert(make_pair(label, pq_insert));
        }
        else
        {
            target_contour_iter->second.push(*it);
            #if DEBUG_LEVEL >=2
                cout << "inserting node to contour " << label << ": " << *it  << endl;
            #endif
        }               
    }

    // if return true, optimal solution is found    
    bool current_contour_cleanup(){
        // clean contour
        if(current_contour_iter->second.empty())
        {
            // if the current contour is empty, we need to find the next contour
            map<int, PriorityQueue<T>>::iterator current_iter = current_contour_iter;
            
            // if there's contour left after deletion, cycle back or go to the next
            if(contours->size() > 1)
            {
                if(current_contour_iter != contours->end())
                {
                    ++current_contour_iter;
                }
                else
                {
                    current_contour_iter = contours->begin();
                }
                contours->erase(current_iter);
                return false;
            }
            else
            {
                // only one contour left and the contour is empty, we need to stop
                contours->erase(current_iter);
                return true;
            }
        }
        return false;
    }   
}


#endif