#ifndef SEARCHER_H
#define SEARCHER_H

template<typename T>
struct Searcher {
    Searcher(){}
    virtual bool empty() = 0;
    virtual T search_next() = 0;
    virtual void push(const T& element) = 0; // how to make derived class implement function just with the same name?
};

#endif