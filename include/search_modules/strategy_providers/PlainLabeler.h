#ifndef PLAIN_LABELER_H
#define PLAIN_LABELER_H

#include "user_def/oneRjSumCjNode.h"
#include "search_modules/strategy_providers/Labeler.h"

struct PlainLabeler: Labeler
{
    const int max_contour = 100;
    int brfs_label = 0;
    enum STRATEGY {BFS, BrFS, CBFS} strategy;
    void bfs(){strategy = STRATEGY::BFS;}
    void brfs(){strategy = STRATEGY::BrFS;}
    void cbfs(){strategy = STRATEGY::CBFS;}
    PlainLabeler(){};
    int operator()(const OneRjSumCjNode &node) const{      
        switch(strategy){
            case STRATEGY::BFS:
                return 0;
            case STRATEGY::BrFS:
                return (brfs_label + 1) % max_contour;
            case STRATEGY::CBFS:
                return node.seq.size();
            default:
                return 0;
        }

    }
};


#endif