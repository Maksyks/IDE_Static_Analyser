#include "core/viewers/SliceResultViewer.h"
#include "core/model/SliceModel.h"
#include "../../app/CodeEditor.h"   // путь из core/ к app/

SliceResultViewer::SliceResultViewer(QWidget* parent)
    : QTabWidget(parent)
{
    tabCustom_ = new CodeEditor(this); tabCustom_->setReadOnly(true);
    tabLlvm_   = new CodeEditor(this); tabLlvm_->setReadOnly(true);
    addTab(tabCustom_, tr("original_custom"));
    addTab(tabLlvm_,   tr("llvm2c"));
}

void SliceResultViewer::bind(SliceModel* model) {
    connect(model, &SliceModel::changed, this, &SliceResultViewer::onChanged);
}

void SliceResultViewer::onChanged(const SliceResult& s) {
    tabCustom_->setPlainText(s.custom);
    tabLlvm_->setPlainText(s.llvm2c);
    // пробрасываем клики по строке наружу
    connect(tabCustom_, &CodeEditor::lineActivated, this, &SliceResultViewer::lineActivated);
    //connect(tabLlvm_,   &CodeEditor::lineActivated, this, &SliceResultViewer::lineActivated);
}
