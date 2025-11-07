#include "core/model/SliceModel.h"
#include <QMetaType>
#include <QVariant>

SliceModel::SliceModel(QObject* parent) : QObject(parent) {
    qRegisterMetaType<SliceResult>("SliceResult");
}

const SliceResult& SliceModel::state() const {
    return s_;
}

void SliceModel::apply(const AnalysisResultEnvelope& env) {
    if (env.kind != QLatin1String("slice.v1")) // пока обработка ответа от одного плагина
        return;
    // 2) Типобезопасная проверка: можно ли вытащить из QVariant именно SliceResult?
    if (!env.payload.canConvert<SliceResult>())
        return;
    s_ = env.payload.value<SliceResult>();
    emit changed(s_);
}
