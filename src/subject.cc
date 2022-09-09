#include "subject.h"
#include "view.h"

Subject::Subject() {}
Subject::~Subject() {}

void Subject::attachView(std::unique_ptr<View> v) { _views.emplace_back(std::move(v)); }

void Subject::updateViews(Info& info) {
    for (auto &view : _views) view->notify(info);
}
