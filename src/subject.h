#ifndef SUBJECT_H
#define SUBJECT_H

#include "info.h"
#include <vector>
#include <memory>

class View;

class Subject {
    public:
        Subject();
        void attachView(std::unique_ptr<View> v);
        virtual ~Subject() = 0;

    protected:
        void updateViews(Info& info);

    private:
        std::vector<std::unique_ptr<View>> _views;
};


#endif
